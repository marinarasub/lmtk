/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in libLMTKimage, the image library for LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

 /**
 * @file pluginchain.h
 * @author marinarasub
 * @date January 2022
 * @brief Header file for a ordered list of effects to apply to an image.
 */

#ifndef _LIBLMTKIMAGE_PLUGINCHAIN_H_
#define _LIBLMTKIMAGE_PLUGINCHAIN_H_
#pragma once

#include <vector>
#include <list>
#include "imageshader.h"


namespace image {

    /**
    * @class PluginChain "pluginchain" 
    * @brief Class for applying multiple effects to an image, in order.
    * 
    * Maintains a ordered list of image effects to apply to an image.
    * Individual effects can be accessed or you can apply them all at once.
    * @see ImageShader
    */
    class PluginChain
    {
    public:

        /**
        * Creates an empty plugin chain.
        */
        PluginChain() {}

        /**
        * / nothing /
        * @note Free memory yourself.
        */
        ~PluginChain();

        /**
        * Applies every effect on an image, in order.
        * 
        * @param img Image to apply effects to
        */
        virtual void operator()(Image &img);

        // TODO throw? or let vector throw
        /**
        * Access the ith effect in the plugin chain
        * 
        * @param i Index of effect to access
        * @return Reference to image shader pointer at index i
        */
        ImageShader*& operator[](size_t i);

        /**
        * Add an effect to the plugin chain, n times.
        * 
        * @param fx Effect to add
        * @param passes Number of times to apply the effect in sequence
        */
        void addEffect(ImageShader* fx, size_t passes);

        /**
        * Add an effect to plugin chain.
        *
        * Adds the effect once.
        * @param fx Effect to add
        */
        void addEffect(ImageShader *fx);

        /**
        * Add effect at position i in chain, n times
        * 
        * @param fx Effect to add
        * @param passes number of times to add fx
        * @param idx Index to insert at
        */
        void addEffect(ImageShader *fx, size_t passes, size_t idx);

        /**
        * Add multiple effects to plugin chain.
        *
        * Adds all effects if vector.
        * @param fx Effects to add
        */
        void addEffects(std::vector<ImageShader*> fx);

        /**
        * Remove effect from fx, if exists and not null
        */
        void removeEffect(ImageShader* fx);

        /**
        * Remove effect at index i, if exists
        */
        void removeEffect(size_t index);

        /**
        * Returns the number of effects in the plugin chain
        * 
        * @return The size of the effect chain
        */
        size_t size();

        /**
        * Check if the plugin chain is empty 
        * 
        * @return True if it is empty, false otherwise
        */
        bool empty();

    private:

        std::list<ImageShader*> chain; /**< internal list of effects */

        //size_t completed;

    };

    // TODO ostream, tostring

}

#endif // _LIBLMTKIMAGE_PLUGINCHAIN_H_