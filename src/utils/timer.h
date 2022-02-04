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
 * @file timer.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains a basic timer wrapper for standard library chrono
 */

#ifndef _UTILS_TIMER_H_
#define _UTILS_TIMER_H_

#include <chrono>


namespace utils {

	using namespace std::chrono;
    using hrc = high_resolution_clock;

	/**
    * @class Timer "timer.h"
    * @brief Represents a timer 
    */
	class Timer
	{
	public:

        /**
        * Creates a timer object
        */
		Timer();

        /**
        * Starts the timer.
        * 
        * Marks the start time.
        */
		void start();

        /**
        * Gets interval from start time.
        * 
        * @returns Interval from last call to start on *this
        */
		double time(); // return time in s.

		// TODO to string.

        // TODO pause/lap

	private:

		hrc::time_point start_point; /**< saved start absolute time */

		//time_p
	};
}


#endif // _UTILS_TIMER_H_
