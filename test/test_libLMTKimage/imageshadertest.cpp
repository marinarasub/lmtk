#include "imageshadertest.h"

using namespace ::testing;
using namespace image;

/**
* Test class for image tool/ shader functions. 
* Will use PNG class for output.
*/
class ShaderTest : public Test
{
public:
	const static std::string IMG_FOLDER;
	const static std::string OUT_FOLDER;

protected:

	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

const std::string ShaderTest::IMG_FOLDER = "../testdata/images/in/";
const std::string ShaderTest::OUT_FOLDER = "../testdata/images/out/shadertest/";

TEST_F(ShaderTest, bokeh_blur_near_zero)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        BokehBlur blur(0.00001);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-zero.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}


TEST_F(ShaderTest, gaussian_blur_near_zero_stdev)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        GaussianBlur blur(0.00001);
        blur(img);
        img.writeFile(OUT_FOLDER + "gaussian-zero.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, tilt_shift_bokeh)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        BokehBlur blur(10);
        TiltShiftBlur tshift(
            img.height() / 3,
            2 * img.height() / 3,
            static_cast<float>(img.height()) / 6,
            &blur);
        tshift(img);
        img.writeFile(OUT_FOLDER + "tshift-bokeh.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, tilt_shift_gaussianhv)
{
    try {
        JPEG img(IMG_FOLDER + "ny.jpg");
        GaussianBlurHorizontal blurh(5);
        GaussianBlurVertical blurv(5);
        TiltShiftBlur tshifth(
            img.height() / 3,
            2 * img.height() / 3,
            static_cast<float>(img.height()) / 8,
            &blurh);
        TiltShiftBlur tshiftv(
            img.height() / 3,
            2 * img.height() / 3,
            static_cast<float>(img.height()) / 8,
            &blurv);
        tshiftv(img);
        tshifth(img);
        img.writeFile(OUT_FOLDER + "tshift-gaussianhv.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, tilt_shift_gaussian)
{
    try {
        JPEG img(IMG_FOLDER + "ny.jpg");
        GaussianBlur blur(5);
        TiltShiftBlur tshift(
            img.height() / 3,
            2 * img.height() / 3,
            static_cast<float>(img.height()) / 6,
            &blur);
        tshift(img);
        img.writeFile(OUT_FOLDER + "tshift-gaussian.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, rotate_90)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        ImageRotate rot(90);
        rot(img);
        img.writeFile(OUT_FOLDER + "rot90.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}


TEST_F(ShaderTest, rotate_30)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        ImageRotate rot(30);
        rot(img);
        img.writeFile(OUT_FOLDER + "rot30.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, rotate_neg30)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        ImageRotate rot(-30);
        rot(img);
        img.writeFile(OUT_FOLDER + "rotneg30.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, rotate_neg110)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        ImageRotate rot(-110);
        rot(img);
        img.writeFile(OUT_FOLDER + "rotneg110.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, rotate_180)
{
    try {
        JPEG img(IMG_FOLDER + "sun.jpg");
        ImageRotate rot(180);
        rot(img);
        img.writeFile(OUT_FOLDER + "rot180.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, rotate_270)
{
    try {
        JPEG img(IMG_FOLDER + "sun.jpg");
        ImageRotate rot(270);
        rot(img);
        img.writeFile(OUT_FOLDER + "rot270.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, rotate_3600)
{
    try {
        JPEG img(IMG_FOLDER + "sun.jpg");
        ImageRotate rot(3600);
        rot(img);
        img.writeFile(OUT_FOLDER + "rot3600.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, vignette)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        VignetteShader vignette(img.width()/3, img.height()/3, 1);
        vignette(img);
        img.writeFile(OUT_FOLDER + "vignette.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, invert)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		ColorInverter shader;
		shader(img);
		img.writeFile(OUT_FOLDER + "invert-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

TEST_F(ShaderTest, invert2)
{
    try {
        JPEG img(IMG_FOLDER + "fireworks.jpg");
        ColorInverter shader;
        shader(img);
        img.writeFile(OUT_FOLDER + "invert2-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write png file";
    }
}

TEST_F(ShaderTest, chroma_key)
{
	float lo = 0.1;
	try {
		PNG img(IMG_FOLDER + "gstest.png");
		ChromaKeyer keyer(*img.getRGBAPixel(0, 0), lo);
		keyer(img);
		img.writeFile(OUT_FOLDER + "gstest-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

TEST_F(ShaderTest, chroma_key2)
{
	float lo = 0.15;
	try {
		PNG img(IMG_FOLDER + "gstest2.png");
		ChromaKeyer keyer(*img.getRGBAPixel(0, 0), lo);
		keyer(img);
		img.writeFile(OUT_FOLDER + "gstest2-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

TEST_F(ShaderTest, grayscale)
{
    try {
        JPEG img(IMG_FOLDER + "test.jpg");
        GrayScaleShader grayer;
        grayer(img);
        img.writeFile(OUT_FOLDER + "grayscale-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, grayscale2)
{
    try {
        JPEG img(IMG_FOLDER + "train.jpg");
        GrayScaleShader grayer;
        grayer(img);
        img.writeFile(OUT_FOLDER + "grayscale2-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, hsl_adjust)
{
    try {
        JPEG img(IMG_FOLDER + "test.jpg");

        HueSatLumAdjust hsl_adjust(-30, 1.3, 0.8);
        hsl_adjust(img);
        img.writeFile(OUT_FOLDER + "hsl-out.jpg");

        hsl_adjust = HueSatLumAdjust(30, 1/1.3, 1/0.8); // return
        hsl_adjust(img);
        img.writeFile(OUT_FOLDER + "hslundo-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, hsl_saturate)
{
    try {
        JPEG img(IMG_FOLDER + "bird.jpg");

        HueSatLumAdjust hsl_adjust(0, 2, 1);
        hsl_adjust(img);
        img.writeFile(OUT_FOLDER + "hsl-sat-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, hsl_inc_lum)
{
    try {
        JPEG img(IMG_FOLDER + "dark.jpg");

        HueSatLumAdjust hsl_adjust(0, 1, 1.8);
        hsl_adjust(img);
        img.writeFile(OUT_FOLDER + "hsl-lum-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, hsl_hue)
{
    try {
        JPEG img(IMG_FOLDER + "sun.jpg");

        HueSatLumAdjust hsl_adjust(-20, 1, 1);
        hsl_adjust(img);
        img.writeFile(OUT_FOLDER + "hsl-hue-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, box_blur_once)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        BoxBlur blur;
        blur(img);
        img.writeFile(OUT_FOLDER + "boxblur-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, fast_blur_wider)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        BoxBlur blur(5);
        blur(img);
        img.writeFile(OUT_FOLDER + "fastblurmore-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}


TEST_F(ShaderTest, fast_blur_seperable)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        BoxBlurHorizontal blurh(10);
        BoxBlurVertical blurv(10);
        blurv(img);
        blurh(img);
        img.writeFile(OUT_FOLDER + "fastblur-seperable-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, gaussian_blur_once)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        GaussianBlur blur(2, 2);
        blur(img);
        img.writeFile(OUT_FOLDER + "gaussian-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, gaussian_blur_long)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        GaussianBlur blur(2, 6);
        blur(img);
        img.writeFile(OUT_FOLDER + "gaussian-vert-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, gaussian_blur_serperable)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        GaussianBlurHorizontal blurh(6);
        GaussianBlurVertical blurv(6);
        blurh(img);
        blurv(img);
        img.writeFile(OUT_FOLDER + "gaussian-seperable-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

//TEST_F(ShaderTest, gaussian_blur_auto)
//{
//    try {
//        JPEG img(IMG_FOLDER + "testblur-small.jpg");
//        GaussianBlur blur(3);
//        blur(img);
//        img.writeFile(OUT_FOLDER + "gaussian-auto-out.jpg");
//
//    }
//    catch (...) {
//        FAIL() << "Failed to write jpg file";
//    }
//}

TEST_F(ShaderTest, gaussian_blur_heavy)
{
    try {
        JPEG img(IMG_FOLDER + "testblur-small.jpg");
        GaussianBlur blur(6);
        blur(img);
        img.writeFile(OUT_FOLDER + "gaussian-heavy-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, sharpen)
{
    try {
        JPEG img(IMG_FOLDER + "testsharp-small.jpg");
        ImageSharpen sharp;
        sharp(img);
        img.writeFile(OUT_FOLDER + "sharp-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, sharpen_light)
{
    try {
        JPEG img(IMG_FOLDER + "testsharp-small.jpg");
        ImageSharpen sharp(0.33);
        sharp(img);
        img.writeFile(OUT_FOLDER + "sharp-light-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, sharpen_lots)
{
    try {
        JPEG img(IMG_FOLDER + "testsharp-small.jpg");
        ImageSharpen sharp(2.5);
        sharp(img);
        img.writeFile(OUT_FOLDER + "sharp-heavy-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, bokeh)
{
    try {
        JPEG img(IMG_FOLDER + "lights.jpg");
        BokehBlur blur(10);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, bokeh_wide)
{
    try {
        JPEG img(IMG_FOLDER + "lights.jpg");
        BokehBlur blur(15, 5);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-wide-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}


TEST_F(ShaderTest, bokeh_alt1)
{
    try {
        JPEG img(IMG_FOLDER + "treelights-small.jpg");
        BokehBlur blur(6);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-alt1-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, bokeh_alt2)
{
    try {
        JPEG img(IMG_FOLDER + "stars-small.jpg");
        BokehBlur blur(10);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-alt2-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, bokeh_alt3)
{
    try {
        JPEG img(IMG_FOLDER + "city-small.jpg");
        BokehBlur blur(3);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-alt3-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

TEST_F(ShaderTest, bokeh_alt4)
{
    try {
        JPEG img(IMG_FOLDER + "lights2.jpg");
        BokehBlur blur(10);
        blur(img);
        img.writeFile(OUT_FOLDER + "bokeh-alt4-out.jpg");

    }
    catch (...) {
        FAIL() << "Failed to write jpg file";
    }
}

