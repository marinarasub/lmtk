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
 * @file utilsstring.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains handy string utilities.
 */

#ifndef _UTILS_UTILSSTRING_H_
#define _UTILS_UTILSSTRING_H_
#pragma once

#include <string>


namespace utils {

	// removes all spaces in string
	std::string remove_spaces(std::string in);

	// counts number of given char in string 
	size_t count_char(std::string in, char c);

}


#endif // _UTILS_UTILSSTRING_H_