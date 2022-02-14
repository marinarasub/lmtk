#include "colorinvert.h"

namespace image {

    void ColorInverter::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel ColorInverter::operator()(const Image& img, int x, int y)
    {
        RGBAPixel* p = img.getRGBAPixel(x, y);
        return invert(*p);
    }

    ColorInverter* ColorInverter::clone()
    {
        return new ColorInverter(*this);
    }

    RGBAPixel ColorInverter::invert(RGBAPixel p)
    {
        p.set(1 - p.r, 1 - p.g, 1 - p.b);
        return p;
    }

}