#include "imagetest.h"

using namespace ::testing;
using namespace image;

/**
* Test class for RGBA Pixel (red, green, blue, alpha)
* Tests constructors, comparison, and other basic functions.
*/
class RGBAPixelTest : public Test
{
protected:
	RGBAPixel p;
};

/**
* Constructor tests
*/
TEST(RGBAPixelTest, constructor_uint_basic_max)
{
	RGBAPixel p = RGBAPixel(
        std::numeric_limits<std::uint32_t>::max(), 
        std::numeric_limits<std::uint32_t>::max(),
        std::numeric_limits<std::uint32_t>::max(), 
        std::numeric_limits<std::uint32_t>::max(), 32);
	EXPECT_FLOAT_EQ(1.0, p.r);
	EXPECT_FLOAT_EQ(1.0, p.g);
	EXPECT_FLOAT_EQ(1.0, p.b);
	EXPECT_FLOAT_EQ(1.0, p.a);

	p = RGBAPixel(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 16);
	EXPECT_FLOAT_EQ(1.0, p.r);
	EXPECT_FLOAT_EQ(1.0, p.g);
	EXPECT_FLOAT_EQ(1.0, p.b);
	EXPECT_FLOAT_EQ(1.0, p.a);

	p = RGBAPixel(255, 255, 255, 255, 8);
	EXPECT_FLOAT_EQ(1.0, p.r);
	EXPECT_FLOAT_EQ(1.0, p.g);
	EXPECT_FLOAT_EQ(1.0, p.b);
	EXPECT_FLOAT_EQ(1.0, p.a);

	p = RGBAPixel(15, 15, 15, 15, 4);
	EXPECT_FLOAT_EQ(1.0, p.r);
	EXPECT_FLOAT_EQ(1.0, p.g);
	EXPECT_FLOAT_EQ(1.0, p.b);
	EXPECT_FLOAT_EQ(1.0, p.a);
}

TEST(RGBAPixelTest, constructor_uint_basic_half)
{
	float expect;
	RGBAPixel p = RGBAPixel(
        std::numeric_limits<std::uint32_t>::max()/2, 
        std::numeric_limits<std::uint32_t>::max()/2, 
        std::numeric_limits<std::uint32_t>::max()/2, 
        std::numeric_limits<std::uint32_t>::max()/2, 32);
	expect = (float) (
        std::numeric_limits<std::uint32_t>::max()/2) / 
        std::numeric_limits<std::uint32_t>::max();
	EXPECT_FLOAT_EQ(expect, p.r);
	EXPECT_FLOAT_EQ(expect, p.g);
	EXPECT_FLOAT_EQ(expect, p.b);
	EXPECT_FLOAT_EQ(expect, p.a);

	p = RGBAPixel(255/2, 255/2, 255/2, 255/2, 8);
	expect = (float) (255 / 2) / 255;
	EXPECT_FLOAT_EQ(expect, p.r);
	EXPECT_FLOAT_EQ(expect, p.g);
	EXPECT_FLOAT_EQ(expect, p.b);
	EXPECT_FLOAT_EQ(expect, p.a);

	p = RGBAPixel(7, 7, 7, 7, 4);
	expect = (float) 7 / 15;
	EXPECT_FLOAT_EQ(expect, p.r);
	EXPECT_FLOAT_EQ(expect, p.g);
	EXPECT_FLOAT_EQ(expect, p.b);
	EXPECT_FLOAT_EQ(expect, p.a);
}

TEST(RGBAPixelTest, constructor_uint_zero)
{
	RGBAPixel p;
	for (int d = 1; d <= 32; d = d * 2)
	{
		p = RGBAPixel(0, 0, 0, 0, d);
		EXPECT_FLOAT_EQ(0, p.r);
		EXPECT_FLOAT_EQ(0, p.g);
		EXPECT_FLOAT_EQ(0, p.b);
		EXPECT_FLOAT_EQ(0, p.a);
	}
}

TEST(RGBAPixelTest, constructor_flt_basic)
{
	RGBAPixel p = RGBAPixel(1, 1, 1, 1);
	EXPECT_FLOAT_EQ(1.0, p.r);
	EXPECT_FLOAT_EQ(1.0, p.g);
	EXPECT_FLOAT_EQ(1.0, p.b);
	EXPECT_FLOAT_EQ(1.0, p.a);

	p = RGBAPixel(0.5, 0.5, 0.5, 0.5);
	EXPECT_FLOAT_EQ(0.5, p.r);
	EXPECT_FLOAT_EQ(0.5, p.g);
	EXPECT_FLOAT_EQ(0.5, p.b);
	EXPECT_FLOAT_EQ(0.5, p.a);

	p = RGBAPixel(0, 0, 0, 0);
	EXPECT_FLOAT_EQ(0, p.r);
	EXPECT_FLOAT_EQ(0, p.g);
	EXPECT_FLOAT_EQ(0, p.b);
	EXPECT_FLOAT_EQ(0, p.a);
}

