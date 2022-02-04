#include "bokehblur.h"

namespace image {

    image::BokehBlur::BokehBlur(float radius)
        : BokehBlur(radius, radius)
    {   
    }

    BokehBlur::BokehBlur(float radiusX, float radiusY)
        : radiusX(radiusX), radiusY(radiusY), ImageConvolution(ceil(radiusX+1), ceil(radiusY+1))
    {
        computeKernel();
    }

    
    void image::BokehBlur::computeKernel()
    {
        int center_x = (kernel.cols() / 2);
        int center_y = (kernel.rows() / 2);

        using namespace utils::math;

        for (int y = 0; y < kernel.rows(); y++)
        {
            for (int x = 0; x < kernel.cols(); x++)
            {
                // use implicit equation for elipse
                double elipse = sqr(x - center_x) / sqr(radiusX) + sqr(y - center_y) / sqr(radiusY);
                double thickness = 1 / fmin(radiusX, radiusY);
                double err = (elipse - 1) / thickness;
                kernel(y, x) = elipse <= 1 ?
                    1.0 : (err < 1) ? (1 - err) : 0;
            }
        }
        normalize();

    }

}