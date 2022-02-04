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
 * @file utilsmath.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains various handy math functions
 */

#ifndef _UTILS_UTILSMATH_H_
#define _UTILS_UTILSMATH_H_
#pragma once

#include <math.h>
#include <complex>


namespace utils {

    /**
    * @namespace utils::math
    * @brief contains math utility functions.
    * 
    * In most cases, the functions use cartesian coordinates and conventions in
    * euclidian space
    * x, y, z are used to represent major axes.
    */
    namespace math {

        /**
        * Represents a complex number using doubles.
        */
        typedef std::complex<double> complex;

        /**
        * Represents a complex number using floats.
        */
        typedef std::complex<float> complexf;

        /**
        * The imaginary unit, also known as i, sqrt(-1).
        */
        constexpr complex IMAGINARY_UNIT = complex(0, 1);

        /**
        * The imaginary unit, also known as i, sqrt(-1) using float32.
        */
        constexpr complexf IMAGINARY_UNIT_F = complexf(0, 1);

        /**
        * Euler's number.
        */
        const double EULER = std::exp(1);

        /**
        * Pi to a decent precision.
        */
        constexpr double PI = 3.141592653589793238463;

        /**
        * Convert a number to a complex type.
        * 
        * @param val Number to convert
        * @return Converted complex number
        */
        complex real_to_complex(double val);

        /**
        * Convert a number to a complex type, using float.
        *
        * @param val Number to convert
        * @return Converted complex number
        */
        complexf real_to_complexf(float val);

        /**
        * Returns the square of a number.
        * 
        * @param val Number to square
        * @return Square of number, n * n
        */
        double sqr(double val);

        /**
        * Returns the square of a number, for float.
        *
        * @param val Number to square
        * @return Square of number, n * n as float
        */
        float sqrf(float val);

        /**
        * Squares a complex number.
        * 
        * @param val Complex number to square
        * @return Squared complex number
        */
        complex sqr(complex val);

        /**
        * Squares a complex number, for float.
        *
        * @param val Complex number to square
        * @return Squared complex number
        */
        complexf sqrf(complexf val);

        /**
        * Sums the number in an array of size n.
        * 
        * @param arr Array of numbers
        * @param n Size of array
        * @return Sum of all elements up to index n-1
        */
        double nsum(double arr[], size_t n);

        /**
        * Sums the number in an array of size n, for float32.
        *
        * @param arr Array of numbers
        * @param n Size of array
        * @return Sum of all elements up to index n-1
        */
        float nsumf(float arr[], size_t n);

        //double stdev();
        //double mean();
        //double median();

        /**
        * Return 2D distance between two points.
        * 
        * Uses euclidian distance
        * @param x1 X-position of first coordinate
        * @param y1 Y-position of first coordinate
        * @param x2 X-position of second coordinate
        * @param y2 Y-position of second coordinate
        * @return Euclidian distance between (x1, x2) and (y2, y1)
        */
        double dist(double x1, double y1, double x2, double y2);

        /**
        * Compute the gaussian value of a variable x with mean and standard
        * deviation.
        * 
        * Gaussian is normalized so integral is 1.
        * @param mean Mean value of gaussian
        * @param sigma Standard deviation of gaussian
        * @param x Value of apply gaussian to
        * @return Gaussian of x using N(mean, sigma)
        */
        double gaussian(double mean, double sigma, double x);

        /**
        * Compute the 2D gaussian value of a variable x with means and standard
        * deviations.
        *
        * Gaussian is normalized so integral is 1.
        * @param mean_x Mean x value of gaussian
        * @param mean_y Mean y of gaussian
        * @param sigma_x Standard deviation in x of gaussian
        * @param sigma_y Standard deviation in y of gaussian
        * @param x X location of number
        * @param y Y location of number
        * @return Gaussian at (x, y)
        */
        double gaussian2d(
            double mean_x,
            double mean_y,
            double sigma_x,
            double sigma_y,
            double x,
            double y);
    }
}

#endif // _UTILS_UTILSMATH_H_