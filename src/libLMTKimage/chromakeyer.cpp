#include "chromakeyer.h"

namespace image {

    ChromaKeyer::ChromaKeyer(RGBAPixel target)
        : ChromaKeyer(target, DEFAULT_TOLERANCE)
    {
    }

    ChromaKeyer::ChromaKeyer(RGBAPixel target, float tol) : target(target)
    {
        threshold = fmin(sqrt(3), fmax(0.0, tol)); 
        // Note: sqrt3 is the max distance. May choose to normalize max tol to 1
        // in the future.
    }

    void ChromaKeyer::operator()(Image& img)
    {
        ImageShader::operator()(img);
    }

    RGBAPixel ChromaKeyer::operator()(const Image& img, int x, int y)
    {
        RGBAPixel* p = img.getRGBAPixel(x, y);
        float dist = p->dist(target);
        RGBAPixel res(*p);
        if (dist <= threshold) p->setAlpha(0);
        return res;
    }

    ChromaKeyer* ChromaKeyer::clone()
    {
        return new ChromaKeyer(*this);
    }

}
