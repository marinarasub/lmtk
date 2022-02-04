/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in the utils library for LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

 /**
 * @file threadpool.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains handy string utilities.
 */

#ifndef _UTILS_THREADPOOL_H_
#define _UTILS_THREADPOOL_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <iostream>
// #include <chrono>
// #include <random> // just for testing
#include <stdexcept>
#include <stdarg.h>
#include <tuple>


namespace threadpool {

    /**
    * @struct task "threadpool.h"
    * @brief A task for a thread which stores a void calback
    */
    struct task 
    {
        std::function<void()> callback;
    };


    // TODO priority queue
    /**
    * @class TaskQueue "threadpool.h"
    * @brief A FIFO queue of callback tasks that is thread-safe
    */
    class TaskQueue
    {
    public:

        /**
        * Creates an empty task queue.
        */
        TaskQueue();

        /**
        * Pushes a task onto the task queue.
        * 
        * @param t Task to push onto queue
        */
        void enqueue(const task &t);

        /**
        * Pop the oldest task on the queue.
        * 
        * Removes the task from the queue
        * @return Oldest task on the queue.
        */
        task dequeue();

        /**
        * Checks if the task queue is empty.
        * 
        * @return True if empty, false otherwise
        */
        bool empty() const;

        /**
        * Get the size of the task queue.
        * 
        * @return Size of the task queue
        */
        size_t size() const;

    private:

        std::queue<task> task_queue; /**< Internal storage of task queue */

        std::mutex queue_mtx; /**< Mutex for queue access */
    };


    /**
    * @class ThreadPool "threadpool.h"
    * @brief Class for a pool of flexible worker threads which can be given
    * miscellaneous tasks to complete.
    * 
    * Any sized pool of worker threads can be created, but it is not recommended
    * to create more than hardware support unless tasks require lots of waiting,
    * such as memory or disk read/writes.
    */
    class ThreadPool
    {
    public:

        /**
        * Creates a threadpool with the default number of threads.
        * 
        * Checks hardware concurrency for number of threads supported.
        */
        ThreadPool();

        /**
        * Creates a threadpool with n threads.
        * 
        * @param num_threads Number of threads to add to pool
        */
        ThreadPool(size_t num_threads);

        /**
        * Deletes all threads.
        * 
        * @warning Should not be called before join if the pool has already 
        * been started.
        */
        ~ThreadPool();

        /**
        * Starts the threads into worker thread main loop.
        * 
        * The threads will run all tasks are completed, unless stopped
        * @see stop()
        */
        void start();

        /**
        * Join the threadpool after the tasks are completed.
        * 
        * Will join each thread as long as joinable (i.e. not detached)
        * Threads will exit when there are no more tasks remaining.
        * @note tasks can no longer be added from the thread will calls join as 
        * the thread will be blocked.
        */
        void join();

        /**
        * Requests threads to stop execution, regardless of tasks remaining.
        * 
        * Threads will exit when finished their current task, if any. Then joins
        * the threadpool
        * @note Not a force terminate, will not save infinite loops, deadlocks
        * or other indefinite execution.
        */
        void stop();

        /**
        * Detach all threads in the pool, allowing threads to execute 
        * independent of main thread.
        * 
        * Threads will no longer be joinable.
        */
        void detach();

        /**
        * Adds a task for the threadpool given callback and arguments.
        * 
        * Add using std::function
        * @tparam Args Variadic arguments
        * @param callback Callback function for threads to execute
        * @param args Variadic arguments to call callback with
        * Basically, you can call with any arguments you want
        * // !!! I don't think it handles references very well
        */
        template<typename ... Args>
        void addTask(std::function<void(Args...)> callback, Args... args)
        {
            std::function<void()> store = [=]{ 
                callback(args...); 
            };
            tasks.enqueue(task{store});
            recheck.notify_one();
        }

        /**
        * Adds a task for the threadpool given callback and arguments.
        *
        * Add using c-style callback (function pointer)
        * @tparam Args Variadic arguments
        * @param callback Callback function for threads to execute
        * @param args Variadic arguments to call callback with
        * Basically, you can call with any arguments you want
        * // !!! I don't think it handles references very well
        */
        template<typename ... Args>
        void addTask(void(*callback)(Args...), Args... args)
        {
            std::function<void()> store = [=]{ 
                callback(args...); 
            };
            tasks.enqueue(task{store});
            recheck.notify_one();
        }

        /**
        * Get number of tasks remaining, when called.
        * 
        * @return Number of tasks remaining on queue
        */
        size_t tasks_remaining() const;

        /**
        * Returns the total number of tasks completed by the threadpool when
        * called.
        * 
        * @return Cumulative number of tasks completed
        */
        size_t tasks_completed() const; 
        
    private:
        
        /**
        * Helper function for joining all threads.
        */
        void join_all_threads();

        /**
        * Helper function for detaching all threads.
        */
        void detach_all_threads();

        /**
        * Helper function for deleting threads.
        */
        void destroy();

        /**
        * Main loop for worker threads to run in.
        * 
        * While the threadpool has started and has not been asked to stop, the
        * threads will check the queue for tasks. If there are tasks, the thread
        * will dequeue an item and run the task. In not, it will block until
        * signaled to check again.
        * @param tpool Threadpool it is part of
        */
        static void worker_thread(ThreadPool *tpool);

        /**
        * Function for executing the callback of a task using calling thread.
        * 
        * @param t Task to execute
        */
        static void execute_task(const task &t);

        /**
        * Checks if threads should stop execution.
        * 
        * @return True if thead should stop running the main worker thread loop,
        * false otherwise
        */
        bool should_terminate();

        /**
        * Checks to see if threads should wait for a new task
        * 
        * @return True if there are no tasks and the threadpool has not been 
        * asked to stop.
        */
        bool should_wait();

        /**
        * Check if threads should run a task from the queue
        * 
        * @return True if there are tasks on the queue, and the threadpool has 
        * not been asked to stop
        */
        bool should_run_task();

        TaskQueue tasks; /**< Queue of tasks to run */

        std::vector<std::thread*> workers; /**< Worker threads */

        size_t idle_threads; /**< Number of threads not running a task */

        std::mutex mtx; /**< Threadpool mutex */

        // this DOES NOT guarantee all tasks added will be completed
        bool stop_request; /**< Flag for termination ASAP */

        // this guarantees all tasks added will be completed
        bool finish_up; /**< Flag on termination when task queue is empty */
        
        std::condition_variable complete;
        /**< Condition variable notifying a single thread has completed */
        
        std::condition_variable recheck;
        /**< Condition variable for notifying threads to recheck status */
        
        size_t total_tasks_completed; 
        /**< Number of tasks completed by the threadpool */
    };
    
}
#endif // _UTILS_THREADPOOL_H_