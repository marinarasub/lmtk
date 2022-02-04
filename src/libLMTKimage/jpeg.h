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
* @file jpeg.h
* @author marinarasub
* @date December 2021
* @brief Contains the JPEG image class.
*
* The JPG class uses the libjpeg interface for file I/O and compression, and is
* a high level representation of a JPEG image.
* @note file extensions can be .jpg or .jpeg 
*/


#ifndef _LIBLMTKIMAGE_JPEG_H_
#define _LIBLMTKIMAGE_JPEG_H_
#pragma once

#include <stdio.h>
#include <cstring>
#include <stdexcept>
#include <jpeglib.h>
#include "imagefile.h"
#include "../utils/utils.h"


namespace image {

    /**
    * @class JPEG jpeg.h
    * @brief JPEG image class.
    *
    * The JPEG class has all image functionality plus read/write capability, and
    * additional JPEG specific tools.
    * @see Image
    */
    class JPEG : public ImageFile
    {
    public:

        /**
        * Creates a JPEG image of size width * height
        *
        * Calls base class constructor
        * @see Image
        * @param w Width
        * @param h Height
        */
        JPEG(unsigned int w, unsigned int h);

        /**
        * Creates a JPEG in memory from a jpeg/jpg file stored on disk.
        * 
        * @see readFile()
        * @param path Path to file
        * @throws Exception if could not read file
        */
        JPEG(std::string path);

        /**
        * Converts an image to a writable JPEG
        */
        JPEG(const Image& img);

        /**
        * Does nothing right now
        */
        ~JPEG();

        /**
        * Read JPEG file from disk.
        * 
        * Attempt to open file for read, and replaces existing data, if any.
        * Converts byte data from libjpeg to RGBAPixels.
        * @param path Path to file to read
        * @throws An exception if failed to read (i.e. file does not exist)
        */
        void readFile(std::string path) override;

        /**
        * Writes image to new or exisiting JPEG file on disk.
        * 
        * Directory must exist. Converts RGBAPixel data to jpeg byte data for
        * libjpeg.
        * @param Path to write file
        * @throws An exception if failed to write
        */
        void writeFile(std::string path) override;

        // write a copy. if name is same as original append " (n)" for n copies
        // int writeFileCopy(std::string path);

        // hash()

        // !=, == and = copy 

    private:

        /**
        * Converts libjpeg pixel data RGBAPixels.
        *
        * @warning Assumes the row pointers are already allocated
        * @param row_ptrs Array of pointers to each row of byte data of the PNG
        * image that was read from libpng interface
        */
        void row_ptrs_to_pixels(const JSAMPARRAY& row_ptrs);

        /**
        * Converts RGBAPixels to jpeg samples for libjpeg.
        * 
        * @param row_ptr Pointers to row of jpeg sample arrays
        */
        void pixels_to_row_ptrs(JSAMPARRAY& row_ptrs);
    };

}

#endif // _LIBLMTKIMAGE_JPEG_H_

