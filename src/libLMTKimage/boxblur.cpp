#include "boxblur.h"

namespace image {

    BoxBlur::BoxBlur()
        : BoxBlur(DEFAULT_BOXBLUR_RADIUS)
    {}


    BoxBlur::BoxBlur(size_t radius)
        : BoxBlur(radius, radius)
    {
        computeKernel();
    }

    BoxBlur::BoxBlur(size_t radiusX, size_t radiusY)
        : radiusX(radiusX), radiusY(radiusY), Blur(radiusX, radiusY)
    {
    }

    BoxBlur* BoxBlur::operator*(double scalar)
    {
        return new BoxBlur(
            radiusX * scalar, 
            radiusY * scalar);
    }

    BoxBlur* BoxBlur::clone()
    {
        return new BoxBlur(*this);
    }

    void BoxBlur::computeKernel()
    {
        kernel.setOnes();
        normalize();
    }


    BoxBlurHorizontal::BoxBlurHorizontal()
        : BoxBlurHorizontal(DEFAULT_BOXBLUR_RADIUS)
    {}


    BoxBlurHorizontal::BoxBlurHorizontal(size_t radius)
        : hradius(radius), Blur(radius, 0)
    {
        computeKernel();
    }

    BoxBlurHorizontal* BoxBlurHorizontal::operator*(double scalar)
    {
        return new BoxBlurHorizontal(this->hradius * scalar);
    }

    BoxBlurHorizontal* BoxBlurHorizontal::clone()
    {
        return new BoxBlurHorizontal(*this);
    }

    void BoxBlurHorizontal::computeKernel()
    {
        kernel.setOnes();
        normalize();
    }


    BoxBlurVertical::BoxBlurVertical()
        : BoxBlurVertical(DEFAULT_BOXBLUR_RADIUS)
    {}


    BoxBlurVertical::BoxBlurVertical(size_t radius)
        : vradius(radius), Blur(0, radius)
    {
        computeKernel();
    }

    BoxBlurVertical* BoxBlurVertical::operator*(double scalar)
    {
        return new BoxBlurVertical(this->vradius * scalar);
    }

    BoxBlurVertical* BoxBlurVertical::clone()
    {
        return new BoxBlurVertical(*this);
    }

    void BoxBlurVertical::computeKernel()
    {
        kernel.setOnes();
        normalize();
    }

}
