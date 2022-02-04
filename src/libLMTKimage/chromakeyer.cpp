#include "chromakeyer.h"

namespace image {

    ChromaKeyShader::ChromaKeyShader(RGBAPixel target)
        : ChromaKeyShader(target, DEFAULT_TOLERANCE)
    {
    }

    ChromaKeyShader::ChromaKeyShader(RGBAPixel target, float tol) : target(target)
    {
        threshold = fmin(sqrt(3), fmax(0.0, tol)); 
        // Note: sqrt3 is the max distance. May choose to normalize max tol to 1
        // in the future.
    }

    void ChromaKeyShader::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel ChromaKeyShader::operator()(const Image& img, size_t x, size_t y)
    {
        RGBAPixel* p = img.getRGBAPixel(x, y);
        float dist = p->dist(target);
        RGBAPixel res(*p);
        if (dist <= threshold) p->setAlpha(0);
        return res;
    }

}
