#include "imagefx.hpp"


namespace lmtkimage
{

    // map for fx string to instantiation wrapper
    static std::unordered_map<std::string, fx_info> fx_map =
    {
        {"bokeh-blur", {make_bokeh_blur, "bokeh/lens blur", "[#passes*](radius-x, radius-y)"}},
        {"box-blur", {make_box_blur, "box convolution blur, default is equivalent to fast blur", "[#passes*](radius)"}},
        {"fast-blur", {make_fast_blur, "fast blur, approximates gaussian blur (using box blur)", "(radius)"}},
        {"chroma-key", {make_chroma_keyer, "chroma keyer, removes all color within threshold of target", "(r, g, b, a*, threshold*)"}},
        {"color-invert", {make_color_invert, "inverts color", "none"}},
        {"gaussian-blur", {make_gaussian_blur, "blurs the image with surrounding pixels with to gaussian function", "[#passes*](stdev-x, stdev-y, tolerance*)"}},
        {"tilt-shift-blur", {make_tilt_shift, "blurs image outside of top and bottom y limits with chosen blur method","[#passes*](blur-method, top-y, bottom-y, gradient-size, gradient-speed, <blur-method args>...)"}},
        {"sharpen", {make_image_sharpen, "sharpens the image by emphasizing edges", "[#passes*](amount*)"}},
        {"hsl-adjust", {make_hsl_adjust, "adjust the hue, saturation and luminance of the image", "(hue shift in degrees, saturation multiplier, luminance multiplier)"}},
        {"grayscale", {make_grayscale, "convert the image to grayscale (black & white)", "none"}},
        {"vignette", {make_vignette, "apply vignette to image with given color, default black", "(radius-x, radius-y, fade-amt, fade-color*)"}}
    };

    // TODO make except. use map usage field
    // TODO count passes since removed from image shaders TODO!!!!!!
    // TODO return multiple

    std::vector<ImageShader*> make_bokeh_blur(size_t passes, std::vector<std::string> args)
    {
        if (passes == 0) throw std::invalid_argument("# of passes must be > 0");
        // why would you want more than 1 pass though?
        float radX, radY;
        switch (args.size())
        {
        case 1:
            radX = std::stof(args[0]);
            radY = radX;
            break;
        case 2:
            radX = std::stof(args[0]);
            radY = std::stof(args[1]);
            break;
        default:
            throw std::invalid_argument("invalid number of args");
        }
        return std::vector<ImageShader*>(passes, new BokehBlur(radX, radY));
    }

    std::vector<ImageShader*> make_box_blur(size_t passes, std::vector<std::string> args)
    {
        if (passes == 0) throw std::invalid_argument("# of passes must be > 0");
        float radX, radY;
        switch (args.size())
        {
        case 1:
            radX = std::stof(args[0]);
            radY = radX;
            break;
        case 2:
            radX = std::stof(args[0]);
            radY = std::stof(args[1]);
            break;
        default:
            throw std::invalid_argument("invalid number of args");
        }
        std::vector<ImageShader*> boxb;
        BoxBlurHorizontal* bX = new BoxBlurHorizontal(radX);
        BoxBlurVertical* bY = new BoxBlurVertical(radY);
        for (size_t i = 0; i < passes; i++)
        {
            boxb.push_back(bX);
            boxb.push_back(bY);
        }
        return boxb;
    }

    std::vector<ImageShader*> make_fast_blur(size_t passes, std::vector<std::string> args)
    {
        return make_box_blur(passes * 3, args);
    }

    std::vector<ImageShader*> make_chroma_keyer(size_t passes, std::vector<std::string> args)
    {
        if (passes != 1) throw std::invalid_argument("chroma key only needs 1 pass");
        if (args.size() < 3) throw std::invalid_argument("chroma key needs 3, 4 or 5 args");
        float r = std::stof(args[0]);
        float g = std::stof(args[1]);
        float b = std::stof(args[2]);
        RGBAPixel p(r, g, b);
        float a, tol = ChromaKeyer::DEFAULT_TOLERANCE;
        if (args.size() > 3)
        {
            a = std::stof(args[3]);
            p.setAlpha(a);
        }
        if (args.size() > 4)
        {
            tol = std::stof(args[4]);
        }
        if (args.size() > 5) throw std::invalid_argument("too many args for chroma key");
        return std::vector<ImageShader*>(1, new ChromaKeyer(p, tol));
    }

    std::vector<ImageShader*> make_color_invert(size_t passes, std::vector<std::string> args)
    {
        if (passes != 1) throw std::invalid_argument("invert only needs 1 pass");
        if (args.size() > 0) throw std::invalid_argument("too many args for invert");
        return std::vector<ImageShader*>(1, new ColorInverter());
    }