TEST(RGBAPixelTest, constructor_flt_varied)
{
	RGBAPixel p = RGBAPixel(0.8, 0.6, 0.4, 0.2);
	EXPECT_FLOAT_EQ(0.8, p.r);
	EXPECT_FLOAT_EQ(0.6, p.g);
	EXPECT_FLOAT_EQ(0.4, p.b);
	EXPECT_FLOAT_EQ(0.2, p.a);

	p = RGBAPixel(0.1, 0.3, 0.5, 0.7);
	EXPECT_FLOAT_EQ(0.1, p.r);
	EXPECT_FLOAT_EQ(0.3, p.g);
	EXPECT_FLOAT_EQ(0.5, p.b);
	EXPECT_FLOAT_EQ(0.7, p.a);

	p = RGBAPixel(0, 1, 0.33, 0.47);
	EXPECT_FLOAT_EQ(0, p.r);
	EXPECT_FLOAT_EQ(1, p.g);
	EXPECT_FLOAT_EQ(0.33, p.b);
	EXPECT_FLOAT_EQ(0.47, p.a);
}

TEST(RGBAPixelTest, constructor_flt_edge)
{
	float max = 0.99999;
	float min = 0.00001;
	RGBAPixel p = RGBAPixel(max, max, max, max);
	EXPECT_FLOAT_EQ(max, p.r);
	EXPECT_FLOAT_EQ(max, p.g);
	EXPECT_FLOAT_EQ(max, p.b);
	EXPECT_FLOAT_EQ(max, p.a);

	p = RGBAPixel(min, min, min, min);
	EXPECT_FLOAT_EQ(min, p.r);
	EXPECT_FLOAT_EQ(min, p.g);
	EXPECT_FLOAT_EQ(min, p.b);
	EXPECT_FLOAT_EQ(min, p.a);
}

/**
* Function tests
*/

TEST(RGBAPixelTest, equals_no)
{
	RGBAPixel p1, p2;
	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = RGBAPixel(1, 1, 1, 1);
	EXPECT_FALSE(p1 == p2);
	EXPECT_TRUE(p1 != p2);
}

TEST(RGBAPixelTest, equals_no_alpha)
{
	RGBAPixel p1, p2;
	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = p1;
	p2.setAlpha(1);
	EXPECT_FALSE(p1 == p2);
	EXPECT_TRUE(p1 != p2);
}

TEST(RGBAPixelTest, equals_yes)
{
	RGBAPixel p1, p2;
	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = p1;
	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 != p2);

	p1 = RGBAPixel(1, 1, 1, 1);
	p2 = p1;
	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 != p2);

	p1 = RGBAPixel(0.2, 0.4, 0.6, 0.8);
	p2 = p1;
	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 != p2);
}

TEST(RGBAPixelTest, distance_basic)
{
	RGBAPixel p1, p2;
	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = RGBAPixel(1, 1, 1, 1);
	EXPECT_FLOAT_EQ(sqrt(3) , p1.dist(p2));

	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = RGBAPixel(p1);
	EXPECT_FLOAT_EQ(0, p1.dist(p2));
}

TEST(RGBAPixelTest, distance_alpha)
{
	RGBAPixel p1, p2;
	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = RGBAPixel(0, 0, 0, 1);
	EXPECT_FLOAT_EQ(0, p1.dist(p2));

	p1 = RGBAPixel(0, 0, 0, 0);
	p2 = RGBAPixel(1, 1, 1, 0);
	EXPECT_FLOAT_EQ(sqrt(3), p1.dist(p2));
}

TEST(RGBAPixelTest, distance_varied)
{
	RGBAPixel p1, p2;
	p1 = RGBAPixel(0.1, 0.2, 0.3, 0.4);
	p2 = RGBAPixel(0.2, 0.4, 0.6, 0.8);
	EXPECT_FLOAT_EQ(sqrt(0.1 * 0.1 + 0.2 * 0.2 + 0.3 * 0.3), p1.dist(p2));

	p1 = RGBAPixel(0.1, 0.2, 0.3, 1);
	p2 = RGBAPixel(0.05, 0.14, 0.23, 0);
	EXPECT_FLOAT_EQ(sqrt(0.05 * 0.05 + 0.06 * 0.06 + 0.07 * 0.07), p1.dist(p2));
}

