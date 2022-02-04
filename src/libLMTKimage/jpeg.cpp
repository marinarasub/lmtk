#include "jpeg.h"

namespace image {

    JPEG::JPEG(unsigned int w, unsigned int h) : ImageFile(w, h)
    {
    }

    JPEG::JPEG(std::string path)
    {
        try {
            readFile(path);
        }
        catch (const std::exception &e)
        {
            throw e;
        }
    }

    JPEG::JPEG(const Image& other) : ImageFile(other)
    {
    }

    JPEG::~JPEG()
    {
    }

    // TODO handle except by libjpeg

    void JPEG::readFile(std::string path)
    {
        FILE* fp = fopen(path.c_str(), "rb"); // read-binary file
        if (fp == NULL) throw std::invalid_argument("file " + path + " does not exist"); // TODO fclose before throw (png too)

        jpeg_decompress_struct* dinfo = (jpeg_decompress_struct*)
            alloca(sizeof(jpeg_decompress_struct));
        jpeg_error_mgr jerr;
        // TODO setjmp
        // STEP 1 : decompression opject
        dinfo->err = jpeg_std_error(&jerr);
        jpeg_create_decompress(dinfo);
        int channels = 3; // 3 channels 
        // STEP 2 : read src and header
        // check fopen already done
        jpeg_stdio_src(dinfo, fp);
        jpeg_read_header(dinfo, TRUE); // checks if JPEG for us
        // STEP 3 : decompress, read pixels
        jpeg_start_decompress(dinfo);
        setInitialSize(dinfo->output_width, dinfo->output_height);
        channels = dinfo->output_components;
        if (channels != 3) {
            throw std::invalid_argument("only 3 channel JPEG supported right now");
        }
        // malloc row ptrs
        JSAMPARRAY row_ptrs = (*dinfo->mem->alloc_sarray)
            ((j_common_ptr)dinfo, JPOOL_IMAGE, width() * channels, height());
        //JSAMPARRAY row_ptrs = (JSAMPARRAY)malloc(height() * sizeof(JSAMPROW)); // similar to libpng
        //for (unsigned int y = 0; y < height(); y++)
        //{
        //    row_ptrs[y] = (JSAMPROW)malloc(width() * sizeof(JSAMPLE) * channels);
        //    if (row_ptrs[y] == NULL) throw ERROR;
        //}
        // TODO reading one row at a time probably saves memory
        // apparently the loop has to be here. ugh.
        JSAMPROW row_p = (JSAMPROW)alloca(width() * channels);
        unsigned int y = 0;
        while (dinfo->output_scanline < dinfo->output_height) {
            //JDIMENSION d = 
            jpeg_read_scanlines(dinfo, &row_p, 1);
            std::memcpy(row_ptrs[y++], row_p, width() * channels);
            //printf("%d lines read VS output scanline %d\n", d, dinfo->output_scanline);
        }
        // cmon, there's gotta be a better way to do that
        row_ptrs_to_pixels(row_ptrs);
        // reverse pixels_to_row_ptrs(row_ptrs);
        /*for (unsigned int y = 0; y < height(); y++)
        {
            free(row_ptrs[y]);
        }
        free(row_ptrs);*/
        jpeg_finish_decompress(dinfo);
        jpeg_destroy_decompress(dinfo);

        fclose(fp);
    }

    // TODO compression levels
    void JPEG::writeFile(std::string path)
    {
        FILE* fp = fopen(path.c_str(), "wb");
        // append .jpeg if path is not // write-binary file
        if (fp == NULL) throw std::invalid_argument("file does not exist");

        // libjpeg-turbo structs for write
        //extern JSAMPLE* image_buffer; // pixel array
        jpeg_compress_struct* cinfo = (jpeg_compress_struct*)
            alloca(sizeof(jpeg_compress_struct));
        jpeg_error_mgr jerr;
        // TODO setjmp
        // STEP 1 : compression opject
        cinfo->err = jpeg_std_error(&jerr);
        jpeg_create_compress(cinfo);
        int channels = 3; // 3 channels 
        // STEP 2 : write destination
        // check fopen already done
        jpeg_stdio_dest(cinfo, fp);

        // STEP 3 : Compression parameters
        cinfo->image_width = width();
        cinfo->image_height = height();
        cinfo->input_components = channels; // num channels (jpeg has no alpha)
        cinfo->in_color_space = JCS_RGB; // default 8 bit TODO variable color space
        int quality = 100; // 0..100
        jpeg_set_defaults(cinfo);
        jpeg_set_quality(cinfo, quality, TRUE);

        // STEP 4-6 : Compression
        jpeg_start_compress(cinfo, TRUE);
        // malloc row ptrs
        JSAMPARRAY row_ptrs = (JSAMPARRAY)malloc(height() * sizeof(JSAMPROW)); // similar to libpng
        for (unsigned int y = 0; y < height(); y++)
        {
            row_ptrs[y] = (JSAMPROW)malloc(width() * sizeof(JSAMPLE) * channels);
            if (row_ptrs[y] == NULL) throw std::runtime_error("Failed to write JPEG");
        }
        pixels_to_row_ptrs(row_ptrs);
        jpeg_write_scanlines(cinfo, row_ptrs, height());
        //free row ptrs
        for (unsigned int y = 0; y < height(); y++)
        {
            free(row_ptrs[y]);
        }
        free(row_ptrs);
        jpeg_finish_compress(cinfo);
        jpeg_destroy_compress(cinfo);

        fclose(fp);
    }

    // TODO modify for 16bit color channels, grayscale
    // helper for transfer, channel size in bytes. i.e. =1 for rgb 8bit channels
    void JPEG::row_ptrs_to_pixels(const JSAMPARRAY& row_ptrs)
    {
        byte bit_depth = 8;
        byte channels = 3; // RGB
        for (unsigned int y = 0; y < height(); y++)
        {
            for (unsigned int x = 0; x < width(); x++)
            {
                unsigned int pixel_size = channels * sizeof(JSAMPLE);
                JSAMPLE r = 0, g = 0, b = 0;
                unsigned int base = x * pixel_size;
                JSAMPLE* byte_data = &row_ptrs[y][base];
                r = byte_data[0];
                g = byte_data[1];
                b = byte_data[2];
                RGBAPixel p(r, g, b, utils::uint_max_val(8), 8); // TODO use right constructor for bit size
                //std::cout << p.to_string() << std::endl; // debug print
                setRGBAPixel(p, x, y);
                //printf("pixel %s at (%u, %u)\n", p.to_string().c_str(), x, y);
            }
        }
    }

    // array of row ptrs for each row
    void JPEG::pixels_to_row_ptrs(JSAMPARRAY& row_ptrs)
    {
        // up to 32 bit per channel  TODO
        byte bit_depth = 8;
        byte channels = 3; // RGB
        for (unsigned int y = 0; y < height(); y++)
        {
            for (unsigned int x = 0; x < width(); x++)
            {
                unsigned int pixel_size = channels * sizeof(JSAMPLE);
                unsigned int base = x * pixel_size;
                JSAMPLE* byte_data = &row_ptrs[y][base];
                double scale = (double)utils::uint_max_val(bit_depth);
                // convert all to int
                RGBAPixel p = *getRGBAPixel(x, y);
                JSAMPLE r, g, b;
                r = (JSAMPLE)round(p.r * scale);
                g = (JSAMPLE)round(p.g * scale);
                b = (JSAMPLE)round(p.b * scale);
                byte_data[0] = r;
                byte_data[1] = g;
                byte_data[2] = b;
            }
        }
    }

}

