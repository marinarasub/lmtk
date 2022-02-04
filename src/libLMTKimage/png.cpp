#include "png.h"

namespace image {
    /**
    * public interface functions
    */

    PNG::PNG(unsigned int w, unsigned int h) : ImageFile(w, h)
    {
    }

    PNG::PNG(std::string path)
    {
        try {
            readFile(path);
        }
        catch (const std::exception& e) {
            throw e;
        }
        //bitmap->width = [this png height]
    }

    PNG::PNG(const Image& other) : ImageFile(other)
    {
        // TODO other stuff like metadata
    }

    PNG::~PNG()
    {
        // clear any that PNG used that Image did not
    }

    // reads png using libpng interface into PNG class.
    // TODO use exceptions instead of macros
    // TODO create exception helper fun
    void PNG::readFile(std::string path)
    {
        clear();
        FILE* fp = fopen(path.c_str(), "rb"); // read-binary file

        // chekc if exists and png
        try {
            if (!isFilePNG(fp)) throw std::invalid_argument("file " + path + " is not a png");
        }
        catch (const std::exception &e)
        {
            throw e;
        }

        // png structs low level interface libpng: Create read, info and end info structs
        png_structp png_ptr;
        png_infop info_ptr, end_info_ptr;
        if (!create_png_read_structs(png_ptr, info_ptr, end_info_ptr))
        {
            throw std::runtime_error("Failed to read png");
        }
        png_set_sig_bytes(png_ptr, PNG_HEADER_BYTES);
        // Set false jump buffer
        if (setjmp(png_jmpbuf(png_ptr)))
        {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
            if (fp) fclose(fp);
            throw std::runtime_error("Failed to read png");
        }
        png_init_io(png_ptr, fp);
        // read info to class PNG
        if (!process_png_info(png_ptr, info_ptr)) throw std::runtime_error("Failed to read png");
        if (!process_png_pixels(png_ptr, info_ptr)) throw std::runtime_error("Failed to read png");
        // png_read_end(png_ptr, end_info_ptr); optional
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
        if (fp) fclose(fp);
    }

    void PNG::writeFile(std::string path)
    {
        FILE* fp = fopen(path.c_str(), "wb");
        // append .png if path is not // write-binary file
        if (fp == NULL)
        {
            throw std::runtime_error("Failed to write png");
        }

        // Create write, infoand end info structs
        png_structp write_png_ptr;
        png_infop write_info_ptr;
        if (!create_png_write_structs(write_png_ptr, write_info_ptr)) throw std::runtime_error("Failed to write png");

        // png_set_write_status_fn();
        // png_set_user_limits(png_p, max_width, max_height); // max png size
        // SETTINGS
        png_init_io(write_png_ptr, fp);
        if (!write_png_info(write_png_ptr, write_info_ptr)) throw std::runtime_error("Failed to write png");
        if (!write_png_pixels(write_png_ptr, write_info_ptr)) throw std::runtime_error("Failed to write png");

        png_destroy_write_struct(&write_png_ptr, &write_info_ptr);
        fclose(fp);
    }


    //int PNG::writeFileCopy(std::string path)
    //{
    //    // TODO
    //    return -1;
    //}

    // void printInfo();

    /**
    * pnglib interface functions
    */

    // return true if file is PNG using libpng
    bool PNG::isFilePNG(FILE* fp)
    {
        if (!fp) throw std::invalid_argument("File does not exist");
        png_byte header[PNG_HEADER_BYTES];
        fread(header, 1, PNG_HEADER_BYTES, fp);
        bool is_png = !png_sig_cmp(header, 0, PNG_HEADER_BYTES);
        if (!is_png) return false;
        return true;
    }