TEST(RGBAPixelTest, clamp_same)
{
	RGBAPixel p(0, 0, 0, 0);
	EXPECT_TRUE(p == RGBAPixel(0, 0, 0, 0)) << p.to_string();

	p.set(0.5, 0.5, 0.5, 0.5);
	EXPECT_TRUE(p == RGBAPixel(0.5, 0.5, 0.5, 0.5)) << p.to_string();

	p.set(1, 1, 1, 1);
	EXPECT_TRUE(p == RGBAPixel(1, 1, 1, 1)) << p.to_string();
}

TEST(RGBAPixelTest, clamp_max)
{
	RGBAPixel p(2, 2, 2, 2);
	RGBAPixel max(1, 1, 1, 1);
	EXPECT_TRUE(p == max) << p.to_string();
}

TEST(RGBAPixelTest, clamp_min)
{
	RGBAPixel p(-1, -1, -1, -1);
	RGBAPixel min(0, 0, 0, 0);
	EXPECT_TRUE(p == min) << p.to_string();
}

TEST(RGBAPixelTest, clamp_max_edge)
{
	RGBAPixel p;
	RGBAPixel max(1, 1, 1, 1);
	p.set(0.99999, 0.99999, 0.99999, 0.99999);
	EXPECT_FALSE(p == max) << p.to_string();
	p.set(1.00001, 1.00001, 1.00001, 1.00001);
	EXPECT_TRUE(p == max) << p.to_string();
}

TEST(RGBAPixelTest, clamp_min_edge)
{
	RGBAPixel p;
	RGBAPixel min(0, 0, 0, 0);
	p.set(0.00001, 0.00001, 0.00001, 0.00001);
	EXPECT_FALSE(p == min) << p.to_string();
	p.set(-0.00001, -0.00001, -0.00001, -0.00001);
	EXPECT_TRUE(p == min) << p.to_string();
}

TEST(RGBAPixelTest, clamp_channel_min)
{
	RGBAPixel p;
	p.set(-1, 0.5, 0.5, 0.5);
	EXPECT_TRUE(p == RGBAPixel(0, 0.5, 0.5, 0.5)) << p.to_string();
	p.set(0.5, -1, 0.5, 0.5);
	EXPECT_TRUE(p == RGBAPixel(0.5, 0, 0.5, 0.5)) << p.to_string();
	p.set(0.5, 0.5, -1, 0.5);
	EXPECT_TRUE(p == RGBAPixel(0.5, 0.5, 0, 0.5)) << p.to_string();
	p.set(0.5, 0.5, 0.5, -1);
	EXPECT_TRUE(p == RGBAPixel(0.5, 0.5, 0.5, 0)) << p.to_string();
}

TEST(RGBAPixelTest, clamp_channel_max)
{
	RGBAPixel p;
	p.set(2, 0.5, 0.5, 0.5);
	EXPECT_TRUE(p == RGBAPixel(1, 0.5, 0.5, 0.5)) << p.to_string();
	p.set(0.5, 2, 0.5, 0.5);
	EXPECT_TRUE(p == RGBAPixel(0.5, 1, 0.5, 0.5)) << p.to_string();
	p.set(0.5, 0.5, 2, 0.5);
	EXPECT_TRUE(p == RGBAPixel(0.5, 0.5, 1, 0.5)) << p.to_string();
	p.set(0.5, 0.5, 0.5, 2);
	EXPECT_TRUE(p == RGBAPixel(0.5, 0.5, 0.5, 1)) << p.to_string();
}

TEST(RGBAPixelTest, clamp_NaN) 
{
	RGBAPixel p(0.5, 0.5, 0.5, 0.5);
	p.set(NAN, NAN, NAN, NAN);
	EXPECT_TRUE(p == RGBAPixel(1, 1, 1, 1)) << p.to_string();
}

TEST(RGBAPixelTest, hsl_to_rgb_black)
{
    HSLAPixel hsl(0, 0, 0, 1);
    RGBAPixel rgb = hsl;
    EXPECT_EQ(RGBAPixel(0, 0, 0, 1), rgb);
}

TEST(RGBAPixelTest, hsl_to_rgb_white)
{
    HSLAPixel hsl(0, 0, 1, 1);
    RGBAPixel rgb = hsl;
    EXPECT_EQ(RGBAPixel(1, 1, 1, 1), rgb);
}

