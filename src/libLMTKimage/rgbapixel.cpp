#include "rgbapixel.h"

namespace image {

    RGBAPixel RGBAPixel::average(RGBAPixel p1, RGBAPixel p2)
    {
        return weighted_average(p1, p2, 1, 1);
    }

    // will trust user count
    RGBAPixel RGBAPixel::naverage(RGBAPixel pixels[], size_t count)
    {
        float r = 0, b = 0, g = 0, a = 0;
        for (size_t i = 0; i < count; i++)
        {
            r += pixels[i].r;
            g += pixels[i].g;
            b += pixels[i].b;
            a += pixels[i].a;
        }
        if (count != 0) {
            float n = static_cast<float>(count);
            r /= n;
            g /= n;
            b /= n;
            a /= n;
        }
        return RGBAPixel(r, g, b, a);
    }


    RGBAPixel RGBAPixel::weighted_average(RGBAPixel p1, RGBAPixel p2, float w1, float w2)
    {
        float total_weight = w1 + w2;
        float r = (w1 * p1.r + w2 * p2.r);
        float g = (w1 * p1.g + w2 * p2.g);
        float b = (w1 * p1.b + w2 * p2.b);
        float a = (w1 * p1.a + w2 * p2.a);
        if (total_weight != 0)
        {
            r /= total_weight;
            g /= total_weight;
            b /= total_weight;
            a /= total_weight;
        }
        return RGBAPixel(r, g, b, a);
    }

    RGBAPixel RGBAPixel::weighted_naverage(RGBAPixel pixels[], float weights[], size_t count)
    {
        float total_weight = utils::math::nsumf(weights, count);
        float r = 0, g = 0, b = 0, a = 0;
        for (size_t i = 0; i < count; i++)
        {
            r += weights[i] * pixels[i].r;
            g += weights[i] * pixels[i].g;
            b += weights[i] * pixels[i].b;
            a += weights[i] * pixels[i].a;
        }
        if (total_weight != 0)
        {
            r /= total_weight;
            g /= total_weight;
            b /= total_weight;
            a /= total_weight;
        }
        return RGBAPixel(r, g, b, a);
    }

    RGBAPixel::RGBAPixel() 
        : RGBAPixel(0, 0, 0, 0)
    {
        
    }

    RGBAPixel::RGBAPixel(float r, float g, float b)
        : RGBAPixel(r, g, b, 1.0)
    {
    }

    // direct float constructor as percent value [0, 1]
    RGBAPixel::RGBAPixel(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {
        clampRGBA();
    }

    // uses max int
    // pass in bit depth to know what max divior should be, otherwise assumes 8 bit channels
    // max bit depth is 32, if > 32 clip.
    RGBAPixel::RGBAPixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a, uint8_t bit_depth)
    {
        // assume sizeof r == g == b == a
        float max = static_cast<float>(utils::uint_max_val(bit_depth));
        this->r = static_cast<float>(r) / max;
        this->g = static_cast<float>(g) / max;
        this->b = static_cast<float>(b) / max;
        this->a = static_cast<float>(a) / max;
        clampRGBA();
    }

    RGBAPixel::RGBAPixel(const HSLAPixel& hsl)
    {
        color::rgb_color rgb = color::hsl_to_rgb(hsl.h, hsl.s, hsl.l);
        *this = RGBAPixel(rgb.r, rgb.g, rgb.b, hsl.a);
    }

    void RGBAPixel::operator=(const RGBAPixel& other)
    {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        this->a = other.a;
        clampRGBA();
    }

    // TODO within float/float tolerance maybe
    bool RGBAPixel::operator==(const RGBAPixel& other) const
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool RGBAPixel::operator!=(const RGBAPixel& other) const
    {
        return !(*this == other);
    }


    // set rgb
    void RGBAPixel::set(float r, float g, float b)
    {
        *this = RGBAPixel(r, g, b, this->a);
    }


    void RGBAPixel::set(float r, float g, float b, float a)
    {
        *this = RGBAPixel(r, g, b, a);
    }

    void RGBAPixel::set(const RGBAPixel& other)
    {
        *this = other;
    }

    void RGBAPixel::set(const HSLAPixel& other)
    {
        *this = other;
    }

    void RGBAPixel::setAlpha(float a)
    {
        this->a = a;
        clampRGBA();
    }

    void RGBAPixel::setTransparency(float transparency)
    {
        setAlpha(1 - transparency);
    }

    // return euclidian distance // TODO can also divide by sqrt(num channels)? will that make it easier to work with?
    // does not account for alpha channel since it would be the same "color"
    float RGBAPixel::dist(const RGBAPixel& other) const
    {
        float r_dist = r - other.r;
        float g_dist = g - other.g;
        float b_dist = b - other.b;
        return sqrt(r_dist * r_dist + g_dist * g_dist + b_dist * b_dist);
    }

    std::string RGBAPixel::to_string() const
    {
        return "rgba(" +
            std::to_string(r) + ", " +
            std::to_string(g) + ", " +
            std::to_string(b) + ", " +
            std::to_string(a) +
            ")";
    }

    // clamp all [0,1]
    // Assuming NaN reprsents infinity, clamp to 1.
    void RGBAPixel::clampRGBA()
    {
        r = fmax(fmin(r, 1.0), 0.0);
        g = fmax(fmin(g, 1.0), 0.0);
        b = fmax(fmin(b, 1.0), 0.0);
        a = fmax(fmin(a, 1.0), 0.0);
    }

    std::ostream& operator<<(std::ostream& out, const RGBAPixel& pixel)
    {
        out << pixel.to_string();
        return out;
    }

}