    // creates png and info structs from libpng
    bool PNG::create_png_read_structs(png_structp& png_p, png_infop& info_p, png_infop& end_info_p)
    {
        // could add false and warning handlers here
        png_p = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_p) return false;
        info_p = png_create_info_struct(png_p);
        end_info_p = png_create_info_struct(png_p);
        if (!info_p || !end_info_p)
        {
            png_destroy_read_struct(&png_p, &info_p, &end_info_p);
            return false;
        }
        return true;
    }

    bool PNG::create_png_write_structs(png_structp& png_p, png_infop& info_p) // optional: end_write_info_ptr;
    {
        png_p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_p) return false;
        info_p = png_create_info_struct(png_p);
        if (!info_p)
        {
            png_destroy_write_struct(&png_p, NULL);
            return false;
        }
        return true;
    }

    // process info into PNG class (this)
    // TODO handle grayscale, 8 and 16 bit channels seperately
    int PNG::process_png_info(png_structp& png_p, png_infop& info_p)
    {
        png_read_info(png_p, info_p);
        png_uint_32 width, height;
        int bit_depth, color_type, filter, compression, interlace;
        png_get_IHDR(png_p, info_p, &width, &height, &bit_depth, &color_type, &filter, &compression, &interlace);
        setInitialSize(width, height);
        // or use seperate functions for each suach as png_get_image_width
        // get_PLTE
        // get_gAMA
        // get_sRGB ...
        // get_x_pixels_per_inch ...
        // get_pixel_aspect_ratio
        // ALL of these return 0 if unknown i.e. chunk not read/ not present
        png_set_expand(png_p); // expand to rgba8, same as below:
        /*if (color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png_p);
        if (color_type == PNG_COLOR_TYPE_GRAY &&
            bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png_p);
        if (png_get_valid(png_p, info_p,
            PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_p);*/
            // map also strip (i.e. 16 to 8) rgba, strip alpha, invert alpha
           //png_set_expand_16(png_p); OR USE for 16 bit expansion
        png_set_add_alpha(png_p, 0xFFFF, PNG_FILLER_AFTER);
        png_set_strip_16(png_p);

        png_read_update_info(png_p, info_p);
        return true;
    }

    // process metadata, compression etc, from PNG class (this)
    int PNG::write_png_info(png_structp& png_p, png_infop& info_p)
    {
        png_set_IHDR(png_p, info_p, width(), height(), 8,
            PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
        png_set_filter(png_p, 0, PNG_FILTER_NONE);
        png_set_compression_level(png_p, PNG_Z_DEFAULT_COMPRESSION);
        //png_text text[1]; // 1 
        png_time p_time;
        time_t ttime;
        time(&ttime);
        png_convert_from_time_t(&p_time, ttime);
        png_set_tIME(png_p, info_p, &p_time);
        //png_set_text(write_png_p, write_info_p, <some png_text>, <how many texts>);
        png_write_info(png_p, info_p);

        return true;
    }

    // read png_bytes to PNG, handle memory operations
    int PNG::process_png_pixels(png_structp& png_p, png_infop& info_p)
    {
        int status = true;
        // read png bytes (img data) - alloc memory for libpng copy then transfer to PNG class (this)
        png_byte channels = png_get_channels(png_p, info_p);
        png_byte bit_depth = png_get_bit_depth(png_p, info_p) / 8;
        // alloc height * space per row ptr
        png_bytep* row_ptrs = (png_bytep*)png_malloc(png_p, height() * sizeof(png_bytep));
        for (unsigned int y = 0; y < height(); y++)
        {
            // alloc width * space per pixel // TODO bit depth ~= 8
            row_ptrs[y] = (png_byte*)png_malloc(png_p, width() * sizeof(png_byte) * channels);
        }
        png_read_image(png_p, row_ptrs);
        // transfer row ptrs to PNG class
        row_ptrs_to_pixels(row_ptrs);
        // free row ptrs after finished
        for (unsigned int y = 0; y < height(); y++)
        {
            png_free(png_p, row_ptrs[y]);
        }
        png_free(png_p, row_ptrs);

        return status;
    }

    // write PNG bitmap to png_bytes
    int PNG::write_png_pixels(png_structp& png_p, png_infop& info_p)
    {
        int status = true;

        png_bytepp row_ptrs = (png_bytep*)png_malloc(png_p, height() * sizeof(png_bytep));
        for (unsigned int y = 0; y < height(); y++)
        {
            row_ptrs[y] = (png_byte*)png_malloc(png_p, width() * sizeof(png_byte) * 4); // TODO handle bit depth != 8
        }
        pixels_to_row_ptrs(row_ptrs);
        png_set_rows(png_p, info_p, row_ptrs);

        png_write_png(png_p, info_p, PNG_TRANSFORM_IDENTITY, NULL); // or use low level write interface
        //png_write_image(write_png_p, row_ptrs); // write new (rows) data
        //png_write_end(write_png_p, ..._info_p);
        for (unsigned int y = 0; y < height(); y++)
        {
            png_free(png_p, row_ptrs[y]);
        }
        png_free(png_p, row_ptrs);
        row_ptrs = NULL;


        return status;
    }

    // TODO modify for 16bit color channels, grayscale
    // helper for transfer, channel size in bytes. i.e. =1 for rgb 8bit channels
    void PNG::row_ptrs_to_pixels(const png_bytepp& row_ptrs)
    {
        bool alpha = true; png_byte channels = 4;
        for (unsigned int y = 0; y < height(); y++)
        {
            for (unsigned int x = 0; x < width(); x++)
            {
                unsigned int pixel_size = channels * sizeof(png_byte);
                png_uint_32 r = 0, g = 0, b = 0, a = 0;
                png_uint_32 base = x * pixel_size;
                png_bytep byte_data = &row_ptrs[y][base];
                r = byte_data[0];
                g = byte_data[1];
                b = byte_data[2];
                a = byte_data[3];
                RGBAPixel p(r, g, b, a, 8); // TODO use right constructor for bit size
                //std::cout << p.to_string() << std::endl; // debug print
                setRGBAPixel(p, x, y);
            }
        }
    }

    // helper for transfer (reverse). writes to row_ptrs
    // assumes row_ptrs is allocated to appropriate size
    void PNG::pixels_to_row_ptrs(png_bytepp& row_ptrs)
    {
        // up to 16 bit per channel  TODO, use PNG class fields
        bool alpha = true; png_byte bit_depth = 8;
        png_byte channels = alpha ? 4 : 3; // force alpha for now TODO
        for (unsigned int y = 0; y < height(); y++)
        {
            for (unsigned int x = 0; x < width(); x++)
            {
                unsigned int pixel_size = channels * sizeof(png_byte);
                png_uint_32 base = x * pixel_size;
                png_bytep byte_data = &row_ptrs[y][base];
                double scale = (double) utils::uint_max_val(bit_depth);
                // convert all to int
                RGBAPixel p = *getRGBAPixel(x, y);
                png_byte r, g, b, a;
                r = (png_byte)round(p.r * scale);
                g = (png_byte)round(p.g * scale);
                b = (png_byte)round(p.b * scale);
                a = (png_byte)round(p.a * scale);
                byte_data[0] = r;//row_ptrs[y][x * pixel_size + 0] = r;
                byte_data[1] = g;//row_ptrs[y][x * pixel_size + 1] = g;
                byte_data[2] = b;//row_ptrs[y][x * pixel_size + 2] = b;
                byte_data[3] = a;//row_ptrs[y][x * pixel_size + 3] = a;
            }
        }
    }

}
