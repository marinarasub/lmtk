#include "threadpool.h"

namespace threadpool {

    TaskQueue::TaskQueue()
    {
        task_queue = std::queue<task>();
    }

    void TaskQueue::enqueue(const task& t)
    {
        std::unique_lock<std::mutex> lock(queue_mtx);
        task_queue.push(t);
    }

    task TaskQueue::dequeue()
    {
        std::unique_lock<std::mutex> lock(queue_mtx);
        if (task_queue.empty()) throw std::logic_error("queue is empty");
        task ret = task_queue.front();
        task_queue.pop();

        return ret;
    }

    size_t TaskQueue::size() const
    {
        //std::unique_lock<std::mutex> lock(queue_mtx);
        return task_queue.size();
    }

    bool TaskQueue::empty() const
    {
        //std::unique_lock<std::mutex> lock(queue_mtx);
        return task_queue.empty();
    }

    ThreadPool::ThreadPool() : ThreadPool(0)
    {
    }

    
    ThreadPool::ThreadPool(size_t num_threads) 
        : finish_up(false), stop_request(false), total_tasks_completed(0)
    {
        //std::unique_lock<std::mutex> lock(mtx);
        if (num_threads == 0) num_threads = std::thread::hardware_concurrency();
        for (size_t i = 0; i < num_threads; i++)
        {
            workers.push_back(new std::thread());
        }
        idle_threads = num_threads;
    }

    ThreadPool::~ThreadPool()
    {
        destroy();
    }

    void ThreadPool::start()
    {
        //destroy();
        //std::unique_lock<std::mutex> lock(mtx);
        //join(); // if u call start more than once
        for (size_t i = 0; i < workers.size(); i++)
        {
            *workers[i] = std::thread(worker_thread, this);
        }
    }

    // template<typename ... Args>
    // void ThreadPool::addTask(std::function<void(Args...)> callback, Args... args)
    // {
    //     std::function<void()> store = [&]{ callback(args...); };
    //     tasks.enqueue(task{store});
    //     recheck.notify_one();
    // }

    size_t ThreadPool::tasks_remaining() const
    {
        return tasks.size();
    }

    size_t ThreadPool::tasks_completed() const
    {
        return total_tasks_completed;
    }

    void ThreadPool::join()
    {
        std::unique_lock<std::mutex> lock(mtx);
        finish_up = true;
        recheck.notify_all();
        while(idle_threads < workers.size())
           complete.wait(lock);
        lock.unlock();
        join_all_threads();
    }

    void ThreadPool::detach()
    {
        std::unique_lock<std::mutex> lock(mtx);
        finish_up = true;
        recheck.notify_all();
        lock.unlock();
        detach_all_threads();
    }

    void ThreadPool::stop()
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop_request = true;
        recheck.notify_all();
        lock.unlock();
        join_all_threads();
    }

    void ThreadPool::join_all_threads()
    {
        for (size_t i = 0; i < workers.size(); i++)
        {
            //std::cout << "joining..." << std::endl;
            if (workers[i]->joinable()) workers[i]->join();
        }
    }

    void ThreadPool::detach_all_threads()
    {
        for (size_t i = 0; i < workers.size(); i++)
        {
            //std::cout << "detaching..." << std::endl;
            workers[i]->detach();
        }
    }

    void ThreadPool::destroy()
    {
        for (size_t i = 0; i < workers.size(); i++)
        {
            delete workers[i];
        }
    }

    void ThreadPool::worker_thread(ThreadPool *tpool)
    {  
        std::unique_lock<std::mutex> lock(tpool->mtx);
        tpool->idle_threads--;
        lock.unlock();

        while (!tpool->should_terminate()) {
            // simulated delay for DEBUG
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // check lock so queue empty wont change until unlock
            lock.lock(); // queue has its own mutex
            // wait for either end request (on join) or new item if empty
            while (tpool->should_wait())
            {
                tpool->recheck.wait(lock);
            }
            if (!tpool->should_run_task()) {
                lock.unlock(); 
                continue; 
            }
            task t = tpool->tasks.dequeue();
            lock.unlock();
            execute_task(t);
            tpool->total_tasks_completed++;
        } // end task check loop

        // notify that thread is done
        lock.lock();
        //std::cout << "Complete: " << std::this_thread::get_id() << std::endl;
        tpool->idle_threads++;
        tpool->complete.notify_all();
        lock.unlock();
    }

    void ThreadPool::execute_task(const task & t)
    {
        t.callback();
    }
    
    bool ThreadPool::should_terminate()
    {
        return (tasks.empty() && finish_up) || stop_request;
    }

    bool ThreadPool::should_wait()
    {
        return (tasks.empty() && !(finish_up || stop_request));
    }

    bool ThreadPool::should_run_task()
    {
        return (!tasks.empty() && !stop_request);
    }

}