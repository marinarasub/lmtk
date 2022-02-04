/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is the entry point for the LMTK image console application.
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <boost/program_options.hpp>
#include "../libLMTKimage/imagefile.h"
#include "../libLMTKimage/png.h"
#include "../libLMTKimage/jpeg.h"
#include "../libLMTKimage/pluginchain.h"
#include "../utils/file.h"
#include "../utils/utilsstring.h"
#include "../../include/config.h"
#include "../utils/timer.h"
#include "imagetools/imagefx.hpp"
#include "imagetools/renderer.h"
#include "imagetools/progressbar.h"
#include <mutex>

//#include "tools/progressbar.h"

//#pragma comment(linker, "/SUBSYSTEM:CONSOLE")

/*
* 
* This file contains the main console application for image tools.
* It is quite experimental right now, so it is quite a mess.
*
*/

//#if defined(_WIN32) || defined(_WIN64)
//#include <Windows.h>
//#define _CONSOLE
//#endif

std::mutex cout_mtx;

// TODO this
enum class PROGRAM_INFO_LEVEL
{
    SILENT,
    LOW,
    DEFAULT,
    ALL
};

std::string program_version()
{
    return std::string("LMTKImage (c) marinarasub 2022 version ").append(LMTK_VERSION);
}

// fn map for processing
//std::unordered_map<std::string, void(*)()> callback_map;

image::ImageFile* readImage(std::string path)
{
    using namespace image;

    std::string ext = utils::file_extension(path);
    // todo ignore case
    try {
        if (ext == "png") return new PNG(path);
        else if (ext == "jpg" || ext == "jpeg") return new JPEG(path);
        else throw std::invalid_argument("File type not supported");
    }
    catch (const std::exception &e) {
        throw e;
    }
}

// TODO why isnt it working???
void convert(image::ImageFile* &img, std::string ext)
{
    using namespace image;

    ImageFile* temp;
    try {
        // ???
        if (ext == "png") 
        {
            temp = new PNG(*img);
            std::cout << "Cast to PNG" << std::endl;
        }
        else if (ext == "jpg" || ext == "jpeg")
        {
            temp = new JPEG(*img);
            std::cout << "Cast to JPEG" << std::endl;
        }
        else throw std::invalid_argument("File type not supported");
    }
    catch (const std::exception& e) {
        throw e;
    }
    delete img;
    img = temp;
}

void writeImage(image::ImageFile* &img, std::string path)
{
    std::string ext = utils::file_extension(path);
    // todo ignore case
    try {
        convert(img, ext);
        if (img) img->writeFile(path);
        else throw std::runtime_error("failed to write");
    }
    catch (const std::exception& e) {
        throw e;
    }
}

// TODO move to parser class or something
std::vector<std::string> parse_fx_args(std::string args)
{
    args = utils::remove_spaces(args);

    std::vector<std::string> args_list;

    size_t last = 0;
    for (size_t i = 0; i <= args.length(); i++)
    {
        if (args[i] == ',' || i == args.length())
        {
            std::string arg = args.substr(last, i - last);
            if (arg != "") args_list.push_back(arg);
            last = i + 1;
        }
        // todo handle bad chars (keep alphanumeric)
        // todo handle spaces
        // todo use const for space and delimiter
    }
    return args_list;
}

// TODO move to parser class or something
std::vector<image::ImageShader*> get_effects(std::string str)
{
    using namespace image;

    // mini parser: break into name, brackets and params (comma delim) -> EX blur(2, 3)
    std::invalid_argument syntax_error("syntax error: " + str);
    std::string args = ""; // may be empty
    std::string effect = "";
    size_t passes = 1;

    size_t open_brkt = str.npos, close_brkt = str.npos;
    size_t open_sqr_brkt = str.npos, close_sqr_brkt = str.npos;
    for (size_t i = 0; i < str.length(); i++)
    {
        // args brackets
        if (str[i] == '(')
        {
            if (open_brkt != str.npos || close_brkt != str.npos) throw syntax_error; // already () brackets
            open_brkt = i;
            close_brkt = str.find_first_of(')');
            if (close_brkt == str.npos) throw syntax_error; // missing closing
            args = str.substr(i + 1, close_brkt - i - 1);
            i = close_brkt;
        }
        // passes # brackets
        else if (str[i] == '[')
        {
            if (open_sqr_brkt != str.npos || close_sqr_brkt != str.npos) throw syntax_error; // already [] brackets
            open_sqr_brkt = i;
            close_sqr_brkt = str.find_first_of(']');
            std::string pass_str = str.substr(i + 1, close_sqr_brkt - i - 1);
            passes = std::stoul(pass_str);
            i = close_sqr_brkt;
        }
        else
        {
            // brackets must appear after effect name
            if (open_brkt != str.npos && effect != "") throw syntax_error;
            if (open_sqr_brkt != str.npos && effect != "") throw syntax_error;
            effect += str[i];
        }
    }
    std::vector<std::string> args_list = parse_fx_args(args);
    // TODO handle passes
    return lmtkimage::get_effects(effect, passes, args_list);
}

namespace options = boost::program_options;

