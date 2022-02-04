/*/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in libLMTKimage, the image library for LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

 /**
 * @file imagefile.h
 * @author marinarasub
 * @date January 2022
 * @brief File containing base class for write/readable image file
 */


#ifndef _LIBLMTKIMAGE_IMAGEFILE_H_
#define _LIBLMTKIMAGE_IMAGEFILE_H_
#pragma once

#include <string>
#include "image.h"


namespace image {

	/**
    * @class ImageFile "imagefile.h"
    * @brief class for read/writeable image file. 
    * 
    * Essentially a interface containing abstract functions for image IO
    */
	class ImageFile : public Image
	{

	public:

        /**
        * Virtual destructor. empty.
        */
		virtual ~ImageFile() {}

        /**
        * Abstract function for reading an image into memory.
        * 
        * @param path Path to file
        */
		virtual void readFile(std::string path) = 0;

        /**
        * Abstract function for writing an image to disk.
        * 
        * @param path Path to file
        */
		virtual void writeFile(std::string path) = 0;

	protected:

        /**
        * Constructs and ImageFile.
        * 
        * Calls base Image constructor
        * @see Image
        */
		ImageFile() : Image() {}

        /**
        * Creates an image file of size w, h
        * 
        * Call base Image constructor
        * @see Image
        * @param w Width
        * @param h Height
        */
		ImageFile(unsigned int w, unsigned int h) : Image(w, h) {}

        /**
        * Converts an image to to a image file.
        * 
        * @param other Image to convert to image file
        */
		ImageFile(const Image& other) : Image(other) {}

		//ImageFile(const ImageFile &other) : Image(other) {}

	};

}

#endif // _LIBLMTKIMAGE_IMAGEFILE_H_