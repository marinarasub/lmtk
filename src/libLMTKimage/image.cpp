#include "image.h"

namespace image {

    // TODO restrict ttoal size < max int at least
    Image::Image()
    {
        pixel_data.width = 0;
        pixel_data.height = 0;
        pixel_data.pixels = nullptr;
    }

    Image::Image(unsigned int w, unsigned int h) : Image()
    {
        setInitialSize(w, h);
        fillSolidColor(rgbcolor::TRANSPARENT);
    }

    Image::Image(const Image& other) : Image()
    {
        copy(other);
    }

    Image::~Image()
    {
        clear();
    }

    Image Image::operator=(const Image& other)
    {
        if (*this != other) copy(other);
        return *this;
    }

    bool Image::operator==(const Image& other) const
    {
        if (this->width() != other.width()) return false;
        if (this->height() != other.height()) return false;
        for (int i = 0; i < size(); i++) {
            if (pixel_data.pixels[i] != other.pixel_data.pixels[i]) return false;
        }
        return true;
    }

    bool Image::operator!=(const Image& other) const
    {
        return !(*this == other);
    }

    unsigned int Image::width() const
    {
        return pixel_data.width;
    }

    unsigned int Image::height() const
    {
        return pixel_data.height;
    }

    // TODO width * hieght may overflow.
    unsigned int Image::size() const
    {
        return width() * height();
    }

    void Image::fillSolidColor(const RGBAPixel& color)
    {
        for (int i = 0; i < size(); i++) {
            pixel_data.pixels[i] = color;
        }
    }

    void Image::fillGradient(const RGBAPixel& color1, const RGBAPixel& color2)
    {
        float r_range = color2.r - color1.r;
        float g_range = color2.g - color1.g;
        float b_range = color2.b - color1.b;
        float a_range = color2.a - color1.a;
        for (size_t y = 0; y < height(); y++)
        {
            float percent = static_cast<float>(y) / height();
            float r_new = color1.r + r_range * percent;
            float g_new = color1.g + g_range * percent;
            float b_new = color1.b + b_range * percent;
            float a_new = color1.a + a_range * percent;
            for (size_t x = 0; x < width(); x++)
            {
                RGBAPixel* p = getRGBAPixel(x, y);
                p->set(r_new, g_new, b_new, a_new);
            }
        }
    }

    void Image::blendNormal(const Image& other)
    {
        size_t max_h = fmin(height(), other.height());
        size_t max_w = fmin(width(), other.width());
        for (size_t y = 0; y < max_h; y++)
        {
            for (size_t x = 0; x < max_w; x++)
            {
                RGBAPixel* blend = other.getRGBAPixel(x, y);
                float blend_alpha = blend->a;
                float blend_trans = 1.0 - blend_alpha;
                RGBAPixel* base = getRGBAPixel(x, y);
                base->set(base->r * blend_trans + blend->r * blend_alpha,
                    base->g * blend_trans + blend->g * blend_alpha,
                    base->b * blend_trans + blend->b * blend_alpha,
                    base->a * blend_trans + blend->a * blend_alpha);
            }
        }
    }

    void Image::resize(unsigned int w, unsigned int h)
    {
        resize(w, h, ResampleMethod::DEFAULT);
    }

    void Image::resize(unsigned int w, unsigned int h, ResampleMethod method)
    {
        if (w <= 0 || h <= 0) throw std::invalid_argument("image size must be positive integer");
        if (pixel_data.pixels == NULL) throw std::invalid_argument("null pixel data");
        Image temp(w, h);
        float ratio_y = height() / static_cast<float>(h); // 1/scale 
        float ratio_x = width() / static_cast<float>(w);
        float pick_x, pick_y;
        for (size_t y = 0; y < h; y++)
        {
            pick_y = y * ratio_y;
            for (size_t x = 0; x < w; x++)
            {
                pick_x = x * ratio_x;
                temp.setRGBAPixel(this->getRGBAPixel(pick_x, pick_y, method), x, y);
            }
        }
        clear();
        *this = temp;
    }

