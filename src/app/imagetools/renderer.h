/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in the LMTKimage console app.
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

#ifndef __RENDERER_H_
#define __RENDERER_H_
#pragma once

#include <atomic>
#include "../../utils/threadpool.h"
#include  "../../libLMTKimage/image.h"
#include  "../../libLMTKimage/filters.h"
#include  "../../libLMTKimage/pluginchain.h"

namespace renderer {

   using namespace image;

   /**
   * @class ImageRenderer "renderer.h"
   * @brief A helper class for multithreaded image rendering
   */
   class ImageRenderer 
   {

       typedef void(*render_callback_t)(double current_effect_progress,
           size_t effect_number,
           size_t total_effects,
           bool failed);

       struct progress_tracker
       {
           std::atomic<size_t> current_rows_done;
           std::atomic<size_t> current_effect;
           std::atomic<size_t> total_effects;

           progress_tracker(size_t total)
               : total_effects(total), current_effect(1), current_rows_done(0)
           {}
       };

   public:

       ImageRenderer(size_t threads, Image* in);

       ~ImageRenderer();

       void render(PluginChain& fx, Image* out);

       void setProgressCallback(render_callback_t callback);

   private:

       static void renderRow(ImageShader* fx, 
           Image* in,
           Image* out,
           size_t row, 
           progress_tracker* tracker, 
           render_callback_t callback);


       size_t num_threads;
       Image* in; // input

       render_callback_t progress_callback;
 
   };

}


#endif // __RENDERER_H_