TEST(RGBAPixelTest, hsl_to_rgb_red)
{
    HSLAPixel hsl(0, 1, 0.5, 1);
    RGBAPixel rgb = hsl;
    EXPECT_EQ(RGBAPixel(1, 0, 0, 1), rgb);
}

TEST(RGBAPixelTest, hsl_to_rgb_green)
{
    HSLAPixel hsl(120, 1, 0.5, 1);
    RGBAPixel rgb = hsl;
    EXPECT_EQ(RGBAPixel(0, 1, 0, 1), rgb);
}

TEST(RGBAPixelTest, hsl_to_rgb_blue)
{
    HSLAPixel hsl(240, 1, 0.5, 1);
    RGBAPixel rgb = hsl;
    EXPECT_EQ(RGBAPixel(0, 0, 1, 1), rgb);
}

TEST(RGBAPixelTest, hsl_to_rgb_yellow)
{
    HSLAPixel hsl(60, 1, 0.5, 1);
    RGBAPixel rgb = hsl;
    EXPECT_EQ(RGBAPixel(1, 1, 0, 1), rgb);
}

TEST(RGBAPixelTest, navg_one)
{
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::naverage(&white, 1);
	EXPECT_EQ(white, avg);
}

TEST(RGBAPixelTest, navg_two)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel arr[] = { black, white };
	RGBAPixel avg = RGBAPixel::naverage(arr, 2);
	EXPECT_EQ(RGBAPixel(0.5, 0.5, 0.5, 0.5), avg);
}

TEST(RGBAPixelTest, avg_two)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::average(black, white);
	EXPECT_EQ(RGBAPixel(0.5, 0.5, 0.5, 0.5), avg);
}

TEST(RGBAPixelTest, navg_two_varied)
{
	RGBAPixel p1(0, 0.2, 0.5, 0.9);
	RGBAPixel p2(0.1, 0.4, 0.8, 0.99);
	RGBAPixel arr[] = { p1, p2 };
	RGBAPixel avg = RGBAPixel::naverage(arr, 2);
	EXPECT_EQ(RGBAPixel(0.1/2, (0.2+0.4)/2, (0.5+0.8)/2, (0.9+0.99)/2), avg);
}

TEST(RGBAPixelTest, avg_two_varied)
{
	RGBAPixel p1(0, 0.2, 0.5, 0.9);
	RGBAPixel p2(0.1, 0.4, 0.8, 0.99);
	RGBAPixel avg = RGBAPixel::average(p1, p2);
	EXPECT_EQ(RGBAPixel(0.1 / 2, (0.2 + 0.4) / 2, (0.5 + 0.8) / 2, (0.9 + 0.99) / 2), avg);
}

TEST(RGBAPixelTest, wavg_two_balanced)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::weighted_average(black, white, 1, 1);
	EXPECT_EQ(RGBAPixel(0.5, 0.5, 0.5, 0.5), avg);
}

TEST(RGBAPixelTest, wavg_two_biased_zero)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::weighted_average(black, white, 0, 0);
	EXPECT_EQ(RGBAPixel(0, 0, 0, 0), avg);
}

TEST(RGBAPixelTest, wavg_two_only_first)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::weighted_average(black, white, 1, 0);
	EXPECT_EQ(RGBAPixel(0, 0, 0, 0), avg);
}

TEST(RGBAPixelTest, wavg_two_only_second)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::weighted_average(black, white, 0, 1);
	EXPECT_EQ(RGBAPixel(1, 1, 1, 1), avg);
}

TEST(RGBAPixelTest, wavg_two_biased_first)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::weighted_average(black, white, 2, 1);
	EXPECT_EQ(RGBAPixel(1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0), avg);
}

TEST(RGBAPixelTest, wavg_two_biased_second)
{
	RGBAPixel black(0, 0, 0, 0);
	RGBAPixel white(1, 1, 1, 1);
	RGBAPixel avg = RGBAPixel::weighted_average(black, white, 1, 2);
	EXPECT_EQ(RGBAPixel(2.0 / 3.0, 2.0 / 3.0, 2.0 / 3.0, 2.0 / 3.0), avg);
}

TEST(RGBAPixelTest, wavg_two_biased_negative)
{
	float w1 = -2;
	float w2 = 1;
	float tw = w1 + w2;
	RGBAPixel p1(0.1, 0.2, 0.3, 0.4);
	RGBAPixel p2(0.8, 0.7, 0.6, 0.5);
	RGBAPixel avg = RGBAPixel::weighted_average(p1, p2, w1, w2);
	EXPECT_EQ(RGBAPixel(
		((w1 * p1.r) + (w2 * p2.r)) / tw,
		((w1 * p1.g) + (w2 * p2.g)) / tw,
		((w1 * p1.b) + (w2 * p2.b)) / tw,
		((w1 * p1.a) + (w2 * p2.a)) / tw), avg);
}

