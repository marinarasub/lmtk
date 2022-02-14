#include "rotate.h"

namespace image {

    ImageRotate::ImageRotate(float deg)
    {
        // inverse rotation - get original points to sample from
        radians = deg * utils::math::PI / 180;
        // TODO move to utils math
        rot_matrix <<
            std::cos(radians), -std::sin(radians),
            std::sin(radians), std::cos(radians);
        //std::cout << inv_rotation_matrix << std::endl;
        // why doesn't initializer list work??
    }

    void ImageRotate::operator()(Image& img)
    {
        // calculate new image size
        std::pair<int, int> new_size = bouding_rect(img.width(), img.height());
        Image temp(new_size.first, new_size.second);

        for (int y = 0; y < temp.height(); y++)
        {
            for (int x = 0; x < temp.width(); x++)
            {
                int w_diff = temp.width() - img.width();
                int h_diff = temp.height() - img.height();
                temp.setRGBAPixel((*this)(img, x - w_diff / 2, y - h_diff / 2), x, y);
                //temp.setRGBAPixel((*this)(img, x, y), x, y);
            }
        }
        img = temp;
    }

    RGBAPixel ImageRotate::operator()(const Image& img, int x, int y)
    {
        float center_x = static_cast<float>(img.width()) / 2;
        float center_y = static_cast<float>(img.height()) / 2;
        Eigen::Vector2f pick = { static_cast<float>(x) - center_x, static_cast<float>(y) - center_y };
        Eigen::Vector2f sample = rot_matrix * pick;
        float samp_x = sample(0) + center_x;
        float samp_y = sample(1) + center_y;
        if (samp_x < 0 || samp_y < 0 || samp_x >= static_cast<float>(img.width()) || samp_y >= static_cast<float>(img.height()))
            return RGBAPixel();
        else
            return img.getRGBAPixel(samp_x, samp_y, ResampleMethod::DEFAULT);
    }

    ImageRotate* ImageRotate::clone()
    {
        return new ImageRotate(*this);
    }

    std::pair<int, int> ImageRotate::bouding_rect(int x, int y)
    {
        Eigen::Matrix2f size_mat = rot_matrix.cwiseAbs();
        Eigen::Vector2f size_vec;
        size_vec = {
            static_cast<float>(x),
            static_cast<float>(y)
        };  
        Eigen::Vector2f result = size_mat * size_vec;
        return std::make_pair<int, int>(
            static_cast<int>(std::floor(std::fabs(result[0]))), 
            static_cast<int>(std::floor(std::fabs(result[1])))
            );
    }

}