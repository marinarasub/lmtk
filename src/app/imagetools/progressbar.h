/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in the LMTKimage console app.
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

#ifndef __PROGRESSBAR_H_
#define __PROGRESSBAR_H_

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>
#include <stdexcept>

// Allow ANSI escape on Windows
#if defined(_WIN32) || defined(_WIN64)
    #ifndef _WINDOWS
        #define _WINDOWS
    #endif
    #include <windows.h>
        #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
        #endif
    #define _WINDOWS_ANSI()                                         \
    do {                                                            \
        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);              \
        DWORD dw;                                                   \
        GetConsoleMode(hout, &dw);                                  \
        if (!SetConsoleMode(                                        \
            hout,                                                   \
            dw | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) exit(-1);     \
    } while(0)
#endif

namespace progressbar {

    const std::string CLEAR = "\x1B[0J";
    const std::string CLEARSAVED = "\x1B[3J";
    const std::string CLEARLINE = "\x1B[2K";
    const std::string YELLOW = "\x1B[33m";
    const std::string GREEN = "\x1B[32m";
    const std::string RED  = "\x1B[31m";
    const std::string RESET = "\x1B[0m";
    const std::string BLINK = "\x1B[5m";
    const std::string CURSORRESET = "\x1B[0G";

    // TODO the output is well... interesting when the bar is too wide for the
    // console. Figure out a way to detect console width and truncate 
    /**
    * Build a progress bar string with ANSI clear and color.
    * 
    * @return Progress bar string
    */
    std::string getProgressBar(double percent, bool failed);

}

#endif // __PROGRESSBAR_H_ 