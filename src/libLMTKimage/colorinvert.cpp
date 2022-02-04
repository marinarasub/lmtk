#include "colorinvert.h"

namespace image {

    void ColorInvertShader::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel ColorInvertShader::operator()(const Image& img, size_t x, size_t y)
    {
        RGBAPixel* p = img.getRGBAPixel(x, y);
        return invert(*p);
    }

    RGBAPixel ColorInvertShader::invert(RGBAPixel p)
    {
        p.set(1 - p.r, 1 - p.g, 1 - p.b);
        return p;
    }

}