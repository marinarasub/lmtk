#include "sharpen.h"

namespace image {

    image::ImageSharpen::ImageSharpen()
        : ImageSharpen(1)
    {
        computeKernel();
    }

    ImageSharpen::ImageSharpen(float amt)
        : amount(amt), ImageConvolution(SHARP_CENTER)
    {
        computeKernel();
    }

    ImageSharpen* ImageSharpen::clone()
    {
        return new ImageSharpen(*this);
    }

    // assumes kernel is 3x3
    void ImageSharpen::computeKernel()
    {
        //surrounding
        kernel(kernel.rows() / 2 - 1, kernel.cols() / 2) = -amount;
        kernel(kernel.rows() / 2 + 1, kernel.cols() / 2) = -amount;
        kernel(kernel.rows() / 2, kernel.cols() / 2 - 1) = -amount;
        kernel(kernel.rows() / 2, kernel.cols() / 2 + 1) = -amount;

        //middle
        kernel(kernel.rows() / 2, kernel.cols() / 2) = 4 * amount + 1;

    }

}
