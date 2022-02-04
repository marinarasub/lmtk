#include "imagetest.h"


using namespace ::testing;
using namespace image;

//class HSLAPixelTest : public Test
//{
//protected:
//    HSLAPixel p;
//};

/**
* Constructor tests
*/

TEST(HSLAPixelTest, constructor_flt_zero)
{
    HSLAPixel p = HSLAPixel(0, 0, 0, 0);
    EXPECT_FLOAT_EQ(0, p.h);
    EXPECT_FLOAT_EQ(0, p.s);
    EXPECT_FLOAT_EQ(0, p.l);
    EXPECT_FLOAT_EQ(0, p.a);
}

TEST(HSLAPixelTest, constructor_flt_max)
{
    HSLAPixel p = HSLAPixel(359, 1, 1, 1);
    EXPECT_FLOAT_EQ(359, p.h);
    EXPECT_FLOAT_EQ(1, p.s);
    EXPECT_FLOAT_EQ(1, p.l);
    EXPECT_FLOAT_EQ(1, p.a);
}

TEST(HSLAPixelTest, constructor_flt_mid)
{
    HSLAPixel p = HSLAPixel(180, 0.4, 0.5, 0.6);
    EXPECT_FLOAT_EQ(180, p.h);
    EXPECT_FLOAT_EQ(0.4, p.s);
    EXPECT_FLOAT_EQ(0.5, p.l);
    EXPECT_FLOAT_EQ(0.6, p.a);
}

TEST(HSLAPixelTest, constructor_flt_clamp_under)
{
    HSLAPixel p = HSLAPixel(-30, -0.01, -0.01, -0.01);
    EXPECT_FLOAT_EQ(330, p.h);
    EXPECT_FLOAT_EQ(0, p.s);
    EXPECT_FLOAT_EQ(0, p.l);
    EXPECT_FLOAT_EQ(0, p.a);
}

TEST(HSLAPixelTest, constructor_flt_clamp_over)
{
    HSLAPixel p = HSLAPixel(400, 1.01, 1.01, 1.01);
    EXPECT_FLOAT_EQ(40, p.h);
    EXPECT_FLOAT_EQ(1, p.s);
    EXPECT_FLOAT_EQ(1, p.l);
    EXPECT_FLOAT_EQ(1, p.a);
}

/**
* Other tests
*/

TEST(HSLAPixelTest, equals_no)
{
    HSLAPixel p1 = HSLAPixel(359, 1, 1, 1);
    HSLAPixel p2 = HSLAPixel(0, 0, 0, 0);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
}

TEST(HSLAPixelTest, equals_yes)
{
    HSLAPixel p1 = HSLAPixel(180, 0.4, 0.5, 0.6);
    HSLAPixel p2 = p1;
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(HSLAPixelTest, rgb_to_hsl_black)
{
    RGBAPixel rgb(0, 0, 0, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(0, 0, 0, 1), hsl);
}

TEST(HSLAPixelTest, rgb_to_hsl_grey)
{
    RGBAPixel rgb(0.5, 0.5, 0.5, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(0, 0, 0.5, 1), hsl);
}

TEST(HSLAPixelTest, rgb_to_hsl_white)
{
    RGBAPixel rgb(1, 1, 1, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(0, 0, 1, 1), hsl);
}

TEST(HSLAPixelTest, rgb_to_hsl_red)
{
    RGBAPixel rgb(1, 0, 0, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(0, 1, 0.5, 1), hsl);
}

TEST(HSLAPixelTest, rgb_to_hsl_green)
{
    RGBAPixel rgb(0, 1, 0, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(120, 1, 0.5, 1), hsl);
}

TEST(HSLAPixelTest, rgb_to_hsl_blue)
{
    RGBAPixel rgb(0, 0, 1, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(240, 1, 0.5, 1), hsl);
}

TEST(HSLAPixelTest, rgb_to_hsl_yellow)
{
    RGBAPixel rgb(1, 1, 0, 1);
    HSLAPixel hsl = rgb;
    EXPECT_EQ(HSLAPixel(60, 1, 0.5, 1), hsl);
}