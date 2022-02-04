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
        : ImageConvolution(radiusX, radiusY)
    {
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
        : ImageConvolution(radius, 0)
    {
        computeKernel();
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
        : ImageConvolution(0, radius)
    {
        computeKernel();
    }

    void BoxBlurVertical::computeKernel()
    {
        kernel.setOnes();
        normalize();
    }

}
