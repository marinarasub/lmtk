#include "imageshader.h"

namespace image {

    void ImageShader::operator()(Image& img)
    {
        for (size_t y = 0; y < img.height(); y++)
        {
            for (size_t x = 0; x < img.width(); x++)
            {
                img.setRGBAPixel((*this)(img, x, y), x, y);
            }
        }
    }

}