    //void Image::resizeNearestNeighbor(unsigned int w, unsigned int h)
    //{
    //    // guards
    //    if (w <= 0 || h <= 0) throw ERROR;
    //    if (pixel_data.pixels == NULL) throw ERROR;
    //    Image temp(w, h);
    //    float ratio_y = height() / static_cast<float>(h); // 1/scale 
    //    float ratio_x = width() / static_cast<float>(w);
    //    float pick_x, pick_y;
    //    // resize nearest neighbour
    //    for (size_t y = 0; y < h; y++)
    //    {
    //        pick_y = floor(y * ratio_y);
    //        for (size_t x = 0; x < w; x++)
    //        {
    //            pick_x = floor(x * ratio_x);
    //            temp.setRGBAPixel(*this->getRGBAPixel(pick_x, pick_y), x, y);
    //        }
    //    }
    //    clear();
    //    *this = temp;
    //}

    void Image::scale(float scale_x, float scale_y)
    {
        if (scale_x <= 0 || scale_y <= 0) throw std::invalid_argument("scalar must be positive");
        resize(scale_x * width(), scale_y * height());
    }

    void Image::mirror()
    {
        for (size_t y = 0; y < height(); y++)
        {
            for (size_t x = 0; x < width() / 2; x++)
            {
                RGBAPixel* left = getRGBAPixel(x, y);
                RGBAPixel* right = getRGBAPixel(width() - 1 - x, y);
                RGBAPixel temp = *left;
                *left = *right;
                *right = temp; // swap
            }
        }
    }

    RGBAPixel* Image::getRGBAPixel(int x, int y) const
    {
        RGBAPixel* p = pixelAt(x, y);
        if (p == nullptr) throw std::out_of_range("Image:: Pixel index out of range: (" + 
            std::to_string(x) + ", " + 
            std::to_string(y) + ")");
        return p;
    }

    //TODO get pixel with edge case handlers -> extend, mirror, wrap, crop, constant color etc.
    RGBAPixel Image::getRGBAPixel(
        int x,
        int y,
        EdgeHandlingMethod method) const
    {
        //man this is ugly
        int w = static_cast<int>(width());
        int h = static_cast<int>(height());
        switch (method)
        {
        case EdgeHandlingMethod::DEFAULT:
            break;
        case EdgeHandlingMethod::EXTEND:
            if (x < 0) x = 0;
            else if (x >= w) x = w-1;
            if (y < 0) y = 0;
            else if (y >= h) y = h-1;
            break;
        case EdgeHandlingMethod::WRAP: // or TILE
            if (x < 0) x = (x % w) + w;
            if (x >= w) x %= w;
            if (y < 0) y = (y % h) + h;
            if (y >= h) y %= h;
            break;
        case EdgeHandlingMethod::MIRROR: // NOTE: can be out of range (only mirrors once)
            if (x < 0) x = -x;
            else if (x >= w) x = w - (x - w + 2);
            if (y < 0) y = -y;
            else if (y >= h) y = h - (y - h + 2);
            break;
        default:
            throw std::invalid_argument("Invalid Edge Handling Method");
        }
        RGBAPixel* ret = getRGBAPixel(x, y);
        return *ret;
    }

    // TODO choose edge method
    RGBAPixel Image::getRGBAPixel(float x, float y, ResampleMethod method) const
    {
        RGBAPixel ret;
        switch (method)
        {
        case image::ResampleMethod::NEIGHBOR:
            ret = getRGBAPixel(roundf(x), roundf(y), EdgeHandlingMethod::EXTEND);
            break;
        case image::ResampleMethod::BILINEAR:
            ret = bilinearResample(x, y);
            break;
        case image::ResampleMethod::BICUBIC:
            ret = bicubicResample(x, y);
            break;
        default:
            throw std::invalid_argument("Invalid Interpolation Method");
        }
        return ret;
    }

    // get ptr to start of row
    RGBAPixel* Image::getRow(int row_num) const
    {
        return pixelAt(0, row_num);
    }

    bool Image::setRow(RGBAPixel row_pixels[], size_t row_width, int row_num)
    {
        RGBAPixel* row_ptr = getRow(row_num);
        if (!row_ptr) return false;
        size_t max = row_width < width() ? row_width : width();
        for (size_t i = 0; i < max; i++)
        {
            row_ptr[i] = row_pixels[i];
        }
        return true;
    }

