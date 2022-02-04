#include "renderer.h"

namespace renderer {

    ImageRenderer::ImageRenderer(size_t threads, Image* in)
        : num_threads(threads)
    {
        if (!in) throw std::invalid_argument("null pointer to image");
        this->in = in;
        this->progress_callback = nullptr;
    }

    ImageRenderer::~ImageRenderer()
    {
        //if (out) delete out;
    }

    void ImageRenderer::renderRow(ImageShader* fx,
        Image* in,
        Image* out, 
        size_t row, 
        progress_tracker* tracker,
        render_callback_t progress_callback)
    {
        try {
            for (size_t x = 0; x < in->width(); x++)
            {
                out->setRGBAPixel((*fx)(*in, x, row), x, row);
            }

            if (progress_callback)
            {
                progress_callback(static_cast<float> (tracker->current_rows_done++) / (out->height()-1),
                    tracker->current_effect,
                    tracker->total_effects, 
                    false);
            }
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl; // how to handle??
            if (progress_callback)
            {
                progress_callback(static_cast<float> (tracker->current_rows_done++) / out->height(),
                    tracker->current_effect,
                    tracker->total_effects,
                    true);
            }
        }
    }

    void ImageRenderer::setProgressCallback(render_callback_t callback)
    {
        progress_callback = callback;
    }

    void ImageRenderer::render(PluginChain& fx, Image* out)
    {
        if (fx.size() == 0) return;
        if (in->width() != out->width()) throw std::runtime_error("images must be same width");
        if (in->height() < out->height()) throw std::runtime_error("ran over image height");

        progress_tracker track(fx.size());
        threadpool::ThreadPool tpool(num_threads);
        for (size_t i = 0; i < fx.size(); i++)
        {
            tpool.start();
            for (size_t row = 0; row < in->height(); row++)
            {
                tpool.addTask(&ImageRenderer::renderRow, fx[i], in, out, row, &track, progress_callback);
            }

            tpool.join();
            // copy before next fx
            *in = *out;
            track.current_rows_done = 0;
            track.current_effect++;
        }
    }

}