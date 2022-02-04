#include "imagetest.h"

using namespace ::testing;
using namespace image;

/**
* Test class for PNG handling (I/O) and basic functions.
* More complicated functions for image shading, manipulation etc. should be tested sepereately
*/
class PNGTest : public Test
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

const std::string PNGTest::IMG_FOLDER = "../testdata/images/in/";
const std::string PNGTest::OUT_FOLDER = "../testdata/images/out/pngtest/";

/**
* TODO
* - Add non arbitrary exception catch (custom exceptions for image, png etc)
*/

/**
* Basic tests
*/

TEST_F(PNGTest, constructor_null_image)
{
	try {
		PNG img(0, 0);
		FAIL() << "Expected an exception for trying to create a 0 size png";
	}
	catch (...) {
		SUCCEED();
	}
}

TEST_F(PNGTest, constructor_new_square)
{
	try {
		PNG img(100, 100);
		ASSERT_EQ(100, img.width());
		ASSERT_EQ(100, img.height());
		ASSERT_EQ(100*100, img.size());
	}
	catch (...) {
		FAIL();
	}
}

TEST_F(PNGTest, constructor_new_wide)
{
	try {
		PNG img(200, 50);
		ASSERT_EQ(200, img.width());
		ASSERT_EQ(50, img.height());
		ASSERT_EQ(200 * 50, img.size());
	}
	catch (...) {
		FAIL();
	}
}

TEST_F(PNGTest, constructor_new_tall)
{
	try {
		PNG img(360, 180);
		ASSERT_EQ(360, img.width());
		ASSERT_EQ(180, img.height());
		ASSERT_EQ(360*180, img.size());
	}
	catch (...) {
		FAIL();
	}
}

TEST_F(PNGTest, get_pixel_outofbounds)
{
    try {
        PNG img(1, 1);
        img.getRGBAPixel(-1, -1);
        FAIL();
    }
    catch (...) {
        SUCCEED();
    }
}

TEST_F(PNGTest, get_pixel_outofbounds2)
{
    try {
        PNG img(1, 1);
        img.getRGBAPixel(1, 1);
        FAIL();
    }
    catch (...) {
        SUCCEED();
    }
}

TEST_F(PNGTest, set_pixel_outofbounds)
{
    try {
        PNG img(1, 1);
        bool set = img.setRGBAPixel(rgbcolor::TRANSPARENT, -1, -1);
        ASSERT_FALSE(set);
    }
    catch (...) {
        FAIL();
    }
}


TEST_F(PNGTest, set_pixel_outofbounds2)
{
    try {
        PNG img(1, 1);
        bool set = img.setRGBAPixel(rgbcolor::TRANSPARENT, 1, 1);
        ASSERT_FALSE(set);
    }
    catch (...) {
        FAIL();
    }
}

TEST_F(PNGTest, equals_basic)
{
	PNG img1(100, 100);
	PNG img2 = img1;
	ASSERT_TRUE(img1 == img2);
	ASSERT_FALSE(img1 != img2);
}

TEST_F(PNGTest, equals_no)
{
	RGBAPixel color(1, 1, 1, 1);
	PNG img1(100, 100);
	img1.fillSolidColor(color);
	PNG img2 = img1;
	color.setAlpha(0);
	img2.setRGBAPixel(color, 99, 99); // assumes this is not the default
	ASSERT_FALSE(img1 == img2);
	ASSERT_TRUE(img1 != img2);
}