    std::vector<ImageShader*> make_gaussian_blur(size_t passes, std::vector<std::string> args)
    {
        if (passes == 0) throw std::invalid_argument("# of passes must be > 0");
        float sdX = 0, sdY = 0, tol = -1;
        switch (args.size())
        {
        case 1:
            sdX = std::stof(args[0]);
            sdY = sdX;
            break;
        case 2:
            sdX = std::stof(args[0]);
            sdY = std::stof(args[1]);
            break;
        case 3:
        {
            float arg3 = std::stof(args[2]);
            if (arg3 > 0)
            {
                tol = arg3;
                break;
            }
        }
        default:
            throw std::invalid_argument("bad args");
        }
        std::vector<ImageShader*> gaussians;
        // TODO tol
        GaussianBlurHorizontal* gX = new GaussianBlurHorizontal(sdX);
        GaussianBlurVertical* gY = new GaussianBlurVertical(sdY);
        for (size_t i = 0; i < passes; i++)
        {
            gaussians.push_back(gX);
            gaussians.push_back(gY);
        }
        return gaussians;
    }

    std::vector<ImageShader*> make_grayscale(size_t passes, std::vector<std::string> args)
    {
        if (passes != 1) throw std::invalid_argument("greyscale only needs 1 pass");
        if (args.size() != 0) throw std::invalid_argument("too many args for grayscale");
        return std::vector<ImageShader*>(1, new GrayScaleShader());
    }

    std::vector<ImageShader*> make_hsl_adjust(size_t passes, std::vector<std::string> args)
    {
        if (passes != 1) throw std::invalid_argument("hsl only needs 1 pass");
        if (args.size() != 3) throw std::invalid_argument("hsl needs 2 args (hue shift degrees, sat multiplier, lum multiplier)");
        float hue = std::stof(args[0]);
        float sat = std::stof(args[1]);
        float lum = std::stof(args[2]);
        return std::vector<ImageShader*>(1, new HueSatLumAdjust(hue, sat, lum));
    }


    std::vector<ImageShader*> make_image_sharpen(size_t passes, std::vector<std::string> args)
    {
        if (passes == 0) throw std::invalid_argument("# of passes must be > 0");
        float amt = -1;
        if (args.size() == 0)
        {
            return std::vector<ImageShader*>(passes, new ImageSharpen());
        }
        else if (args.size() == 1)
        {
            amt = std::stof(args[0]);
            return std::vector<ImageShader*>(passes, new ImageSharpen(amt));
        }
        else throw std::invalid_argument("too many args for sharpen");
    }

    std::vector<ImageShader*> make_tilt_shift(size_t passes, std::vector<std::string> args)
    {
        if (passes == 0) throw std::invalid_argument("# of passes must be > 0");
        if (args.size() < 4) throw std::invalid_argument("tilt shift needs >= 4 args");
        std::string blur_method = args[0];
        // get the blur passes
        std::vector<ImageShader*> blur_passes =
            fx_map[blur_method].function(passes, std::vector<std::string>(args.begin() + 5, args.end()));
        std::vector<ImageShader*> tiltshift;
        for (ImageShader* fx : blur_passes)
        {
            Blur* blur_fx = dynamic_cast<Blur*>(fx);
            if (!fx) throw std::invalid_argument("not a blur method");
            tiltshift.push_back(new TiltShiftBlur(
                std::stoi(args[1]), 
                std::stoi(args[2]), 
                std::stof(args[3]), 
                std::stof(args[4]),
                blur_fx));
            delete blur_fx;
        }
        return tiltshift;
    }

    std::vector<ImageShader*> make_vignette(size_t passes, std::vector<std::string> args)
    {
        if (passes != 1) throw std::invalid_argument("vignette only needs 1 pass");
        if (args.size() == 3)
        {
            VignetteShader* vignette = new VignetteShader(std::stoi(args[0]), std::stoi(args[1]), std::stof(args[2]));
            return std::vector<ImageShader*>(1, vignette);
        }
        //else if (args.size() == 4)
        //{
        //    // TODO parse rgb string to color
        //    
        //}
        else throw std::invalid_argument("vignette needs 3 or 4 args");
    }

    // help msg for usage of fx
    std::string help_fx()
    {
        std::string all_fx;
        all_fx.append("Use effects with --fx \"effect_name[#passes*](arg1, arg2,...)\" ...\n");
        all_fx.append("Valid effects (* denotes optional argument):");

        // find size to resize to
        size_t max_name = 0, max_desc = 0, max_use = 0;
        for (auto kv : fx_map)
        {
            size_t name_len = kv.first.length();
            size_t desc_len = kv.second.description.length();
            size_t use_len = kv.second.usage.length();
            max_name = name_len > max_name ? name_len : max_name;
            max_desc = desc_len > max_name ? desc_len : max_desc;
            max_use = use_len > max_use ? use_len : max_use;
        }
        // format
        for (auto kv : fx_map)
        {
            std::string name = kv.first;
            std::string desc = kv.second.description;
            std::string use = kv.second.usage;
            name.resize(max_name, ' ');
            desc.resize(max_desc, ' ');
            use.resize(max_use, ' ');
            all_fx.append("\n  " + name);
            all_fx.append("    " + desc);
            all_fx.append("    args: " + use);
        }
        return all_fx;
    }

    // returns null if not found
    std::vector<ImageShader*> get_effects(std::string effect, size_t passes, std::vector<std::string> args)
    {
        auto iter = fx_map.find(effect);
        if (iter != fx_map.end()) return fx_map[effect].function(passes, args);
        throw std::invalid_argument("unknown effect: " + effect);
    }


}
