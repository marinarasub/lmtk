#include "hslapixel.h"

namespace image {

    HSLAPixel::HSLAPixel()
        : HSLAPixel(0, 0, 0, 0)
    {
    }

    HSLAPixel::HSLAPixel(float h, float s, float l, float a)
        : h(h), s(s), l(l), a(a)
    {
        clampHSLA();
    }

    HSLAPixel::HSLAPixel(const RGBAPixel& rgb)
    {
        color::hsl_color hsl = color::rgb_to_hsl(rgb.r, rgb.g, rgb.b);
        *this = HSLAPixel(hsl.h, hsl.s, hsl.l, rgb.a);
    }

    void HSLAPixel::operator=(const HSLAPixel& other)
    {
        this->h = other.h;
        this->s = other.s;
        this->l = other.l;
        this->a = other.a;
        clampHSLA();
    }

    bool HSLAPixel::operator==(const HSLAPixel& other) const
    {
        return h == other.h && s == other.s && l == other.l && a == other.a;
    }

    bool HSLAPixel::operator!=(const HSLAPixel& other) const
    {
        return !(*this == other);
    }

    void HSLAPixel::set(float h, float s, float l)
    {
        *this = HSLAPixel(h, s, l, this->a);
    }

    void HSLAPixel::set(float h, float s, float l, float a)
    {
        *this = HSLAPixel(h, s, l, a);
    }

    void HSLAPixel::set(const HSLAPixel& other)
    {
        *this = other;
    }

    void HSLAPixel::set(const RGBAPixel& other)
    {
        *this = other;
    }

    void HSLAPixel::setAlpha(float a)
    {
        this->a = a;
        clampHSLA();
    }

    void HSLAPixel::setTransparency(float transparency)
    {
        this->a = 1.0 - transparency;
        clampHSLA();
    }

    std::string HSLAPixel::to_string() const
    {
        return "hsla(" +
            std::to_string(h) + ", " +
            std::to_string(s) + ", " +
            std::to_string(l) + ", " +
            std::to_string(a) +
            ")";
    }

    void HSLAPixel::clampHSLA()
    {
        h = fmod(h < 0 ? 360.0 + h : h, 360.0);
        s = fmax(fmin(s, 1.0), 0.0);
        l = fmax(fmin(l, 1.0), 0.0);
        a = fmax(fmin(a, 1.0), 0.0);
    }

    std::ostream& operator<<(std::ostream& out, const HSLAPixel& pixel)
    {
        return out << pixel.to_string();
    }

}
