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
* @file png.h
* @author marinarasub
* @date December 2021
* @brief Contains the PNG image class.
*
* The PNG class uses the libpng interface for file I/O and compression, and is
* a high level representation of a PNG image.
*/


#ifndef _LIBLMTKIMAGE_PNG_H_
#define _LIBLMTKIMAGE_PNG_H_
#pragma once

//#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <vector>
#include <png.h>
#include "imagefile.h"
#include "../utils/utils.h"

/**
* @constexpr PNG_HEADER_BYTES
* The number of header bytes read when comparing the file header
*/
constexpr size_t PNG_HEADER_BYTES = 8;

namespace image {

    // TODO right now if only writes 8bit channel RGBA, allow more options
    // TODO PNG info (date author etc) struct or class or hashmap.
    /**
    * @class PNG png.h
    * @brief PNG image class.
    *
    * The PNG class has all image functionality plus read/write capability, and
    * additional PNG specific tools.
    * @see Image
    */
    class PNG : public ImageFile
    {
    private:
        // FILE* file;
        // image info
    public:
        // TODO instantiate PNG info as well.
        /**
        * Creates a PNG image of size width * height.
        *
        * Calls base class constructor
        * @see Image
        * @param w Width
        * @param h Height
        */
        PNG(unsigned int w, unsigned int h);

        // TODO instantiate PNG info as well; exception
        /**
        * Creates a PNG from a file
        *
        * Creates a PNG file and converts all image data to the representation in
        * the Image and PNG classes.
        * @see Image
        * @see readFile();
        * @param path Path of file to open
        * @throw Exception if readFile() throws an exception
        */
        PNG(std::string path);

        // TODO spec
        // copy image to saveable png
        PNG(const Image& other);

        // TODO it is here for future use
        /**
        * Right now it does nothing.
        */
        ~PNG() override;

        // TODO == != operator etc.

        // TODO return bool, use exceptions instead of return codes
        /**
        * Read PNG data from a file from disk
        *
        * Attempts to open and replace existing PNG data if the file given is a
        * valid PNG. Then converts all byte data from the libpng to RGBA pixels.
        * @see isFilePNG()
        * @see RGBAPixel
        * @param path Path of file to open
        * @throws Invalid argument exception if the file is not a PNG or does not exist
        * @throws An exception if failed to read // TODO
        */
        void readFile(std::string path) override;

        // TODO append .png if path is not already .png end
        /**
        * Writes the PNG to a file.
        *
        * Attempts to create/open a file if the directory exists, then reverse
        * pixel data into byte data for libpng to use.
        * @see RGBAPixel
        * @note libpng handles compression
        * @param path Path of file to open
        * @throws Invalid argument exception if the file is not a PNG // TODO
        * @throws An exception filed to write // TODO
        */
        void writeFile(std::string path) override;

        // TOD write a copy to same path as read. if name is same as original append 
        // " (n)" for nth copy
        // int writeFileCopy(std::string path);

        // TODO hash()

        // TODO !=, == and = copy override


    private:
        // TODO do not return int codes, either use enum or exceptions + bool return

        /**
        * Performs quick check to see if file is a PNG.
        *
        * Reads the header (8 bytes) of the given file and compares it to that of a
        * PNG file using libpng.
        * @warning If a file happens to the same header as a PNG signature, it is
        * interpreted as a PNG
        * @return True if the file header matches a PNG, false otherwise
        * @param fp Pointer to the file
        */
        bool isFilePNG(FILE* fp);

        /**
        * Creates structs used by the libpng interface for file read.
        *
        * @note Consult libpng for more details
        * @param png_p Pointer to png_struct
        * @param info_p Pointer to png_info struct
        * @param end_info_p Pointer to png_info struct for end of file info (after
        * pixel data is stored)
        * @return True if creation succeeded, else false
        */
        bool create_png_read_structs(png_structp& png_p, png_infop& info_p, png_infop& end_info_p);

        /**
        * Creates structs used by the libpng interface for file write.
        *
        * @note Consult libpng for more details
        * @param png_p Pointer to png_struct
        * @param info_p Pointer to png_info struct
        * @return Status of creation
        */
        bool create_png_write_structs(png_structp& png_p, png_infop& info_p);

        // TODO process png info and bit depth etc. 
        /**
        * Read and process the metadata of the PNG image.
        *
        * Converts the PNG format to RGBA and initializes the pixel array in memory.
        * @note Consult libpng for more details
        * @param png_p Pointer to png_struct
        * @param info_p Pointer to png_info struct
        * @return Status of info read
        */
        int process_png_info(png_structp& png_p, png_infop& info_p);

        /**
        * Writes the PNG info to the libpng info struct.
        *
        * Sets the necessary metadata (IHDR, date etc.) for libpng to create the PNG
        * file
        * @note Consult libpng for more details
        * @param png_p Pointer to png_struct
        * @param info_p Pointer to png_info struct
        * @return Status of info write
        */
        int write_png_info(png_structp& png_p, png_infop& info_p);

        /**
        * Read and process the pixel byte data of the image.
        *
        * @see row_ptrs_to_pixels()
        * @note Consult libpng for more details
        * @param png_p Pointer to png_struct
        * @param info_p Pointer to png_info struct
        * @return Status of pixel data read
        */
        int process_png_pixels(png_structp& png_p, png_infop& info_p);

        /**
        * Writes the image data to the libpng png struct.
        *
        * @see pixels_to_row_ptrs()
        * @note Consult libpng for more details
        * @param png_p Pointer to png_struct
        * @param info_p Pointer to png_info struct
        * @return Status of pixel data write
        */
        int write_png_pixels(png_structp& png_p, png_infop& info_p);

        /**
        * Converts pixel data from libpng to PNG class.
        *
        * @warning Assumes the row pointers are already allocated
        * @param row_ptrs Array of pointers to each row of byte data of the PNG
        * image that was read from libpng interface
        */
        void row_ptrs_to_pixels(const png_bytepp& row_ptrs);

        /**
        * Converts PNG class pixel data to byte data for libpng.
        *
        * @warning Assumes the row pointers are already allocated
        * @param row_ptrs Array of pointers to each row of byte data to write to
        * for libpng interface
        */
        void pixels_to_row_ptrs(png_bytepp& row_ptrs);

    };

}

#endif // _LIBLMTKIMAGE_PNG_H_