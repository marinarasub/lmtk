#include "bokehblur.h"

namespace image {

    image::BokehBlur::BokehBlur(float radius)
        : BokehBlur(radius, radius)
    {   
    }

    BokehBlur::BokehBlur(float radiusX, float radiusY)
        : radiusX(radiusX), radiusY(radiusY), Blur(ceil(radiusX+1), ceil(radiusY+1))
    {
        if (radiusX == 0) throw std::invalid_argument("radius cannot be 0");
        if (radiusY == 0) throw std::invalid_argument("radius cannot be 0");
        computeKernel();
    }

    BokehBlur* BokehBlur::operator*(double scalar)
    {
        // todo copy edge handle method too
        return new BokehBlur(this->radiusX * scalar, this->radiusY * scalar);
    }

    BokehBlur* BokehBlur::clone()
    {
        return new BokehBlur(*this);
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