TEST_F(PNGTest, fill_solid_color)
{
	try {
		PNG img(100, 100);
		img.fillSolidColor(rgbcolor::GREY);
		for (unsigned int y = 0; y < img.height(); y++)
		{
			for (unsigned int x = 0; x < img.width(); x++) 
			{
				RGBAPixel* p = img.getRGBAPixel(x, y);
				ASSERT_TRUE(*p == rgbcolor::GREY);
			}
		}
		img.writeFile(OUT_FOLDER + "solid-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, fill_gradient)
{
	try {
		PNG img(100, 100);
		img.fillGradient(rgbcolor::BLUE, rgbcolor::RED);
		for (unsigned int y = 0; y < img.height(); y++)
		{
			float percent_y = static_cast<float>(y) / img.height();
			for (unsigned int x = 0; x < img.width(); x++)
			{
				RGBAPixel* p = img.getRGBAPixel(x, y);
				//float percent_x = static_cast<float>(x) / img.width();
				RGBAPixel expect(percent_y, 0, 1.0 - percent_y, 1);
				ASSERT_TRUE(*p == expect);
			}
		}
		img.writeFile(OUT_FOLDER + "grad-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, fill_gradient_alpha)
{
	try {
		PNG img(100, 100);
		img.fillGradient(rgbcolor::WHITE, rgbcolor::TRANSPARENT);
		for (unsigned int y = 0; y < img.height(); y++)
		{
			float percent_y = static_cast<float>(y) / img.height();
			for (unsigned int x = 0; x < img.width(); x++)
			{
				RGBAPixel* p = img.getRGBAPixel(x, y);
				//float percent_x = static_cast<float>(x) / img.width();
				RGBAPixel expect(1, 1, 1, 1.0 - percent_y);
			}
		}
		img.writeFile(OUT_FOLDER + "grad(alpha)-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

/**
* PNG load tests
*/

TEST_F(PNGTest, load_from_file)
{
	try {
		PNG img(IMG_FOLDER + "test.png");
		// success
	}
	catch (...) {
		FAIL() << "Failed to load png image";
	}
}

TEST_F(PNGTest, load_nosuch_file)
{
	try {
		PNG img2(IMG_FOLDER + "notadirectory.png");
		FAIL() << "Expected a file read exception";
	}
	catch (...) {
		SUCCEED();
	}
}

/**
* PNG write tests
*/


TEST_F(PNGTest, load_and_write)
{
	try {
		PNG img(IMG_FOLDER + "rgb.png");
		img.writeFile(OUT_FOLDER + "rgb-out.png");
		// success
	}
	catch (...) {
		FAIL() << "Failed to load or write png image";
	}
}

TEST_F(PNGTest, load_and_write_nodirectory)
{
	try {
		PNG img(IMG_FOLDER + "rgb.png");
		img.writeFile(OUT_FOLDER + "nodirectoryexists/" + "rgb-out.png");
		FAIL() << "Expected a file write exception";
	}
	catch (...) {
		SUCCEED();
	}
}
TEST_F(PNGTest, large)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.writeFile(OUT_FOLDER + "large-out.png");
		// succeed
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

/**
* PNG function tests
*/

TEST_F(PNGTest, copy_large)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		PNG cpy = img;
		cpy.writeFile(OUT_FOLDER + "copy-out.png");
	}
	catch (...) {
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, resize_small)
{
	try {
		PNG small(IMG_FOLDER + "large.png");
		small.resize(240, 360);
		small.writeFile(OUT_FOLDER + "resize(s)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, scale_small)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.scale(0.2, 0.2);
		img.writeFile(OUT_FOLDER + "scale(s)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, resize_large)
{
	try {
		PNG large(IMG_FOLDER + "large.png");
		large.resize(3000, 3500);
		large.writeFile(OUT_FOLDER + "resize(l)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, scale_large)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.scale(1.5, 1.5);
		img.writeFile(OUT_FOLDER + "scale(l)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, resize_twice)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.resize(240, 360);
		img.resize(3000, 3500);
		img.writeFile(OUT_FOLDER + "resize(back)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, scale_tall)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.scale(0.7, 1.3);
		img.writeFile(OUT_FOLDER + "scale(n)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, scale_wide)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.scale(1.1, 0.6);
		img.writeFile(OUT_FOLDER + "scale(w)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}

TEST_F(PNGTest, mirror_horiz)
{
	try {
		PNG img(IMG_FOLDER + "large.png");
		img.mirror();
		img.writeFile(OUT_FOLDER + "mirror(h)-out.png");
	}
	catch (...)
	{
		FAIL() << "Failed to write png file";
	}
}