    bool Image::setRGBAPixel(const RGBAPixel& color, int x, int y)
    {
        RGBAPixel* target = pixelAt(x, y);
        if (target == nullptr) return false;
        *target = color;
        return true;
    }

    bool Image::setHSLAPixel(const HSLAPixel& color, int x, int y)
    {
        RGBAPixel* target = pixelAt(x, y);
        if (target == nullptr) return false;
        *target = color;
        return true;
    }

    RGBAPixel* Image::pixelAt(int x, int y) const
    {
        if (pixel_data.pixels == NULL) return nullptr;
        if (x < 0 || x >= width() || y < 0 || y >= height()) return nullptr;
        return &pixel_data.pixels[y * width() + x];
    }

    // TODO mipmap, box resample

    // resampling functions (for upscale)
    RGBAPixel Image::bilinearResample(float x, float y) const
    {
        //valid int positions
        float x_floor = floor(x);
        float x_ceil = ceil(x);
        float y_floor = floor(y);
        float y_ceil = ceil(y);
        //weights
        float x_floor_weight = x - x_floor;
        float x_ceil_weight = x_ceil - x;
        float y_floor_weight = y - y_floor;
        float y_ceil_weight = y_ceil - y;
        if (x_floor == x_ceil) { x_floor_weight = 1; x_ceil_weight = 1; }
        if (y_floor == y_ceil) { y_floor_weight = 1; y_ceil_weight = 1; }
        /*std::cout << "AT:" << x << "," << y << " " <<
            x_floor_weight << " " <<
            y_floor_weight << " " <<
            x_ceil_weight << " " <<
            y_ceil_weight << std::endl;*/
            // weights for pixels
        float ll_weight = x_ceil_weight * y_ceil_weight;
        float lr_weight = x_floor_weight * y_ceil_weight;
        float ul_weight = x_ceil_weight * y_floor_weight;
        float ur_weight = x_floor_weight * y_floor_weight;
        // get pixels // todo static cast to int
        RGBAPixel ll = getRGBAPixel(x_floor, y_floor, EdgeHandlingMethod::EXTEND);
        RGBAPixel lr = getRGBAPixel(x_ceil, y_floor, EdgeHandlingMethod::EXTEND);
        RGBAPixel ul = getRGBAPixel(x_floor, y_ceil, EdgeHandlingMethod::EXTEND);
        RGBAPixel ur = getRGBAPixel(x_ceil, y_ceil, EdgeHandlingMethod::EXTEND);
        // pixel avg
        float weights[4] = { ll_weight, lr_weight, ul_weight, ur_weight };
        RGBAPixel parr[4] = { ll, lr, ul, ur };
        RGBAPixel wavg = RGBAPixel::weighted_naverage(parr, weights, 4);

        return wavg;
    }

    RGBAPixel Image::bicubicResample(float x, float y) const
    {
        return RGBAPixel(); // TODO
    }

    std::string Image::to_string()
    {
        return "Width: " + std::to_string(width()) + ", " +
            "Height: " + std::to_string(height()) + ", " +
            "Size: " + std::to_string(size());
    }

    void Image::setInitialSize(int w, int h)
    {
        if (w <= 0 || h <= 0) throw std::invalid_argument("image size must be positive integer");
        if (w > 100000 || h > 100000) throw std::invalid_argument("image too large"); // artificial limit
        pixel_data.width = w;
        pixel_data.height = h;
        pixel_data.pixels = new RGBAPixel[size()];//(RGBAPixel*)malloc(size() * sizeof(RGBAPixel));
        //if (pixel_data.pixels == NULL) throw ERROR;
    }

    void Image::copy(const Image& other)
    {
        clear();
        setInitialSize(other.width(), other.height());
        for (int i = 0; i < size(); i++) {
            pixel_data.pixels[i] = other.pixel_data.pixels[i];
        }
    }

    void Image::clear()
    {
        if (pixel_data.pixels != nullptr)
        {
            delete[] pixel_data.pixels;
            pixel_data.pixels = nullptr;
        }
    }

}

