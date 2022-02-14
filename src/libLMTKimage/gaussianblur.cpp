#include "gaussianblur.h"

namespace image {

    float sigmaTolerance(float zscore)
    {
        return utils::math::gaussian(0, 1, zscore);
    }

    // warning: stdev = 0 means div by 0
    // TODO seperate stdev for x, y
    // TODO pick quality (tolerance)
    GaussianBlur::GaussianBlur(float stdev)
        : GaussianBlur(stdev, stdev)
    {
    }

    GaussianBlur::GaussianBlur(float stdevX, float stdevY)
        : GaussianBlur(stdevX, stdevY, sigmaTolerance(3), sigmaTolerance(3))
    {
    }


    GaussianBlur::GaussianBlur(float stdevX, float stdevY, float tolX, float tolY)
        : sigmaX(stdevX), sigmaY(stdevY), Blur()
    {
        if (stdevX <= 0 || stdevY <= 0) throw std::invalid_argument("stdev must be larger than 0");
        if (tolX <= 0 || tolY <= 0) throw std::invalid_argument("tolerance must be larger than 0");
        size_t x = 1, y = 1;
        //constexpr size_t MAX_LIMIT = 1000; // artificial limit so the kernel isnt WAY too big
        while (utils::math::gaussian(0, stdevY, static_cast<float>(y)) > tolY) y++;
        while (utils::math::gaussian(0, stdevX, static_cast<float>(x)) > tolX) x++;
        setKernelSize(x-1, y-1);
        computeKernel();
    }

    GaussianBlur* GaussianBlur::operator*(double scalar)
    {
        // TODO store tolerance too ?
        return new GaussianBlur(this->sigmaX * scalar, this->sigmaY * scalar);
    }

    GaussianBlur* GaussianBlur::clone()
    {
        return new GaussianBlur(*this);
    }

    void GaussianBlur::normalize()
    {
        ImageConvolution::normalize();
    }

    void GaussianBlur::computeKernel()
    {
        // avoid fp error
        if (kernel.size() == 1)
        {
            kernel.setOnes();
            return;
        }

        for (int x = 0; x < kernel.cols(); x++)
        {
            for (int y = 0; y < kernel.rows(); y++)
            {
                kernel(y, x) =
                    utils::math::gaussian2d(
                        static_cast<float>(kernel.cols()) / 2,
                        static_cast<float>(kernel.rows()) / 2,
                        sigmaX,
                        sigmaY,
                        x,
                        y);
            }
        }
        
        normalize();
    }


    GaussianBlurHorizontal::GaussianBlurHorizontal(float stdev)
        : GaussianBlurHorizontal(stdev, sigmaTolerance(3))
    {
    }

    GaussianBlurHorizontal::GaussianBlurHorizontal(float stdev, float tol)
        : sigma(stdev), Blur()
    {
        if (stdev <= 0) throw std::invalid_argument("stdev must be larger than 0");
        if (tol <= 0) throw std::invalid_argument("tolerance must be larger than 0");
        size_t x = 1;
        while (utils::math::gaussian(0, stdev, static_cast<float>(x)) > tol) x++;
        setKernelSize(x-1, 0);
        computeKernel();
    }

    void GaussianBlurHorizontal::normalize()
    {
        ImageConvolution::normalize();
    }

    GaussianBlurHorizontal* GaussianBlurHorizontal::operator*(double scalar)
    {
        return new GaussianBlurHorizontal(this->sigma * scalar);
    }

    GaussianBlurHorizontal* GaussianBlurHorizontal::clone()
    {
        return new GaussianBlurHorizontal(*this);
    }

    void GaussianBlurHorizontal::computeKernel()
    {
        // avoid fp error
        if (kernel.size() == 1)
        {
            kernel.setOnes();
            return;
        }

        for (int x = 0; x < kernel.cols(); x++)
        {
            kernel(0, x) =
                utils::math::gaussian(
                    static_cast<float>(kernel.cols()) / 2,
                    sigma,
                    x);
        }
        normalize();
    }


    GaussianBlurVertical::GaussianBlurVertical(float stdev)
        : GaussianBlurVertical(stdev, sigmaTolerance(3))
    {
    }

    GaussianBlurVertical::GaussianBlurVertical(float stdev, float tol)
        : sigma(stdev), Blur()
    {
        if (stdev <= 0) throw std::invalid_argument("stdev must be larger than 0");
        if (tol <= 0) throw std::invalid_argument("tolerance must be larger than 0");
        size_t y = 1;
        while (utils::math::gaussian(0, stdev, static_cast<float>(y)) > tol) y++;
        setKernelSize(0, y-1);
        computeKernel();
    }

    GaussianBlurVertical* GaussianBlurVertical::operator*(double scalar)
    {
        return new GaussianBlurVertical(this->sigma * scalar);
    }

    GaussianBlurVertical* GaussianBlurVertical::clone()
    {
        return new GaussianBlurVertical(*this);
    }

    void GaussianBlurVertical::normalize()
    {
        ImageConvolution::normalize();
    }

    void GaussianBlurVertical::computeKernel()
    {
        // avoid fp error
        if (kernel.size() == 1)
        {
            kernel.setOnes();
            return;
        }

        for (int y = 0; y < kernel.rows(); y++)
        {
            kernel(y, 0) =
                utils::math::gaussian(
                    static_cast<float>(kernel.rows()) / 2,
                    sigma,
                    y);
        }
        normalize();
    }

}