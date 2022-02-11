#include "tiltshiftblur.h"

namespace image {

    const float TiltShiftBlur::LINEAR_FADE_SPEED = 1.0;
    const float TiltShiftBlur::QUADRATIC_FADE_SPEED = 1/2.0;
    const float TiltShiftBlur::CUBIC_FADE_SPEED = 1/3.0;

    TiltShiftBlur::TiltShiftBlur(int top, int bottom, float gradient, Blur* method)
        : TiltShiftBlur(top, bottom, gradient, QUADRATIC_FADE_SPEED, method)
    {
    }

    TiltShiftBlur::TiltShiftBlur(int top, int bottom, float grad, float fade_speed, Blur* method)
        : top_y(top), bot_y(bottom), grad(grad), fade_exp(1.0/fade_speed)
    {
        if (top_y < 0) throw std::invalid_argument("top_y must be within image height");
        if (bot_y < 0) throw std::invalid_argument("bot_y must be withini image height");
        if (top_y > bot_y) throw std::invalid_argument("top_y must be < bot_y");
        if (grad < 0) throw std::invalid_argument("grad must be > 0");
        //std::cout << grad << std::endl;
        if (!method) throw std::invalid_argument("blur method cannot be null");
        this->blur_method = method->clone();
    }

    TiltShiftBlur::~TiltShiftBlur()
    {
        delete blur_method;
    }

    void TiltShiftBlur::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel TiltShiftBlur::operator()(const Image& img, int x, int y)
    {
        RGBAPixel ret;
        // blur only above and below limits
        if (y <= top_y - grad|| y >= bot_y + grad)
            ret = (*blur_method)(img, x, y);
        // blur gradient
        else
        {
            float amt = fmax((float)top_y - y, (float)y - bot_y); // if within grad
            if (amt > 0)
            {
                amt /= grad;
                Blur* grad_blur = (*blur_method) * std::pow(amt, fade_exp);
                ret = (*grad_blur)(img, x, y);
                delete grad_blur;
            }
            else
            {
                ret = *img.getRGBAPixel(x, y);
            }
        }
        return ret;
    }

    TiltShiftBlur* TiltShiftBlur::clone()
    {
        TiltShiftBlur* copy = new TiltShiftBlur(*this);
        copy->blur_method = this->blur_method->clone();
        return copy;
    }

}