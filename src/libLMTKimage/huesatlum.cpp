#include "huesatlum.h"

namespace image {

    image::HueSatLumAdjust::HueSatLumAdjust(float hue, float sat, float lum)
        : hue_shift(hue), sat_multiplier(sat), lum_multiplier(lum)
    {
    }

    void HueSatLumAdjust::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel HueSatLumAdjust::operator()(const Image& img, size_t x, size_t y)
    {
        RGBAPixel* p = img.getRGBAPixel(x, y);
        HSLAPixel adj = *p;
        adj.set(adj.h + hue_shift,
            adj.s * sat_multiplier,
            adj.l * lum_multiplier);
 
        return RGBAPixel(adj);
    }

}