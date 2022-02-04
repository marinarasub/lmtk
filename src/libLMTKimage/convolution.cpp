#include "convolution.h"

namespace image {

    ImageConvolution::ImageConvolution()
        : ImageConvolution(0)
    {}

    ImageConvolution::ImageConvolution(size_t center)
        : ImageConvolution(center, center)
    {}

    ImageConvolution::ImageConvolution(size_t centerX, size_t centerY)
        : ImageConvolution(centerX, centerY, DEFAULT_EDGE_METHOD)
    {}

    ImageConvolution::ImageConvolution(
        size_t centerX, 
        size_t centerY,
        EdgeHandlingMethod edge_method) : ImageShader(edge_method)
    {
        // guarenteed odd number ensures well defined center for kernel
        setKernelSize(centerX, centerY);
        computeKernel();
    }

    void ImageConvolution::operator()(Image& img)
    {
        Image temp = img;
        for (size_t y = 0; y < img.height(); y++)
        {
            for (size_t x = 0; x < img.width(); x++)
            {
                RGBAPixel* p = img.getRGBAPixel(x, y);
                p->set(this->operator()(temp, x, y));
            }
        }
    }

    RGBAPixel ImageConvolution::operator()(const Image& img, size_t x, size_t y)
    {
        return convolution(img, x, y);
    }

    void ImageConvolution::setKernelSize(size_t centerX, size_t centerY)
    {
        size_t sizeX = (2 * centerX) + 1;
        size_t sizeY = (2 * centerY) + 1;
        kernel.resize(sizeY, sizeX);
    }

    void ImageConvolution::computeKernel()
    {
        kernel.setZero();
        normalize();
    }

    RGBAPixel image::ImageConvolution::convolution(
        const Image& img, 
        unsigned int target_x,
        unsigned int target_y)
    {
        // accumulators
        float red = 0, green = 0, blue = 0, alpha = 0;
        for (int y = 0; y < kernel.rows(); y++)
        {
            for (int x = 0; x < kernel.cols(); x++)
            {
                float weight = kernel(y, x);
                if (weight == 0) continue; // faster than retrieval
                int img_x = x + (int)target_x - kernel.rows() / 2;
                int img_y = y + (int)target_y - kernel.cols() / 2;
                red += weight *
                    img.getRGBAPixel(img_x, img_y, edge_method).r;
                green += weight *
                    img.getRGBAPixel(img_x, img_y, edge_method).g;
                blue += weight *
                    img.getRGBAPixel(img_x, img_y, edge_method).b;
                alpha += weight *
                    img.getRGBAPixel(img_x, img_y, edge_method).a;
            }
        }
        return RGBAPixel(red, green, blue, alpha);
    }

    void ImageConvolution::normalize()
    {
        // if the sum is 0, matrix need not be normalized (sum will always be 0)
        if (kernel.sum() == 0) return;
        kernel *= 1.0 / kernel.sum(); // scale matrix by 1 / sum
    }

}
