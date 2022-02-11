#include "imageshader.h"

namespace image {

    void ImageShader::operator()(Image& img)
    {
        for (int y = 0; y < img.height(); y++)
        {
            for (int x = 0; x < img.width(); x++)
            {
                img.setRGBAPixel((*this)(img, x, y), x, y);
            }
        }
    }

}
