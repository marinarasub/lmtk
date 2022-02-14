#include "grayscale.h"

namespace image {

    void GrayScaleShader::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel GrayScaleShader::operator()(const Image& img, int x, int y)
    {
        RGBAPixel* p = img.getRGBAPixel(x, y);
        return greyScale(*p);
    }

    GrayScaleShader* GrayScaleShader::clone()
    {
        return new GrayScaleShader(*this);
    }

    RGBAPixel GrayScaleShader::greyScale(RGBAPixel p)
    {
        float avg = (p.r + p.g + p.b) / 3;
        p.set(avg, avg, avg);
        return p;
    }

}