int main(int argc, char** argv)
{
    // variables to use
    size_t threads;
    std::string help_arg;
    std::string in;
    std::string out;
    std::vector<std::string> fx;
    std::vector<int> resize;
    std::vector<double> scale;


    // options part TODO multiple options description (bunch into general, file, image, fx, render categories etc.)
    // TODO blend, resize ...
    options::options_description desc("Valid options");
    desc.add_options()
        ("help,h", options::value<std::string>(&help_arg)->implicit_value(""), "show help menu or specific argument help")
        ("version,v", "show version number")
        ("verbose,info-level", options::value<std::string>(), "set info level when running")
        ("multithread,MT", options::value<size_t>(&threads)->implicit_value(0)->default_value(1, "no"), "use multithreaded rendering, given number of threads (if no arg given, will use number of logical cores)")
        ("import,read,open,in", options::value<std::string>(&in), "choose file to open for reading")
        // TODO create image, ie blank
        // TODO blend two+ images
        // TODO save quality (i.e. compression - right now uses default or max quality)
        ("export,write,out", options::value<std::string>(&out), "choose file to write to")
        ("overwrite,ow", options::bool_switch()->default_value(false), "overwrite output file if already exists TODO")
        ("resize", options::value<std::vector<int>>(&resize)->multitoken(), "resize the image to given width, height (done pre-fx)") 
        ("scale", options::value<std::vector<double>>(&scale)->multitoken(), "scale image given scaleX, scaleY (done after resize, pre-fx)")
        ("color-picker,dropper-tool", "get the color at x, y of an image")
        // TODO choose method, pre or post fx
        ("effects,fx", options::value<std::vector<std::string>>(&fx)->multitoken(), "choose effects")
        ;
    options::variables_map vm;
    // get args from cmd line
    try {
        options::store(options::parse_command_line(argc, argv, desc), vm);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    bool mt = threads != 1;

    options::notify(vm);

    // TODO move these all to handler functions
    try {
        
        // help or version don't need other inputs
        if (vm.count("help")) 
        { 
            if (help_arg == "") std::cout << desc << '\n';
            // TODO is there way to match with boost?
            else if (help_arg == "fx" || help_arg == "effect") std::cout << lmtkimage::help_fx() << '\n';
            else std::cout << desc.find(help_arg, true).description() << '\n';
            return 0; 
        }
        // TODO print all software data banner etc.
        else if (vm.count("version")) 
        { 
            std::cout << program_version(); 
            return 0; 
        }
        //if (!vm.count("import")) throw options::error_with_option_name("No image selected", "import");
        // everything else needs in and out
        else if (!vm.count("import")) throw options::error_with_option_name("No file to read", in);
        else if (!vm.count("export")) out = in; // assume same file then
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    utils::Timer timer; // universal timer

    // read
    // TODO support opening multiple files, blending
    image::ImageFile* img;
    try {
       timer.start();
       img = readImage(in);
       std::string time_str = std::to_string(timer.time()); // TODO move to timer class
       time_str.resize(5);
       std::cout << "Read - time elapsed: " << time_str << "s" << '\n';
       size_t byte_size = img->size() * sizeof(image::RGBAPixel);
       std::cout << "Image data size in memory: " << utils::get_size_string(byte_size) << '\n';
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    std::cout << "File read successfully!" << '\n';

    // color picker returns after done
    try {
        if (vm.count("color-picker"))
        {
            std::cout << "" << std::endl;
            return 0;
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    // apply resize, other ...
    try {
        if (vm.count("resize")) 
        {
            timer.start();
            if (resize.size() != 2) throw std::invalid_argument("resize takes width, height");
            img->resize(resize[0], resize[1]);
            std::string time_str = std::to_string(timer.time()); // TODO move to timer class
            time_str.resize(5);
            std::cout << "Resize - time elapsed: " << time_str << "s" << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    try {
        if (vm.count("scale"))
        {
            timer.start();
            if (scale.size() != 2) throw std::invalid_argument("scale takes scaleX, scaleY");
            img->scale(scale[0], scale[1]);
            std::string time_str = std::to_string(timer.time()); // TODO move to timer class
            time_str.resize(5);
            std::cout << "Scale - time elapsed: " << time_str << "s" << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }

    // get fx
    image::PluginChain fx_chain;
    for (size_t i = 0; i < fx.size(); i++)
    {
        std::string str = fx[i];
        std::vector<image::ImageShader*> effect;
        try {
             effect = get_effects(str);
             fx_chain.addEffects(effect);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }

    // render
    timer.start();

    if (mt && fx.size() > 0)
    {
        image::Image* buffer = new image::Image(*img);
        renderer::ImageRenderer render(threads, buffer);
        render.setProgressCallback([](double prog, size_t curr, size_t total, bool failed)
            {
                std::string progstr = progressbar::getProgressBar(prog, false);
                std::lock_guard<std::mutex> lock(cout_mtx);
                if (!failed) 
                {
                    std::string info = " (Pass " + 
                        std::to_string(curr) + 
                        " of " + 
                        std::to_string(total) +
                        ")";
                    progstr.append(info);
                    std::cout << progstr;
                }
                if (prog >= 1 || failed) std::cout << std::endl;
            });
        render.render(fx_chain, img);
        delete buffer;
    }
    else fx_chain(*img);

    std::string time_str = std::to_string(timer.time()); // TODO move to timer class
    time_str.resize(5);
    std::cout << "Render effects - time elapsed: " << time_str << "s" << '\n';

    // write
    try {
        // todo extension checking and overwrite check
        timer.start();
        writeImage(img, out);
        std::string time_str = std::to_string(timer.time()); // TODO move to timer class
        time_str.resize(5);
        std::cout << "Write - time elapsed: " << time_str << "s" << '\n';
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    std::cout << "File wrote successfully!" << '\n';

    delete img;

    // TODO everything lol

    return 0;
}