#include "color.h"

namespace color {

    // TODO do not use classes, let classes implement own conversion using 
    // these

    /**
    * Translated from 
    * @ref https://www.rapidtables.com/convert/color/hsl-to-rgb.html
    */

    hsl_color rgb_to_hsl(double r, double g, double b)
    {
        return rgb_to_hsl(rgb_color{ r, g, b });
    }

    hsl_color rgb_to_hsl(const rgb_color& clr)
    {
        double max_clr = fmax(fmax(clr.r, clr.g), clr.b);
        double min_clr = fmin(fmin(clr.r, clr.g), clr.b);
        double chroma = max_clr - min_clr;

        double hue, sat, light;
        // hue
        if (chroma == 0) hue = 0;
        else if (max_clr == clr.r)
        {
            hue = 60.0 * (fmod((clr.g - clr.b) / chroma, 6));
        }
        else if (max_clr == clr.g)
        {
            hue = 60.0 * ((clr.b - clr.r) / chroma + 2.0);
        }
        else if (max_clr == clr.b)
        {
            hue = 60.0 * ((clr.r - clr.g) / chroma + 4.0);
        }
        else throw -1;
        // light
        light = (max_clr + min_clr) / 2;
        // sat
        if (light == 0 || light == 1) sat = 0;
        else sat = chroma / (1.0 - fabs(2 * light - 1));

        return hsl_color{ hue, sat, light };
    }

    rgb_color hsl_to_rgb(double h, double s, double l)
    {
        return hsl_to_rgb(hsl_color{ h, s, l });
    }

    rgb_color hsl_to_rgb(const hsl_color& clr)
    {
        double c = (1.0 - fabs(2 * clr.l - 1)) * clr.s;
        double hh = clr.h / 60;
        double x = c * (1 - fabs(fmod(hh, 2.0) - 1));
        double m = clr.l - c / 2;

        double red = 0, green = 0, blue = 0;

        if (hh < 1) { red = c, green = x; }
        else if (hh < 2) { red = x, green = c; }
        else if (hh < 3) { green = c, blue = x; }
        else if (hh < 4) { green = x, blue = c; }
        else if (hh < 5) { red = x, blue = c; }
        else if (hh < 6) { red = c, blue = x; }
        else throw -1;
 
        return rgb_color{ red + m, green + m, blue + m };
    }

}
