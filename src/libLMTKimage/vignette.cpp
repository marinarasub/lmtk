#include "vignette.h"

namespace image {

    const RGBAPixel VignetteShader::DEFAULT_FADE_COLOR = rgbcolor::BLACK;

    VignetteShader::VignetteShader(float rX, float rY, float fade)
        : VignetteShader(rX, rY, fade, DEFAULT_FADE_COLOR)
        
    {
    }

    VignetteShader::VignetteShader(float rX, float rY, float fade, RGBAPixel color)
        : radiusX(rX), radiusY(rY), gradient(fade), fade_color(color), ImageShader()
    {
    }

    void VignetteShader::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    VignetteShader* VignetteShader::clone()
    {
        return new VignetteShader(*this);
    }

    RGBAPixel VignetteShader::operator()(const Image& img, int x, int y)
    {
        using namespace utils::math;
        float center_x = static_cast<float>(img.width()) / 2;
        float center_y = static_cast<float>(img.height()) / 2;
        RGBAPixel orig = *img.getRGBAPixel(x, y);
        float elipse = sqr(x - center_x) / sqr(radiusX) + sqr(y - center_y) / sqr(radiusY);
        if (elipse > 1)
        {
            float fade_weight = (elipse - 1) * gradient;
            //fade_weight = std::fmin(std::fmax(fade_weight, 0), 1); // clamp to 1
            return RGBAPixel::weighted_average(orig, fade_color, 1 - fade_weight, fade_weight);
        }
        else
            return orig;
    }

}