TEST(RGBAPixelTest, wavg_two_varied)
{
	float w1 = 0.5;
	float w2 = 2.5;
	float tw = w1 + w2;
	RGBAPixel p1(0, 0.2, 0.5, 0.9);
	RGBAPixel p2(0.1, 0.4, 0.8, 0.99);
	RGBAPixel avg = RGBAPixel::weighted_average(p1, p2, w1, w2);
	EXPECT_EQ(RGBAPixel(
		((w1 * p1.r) + (w2 * p2.r)) / tw,
		((w1 * p1.g) + (w2 * p2.g)) / tw,
		((w1 * p1.b) + (w2 * p2.b)) / tw,
		((w1 * p1.a) + (w2 * p2.a)) / tw), avg);
}

TEST(RGBAPixelTest, wavg_two_many_weights)
{
	constexpr float LIMIT = 5.0;
	constexpr float DL = 0.1;
	RGBAPixel p1(0, 0.2, 0.5, 0.9);
	RGBAPixel p2(0.1, 0.4, 0.8, 0.99);

	for (float w1 = -LIMIT; w1 < LIMIT; w1 += DL)
	{
		for (float w2 = -LIMIT; w2 < LIMIT; w2 += DL)
		{
			float tw = w1 + w2;
			if (tw == 0) continue;
			RGBAPixel avg = RGBAPixel::weighted_average(p1, p2, w1, w2);
			RGBAPixel expect(
				((w1 * p1.r) + (w2 * p2.r)) / tw,
				((w1 * p1.g) + (w2 * p2.g)) / tw,
				((w1 * p1.b) + (w2 * p2.b)) / tw,
				((w1 * p1.a) + (w2 * p2.a)) / tw);
			// use float compare 
			ASSERT_FLOAT_EQ(expect.r, avg.r);
			ASSERT_FLOAT_EQ(expect.g, avg.g);
			ASSERT_FLOAT_EQ(expect.b, avg.b);
			ASSERT_FLOAT_EQ(expect.a, avg.a);
		}
	}
}

TEST(RGBAPixelTest, navg_many)
{
	constexpr int SIZE = 100;
	RGBAPixel arr[SIZE];
	float r_avg = 0, g_avg = 0, b_avg = 0, a_avg = 0;
	for (int i = 0; i < SIZE; i++)
	{
		float r = (float) i / SIZE;
		float g = (float) sqrt(i) / SIZE;
		float b = (float) log(i + 1) / SIZE;
		float a = (float) (SIZE - i) / SIZE;
		arr[i] = RGBAPixel(r, g, b, a);
		r_avg += r;
		g_avg += g;
		b_avg += b;
		a_avg += a;
	}
	r_avg /= SIZE;
	g_avg /= SIZE;
	b_avg /= SIZE;
	a_avg /= SIZE;
	RGBAPixel avg = RGBAPixel::naverage(arr, SIZE);
	EXPECT_EQ(RGBAPixel(r_avg, g_avg, b_avg, a_avg), avg);
}

TEST(RGBAPixelTest, wnavg_many)
{
	constexpr int SIZE = 100;
	RGBAPixel arr[SIZE];
	float weights[SIZE];
	float tw = 0;
	float r_avg = 0, g_avg = 0, b_avg = 0, a_avg = 0;
	for (int i = 0; i < SIZE; i++)
	{
		float r = (float) i / SIZE;
		float g = (float) sqrt(i) / SIZE;
		float b = (float) log(i + 1) / SIZE;
		float a = (float) (SIZE - i) / SIZE;
		arr[i] = RGBAPixel(r, g, b, a);
		weights[i] = i % (SIZE / 4);
		r_avg += weights[i] * r;
		g_avg += weights[i] * g;
		b_avg += weights[i] * b;
		a_avg += weights[i] * a;
		tw += weights[i];
	}
	r_avg /= tw;
	g_avg /= tw;
	b_avg /= tw;
	a_avg /= tw;
	RGBAPixel avg = RGBAPixel::weighted_naverage(arr, weights, SIZE);
	EXPECT_EQ(RGBAPixel(r_avg, g_avg, b_avg, a_avg), avg) << "Total weight: " << tw;
}