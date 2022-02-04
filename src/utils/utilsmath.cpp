#include "utilsmath.h"

namespace utils {
    namespace math {

        complex real_to_complex(double val)
        {
            return complex(val, 0);
        }

        complexf real_to_complexf(float val)
        {
            return complexf(val, 0);
        }

        double sqr(double val)
        {
            return val * val;
        }

        float sqrf(float val)
        {
            return val * val;
        }

        complex sqr(complex val)
        {
            return val * val;
        }

        complexf sqrf(complexf val)
        {
            return val * val;
        }

       /* double precision_round(double num, int precision)
        {
            bool sign = num < 0;
            double mask = sign * pow(10, -(precision + 1));
            if (fabs(num) < fabs(mask)) return num;
            double remainder = fmod(num, mask);
            bool round_up = sign ? remainder <= mask / 2 : remainder >= mask / 2;
            return num - remainder;
        }*/

        double nsum(double arr[], size_t n)
        {
            double sum = 0;
            for (size_t i = 0; i < n; i++)
            {
                sum += arr[i];
            }
            return sum;
        }

        float nsumf(float arr[], size_t n)
        {
            float sum = 0;
            for (size_t i = 0; i < n; i++)
            {
                sum += arr[i];
            }
            return sum;
        }

        double dist(double x1, double y1, double x2, double y2)
        {
            return sqrt(sqr(x2 - x1) + sqr(y2 - y1));
        }

        double gaussian(double mu, double sigma, double x)
        {
            return 1.0 / (sigma * sqrt(2 * PI)) 
                * pow(EULER, -sqr(x - mu) / (2.0 * sqr(sigma)));
        }

        double gaussian2d(double mu_x, 
            double mu_y,
            double sigma_x,
            double sigma_y, 
            double x, 
            double y)
        {
            double x_exp = -sqr(x - mu_x) / (2.0 * sqr(sigma_x));
            double y_exp = -sqr(y - mu_y) / (2.0 * sqr(sigma_y));
            return 1.0 / (sigma_x * sigma_y * 2 * PI)
                * pow(EULER, x_exp + y_exp);
        }
    }
}