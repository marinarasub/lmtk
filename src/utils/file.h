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
 * @file file.h
 * @author marinarasub
 * @date January 2022
 * @brief Utility class for file handling
 */

#ifndef _UTILS_FILE_H_
#define _UTILS_FILE_H_
#pragma once

#include <string>



namespace utils {

    // WIP
	// gets file extension without dot
	// no regard for validity of path or extension
	std::string file_extension(std::string path);

}


#endif // _UTILS_FILE_H_