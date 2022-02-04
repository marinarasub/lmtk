# [LMTK](https://github.com/marinarasub/lmtk) 
[![build-linux](https://github.com/marinarasub/lmtk/actions/workflows/build-linux.yml/badge.svg)](https://github.com/marinarasub/lmtk/actions/workflows/build-linux.yml)
[![build-windows](https://github.com/marinarasub/lmtk/actions/workflows/build-windows.yml/badge.svg)](https://github.com/marinarasub/lmtk/actions/workflows/build-windows.yml)

## Light Multimedia ToolKit
Multimedia processing tool for images, audio and (planned video). 
Currently in early development. Written in C++. A 
student/hobby project.

Made by marinarasub 2021 - 2022

Currently, this README outlines developement progress and features. Keep in mind
that this project is under version 0 development and there may be uncompleted, 
buggy or unusable features. Expect a lot of changes!


 <br/>

# Latest Release ✅
Coming soon.
Target platforms: windows, linux

 <br/>

# Features
Here are some of the main features 😃. A few demos are available see DEMO.md. 
"TODO" indicates a planned or WIP feature (These will only be here during early
development).

 <br/>

## Image Library 🌄
### Supported Formats
- PNG [read/write]
- JPEG [read/write]
### Tools
- Image convolution
- Resizing TODO bicubic and bilinear
- Mirror TODO angle
- Gradient TODO more options lol
- Alpha blending
### Effects
- Blurs & Sharpen
    - Box/fast blur
    - Gaussian blur
    - Bokeh/lens blur
- Adjustment/Correction
    - HSL (Hue/Sat/Lum) Adjust
- Other
    - Grayscale
    - Chroma key
### Console Application
Command line tool for using the image library. Right now it is experimental.
- Features multithreaded rendering

<br/>

## Audio / DSP Library 🎵
### Supported Formats
- FLAC [read only]
- NEXT PLANNED: MP3 (MPEG Audio Layer III)

### Tools/fx
- Audio playback to output device
    - Live gain
- Track Blending (just add them like A + B!)
- Wave Generators:
    - Sine
    - Saw
    - Square
- TODO low pass, high pass, band pass
- TODO peak detection

## Video 🎥
### Supported Formats
- TBA

## Other
- DFT + FFT
  - Power/frequency spectrum
- Utility classes
    - Math functions
    - Threadpool
    - String functions
    - Other...

 <br/>

 
# Compiling / Building
You can build using CMake and using vcpkg as a dependency manager.
Currently only vcpkg is supported for CMake.

First download [CMake](https://cmake.org/) and 
[vcpkg](https://vcpkg.io/en/index.html) if you haven't already.

Make sure to put vcpkg in your environment variables.

Steps to build:

- Run ```vcpkg install``` on the top level folder (lmtk/). This should download
required dependencies.
- Use CMake at the top level folder (lmtk/).
    - If CMake can't find vcpkg toolchain, try specifying VCPKG_ROOT in CMake
    environment varables
    - Select ```BUILD_TEST``` if you want to build tests

 <br/>

# Performance
I'll update this once the project is more mature.
 
  <br/>

# License
MIT license. see LICENSE.

I have not published any third party source code or binaries so far as of January 2022, but info on licenses and links are below.

 <br/>

# Documentation / API
You can use <a href="https://www.doxygen.nl/index.html">Doxygen</a> to generate
you own copy of the API or view a pre-generated version at docs/

The API should be considered unstable at this stage, and is subject to heavy
modification.

 <br/>

# Development ☕
Although it is not intended for community contribution right now, anyone is
welcome to contribute. See CONTRIBUTING.md

## Required Libraries

If you haven't already, download vcpkg and CMake to help you with this part.

The following libraries are currently used in the project, subject to change.

### Images
- <a href="http://www.libpng.org/pub/png/libpng.html">libpng</a> - PNG Reference Library License
- zlib (use link above) - zlib license
- <a href="https://libjpeg-turbo.org/">libjpeg-turbo</a> - Multiple licenses
  - OR <a href="https://ijg.org/">libjpeg</a> - IJG license
### Audio
- <a href="http://www.portaudio.com/">PortAudio</a> - PortAudio license
- <a href="https://www.xiph.org/flac/">FLAC</a> (libFLAC++) - BSD
### Other
- <a href="https://eigen.tuxfamily.org/">Eigen</a> - MPL 2.0
  - will include license if binaries/source code distributed

 <br/>

## Testing
I am using <a href="https://github.com/google/googletest">Google Test</a> to 
unit test, which should be installed using vcpkg.

Utility funcitons are tested "normally" using assertions and such.

Due to the nature of the project, a lot of tests require file read/write which 
is difficult to make portable. If you decide to run tests, expect a lot of 
failed tests unless you supply for your own files. In addition, many features
are quite complex and undergo minor changes often, so the some of the tests are 
not set in stone.

In the future, I will add test media files to the repository.

 <br/>

## Future / Roadmap / Random TODOs
- Text/font support
- Progress callbacks for image stuff (for loading bar etc.)
- Multithreaded processing
- I plan to make a command line interface and GUI, maybe using WxWidgets or something for editing images, audio etc.
- More formats support. 
- Speed optimization
- Probably use ffmpeg in the future.
- Video editor, maybe.
- Writing this file takes a while so I will continue to update as I think of stuff.
- Linux, Mac OS
- Mobile???# Contains all source code
