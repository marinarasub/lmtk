#include "utilstest.h"
#include <string>


using namespace utils;

TEST(UtilsTest, uint_max) 
{
    for (size_t i = 1; i <= 32; i++)
    {
        uint32_t expect = 0;
        uint32_t actual = uint_max_val(i);
        for (size_t k = 0; k < i; k++)
        {
            expect <<= 1;
            expect |= 1;
        }
        EXPECT_EQ(expect, actual) << "Bit Depth: " << i << " :: Expected: " 
            << expect << ", Actual: " << actual;
    }
}

TEST(UtilsTest, uint_max_zero)
{
    uint32_t expect = 0xFFFFFFFF; // treat as "unspecified"
    uint32_t actual = uint_max_val(0);
    EXPECT_EQ(expect, actual) << "Bit Depth: " << 0 << " :: Expected: "
        << expect << ", Actual: " << actual;
}

TEST(UtilsTest, uint_max_over)
{
    constexpr size_t UPPER_LIMIT = 100;
    for (size_t i = 33; i <= UPPER_LIMIT; i++)
    {
        uint32_t expect = 0xFFFFFFFF;
        uint32_t actual = uint_max_val(i);
        EXPECT_EQ(expect, actual) << "Bit Depth: " << i << " :: Expected: "
            << expect << ", Actual: " << actual;
    }
}

TEST(UtilsTest, ulong_pwr2_zero)
{
    uint64_t expect = 1;
    uint64_t actual = uint64_next_pwr2(0);
    EXPECT_EQ(expect, actual);
}

TEST(UtilsTest, ulong_pwr2_even_basic)
{
    uint64_t expect = 2;
    uint64_t actual = uint64_next_pwr2(2);
    EXPECT_EQ(expect, actual);
    expect = 8;
    actual = uint64_next_pwr2(6);
    EXPECT_EQ(expect, actual);
}

TEST(UtilsTest, ulong_pwr2_odd_basic)
{
    uint64_t expect = 8;
    uint64_t actual = uint64_next_pwr2(5);
    EXPECT_EQ(expect, actual);
    expect = 4;
    actual = uint64_next_pwr2(3);
    EXPECT_EQ(expect, actual);
}

TEST(UtilsTest, ulong_pwr2_pwr2)
{
    // expect same value returned
    uint64_t expect;
    uint64_t actual;
    
    for (size_t i = 1; i <= 64; i*=2)
    {
        expect = i;
        actual = uint64_next_pwr2(i);
        EXPECT_EQ(expect, actual);
    }
}

TEST(UtilsTest, ulong_pwr2_even)
{
    uint64_t expect;
    uint64_t actual;
    expect = 1;
    for (size_t i = 0; i <= 64; i += 2)
    {
        while (i > expect) expect *= 2;
        actual = uint64_next_pwr2(i);
        EXPECT_EQ(expect, actual);
    }
}

TEST(UtilsTest, ulong_pwr2_odd)
{
    uint64_t expect;
    uint64_t actual;
    expect = 1;
    for (size_t i = 1; i <= 64; i += 2)
    {
        while (i > expect) expect *= 2;
        actual = uint64_next_pwr2(i);
        EXPECT_EQ(expect, actual);
    }
}

TEST(UtilsTest, uint_ulong_pwr2)
{
    uint32_t small;
    uint64_t big;
    for (uint64_t i = 1; i <= std::numeric_limits<std::uint32_t>::max(); i*=2)
    {
        small = (uint32_t)i-1;
        big = i-1;
        EXPECT_EQ(uint64_next_pwr2(big), uint64_next_pwr2(small));
    }
}

TEST(UtilsTest, uint_ulong_stress)
{
    uint32_t small;
    uint64_t big;
    for (uint64_t i = 1; i <= (std::numeric_limits<std::uint16_t>::max() << 8); i++)
    {
        small = (uint32_t)i;
        big = i;
        EXPECT_EQ(uint64_next_pwr2(big), uint64_next_pwr2(small));
    }
}

/**
* UTILS MATH TESTS BELOW
*/

// WARNING: i is imaginary unit here, e is euler do not use for index etc.
using namespace utils::math;

#define i IMAGINARY_UNIT
#define i_f IMAGINARY_UNIT_F
#define e EULER

TEST(UtilsMathTest, imaginary)
{
    EXPECT_EQ(complex(-1,0), i * i);
    EXPECT_EQ(complexf(-1, 0), i_f * i_f);
}

TEST(UtilsMathTest, complex_of_real)
{
    EXPECT_EQ(real_to_complex(0), complex(0, 0));
    EXPECT_EQ(real_to_complex(1), complex(1, 0));
    EXPECT_EQ(real_to_complex(-1), complex(-1, 0));
    EXPECT_EQ(real_to_complex(-1), i * i);
}

TEST(UtilsMathTest, sqr_trivial)
{
    EXPECT_DOUBLE_EQ(0, sqr(0));
    EXPECT_DOUBLE_EQ(1, sqr(1));
    EXPECT_DOUBLE_EQ(1, sqr(-1));

    EXPECT_FLOAT_EQ(0, sqrf(0));
    EXPECT_FLOAT_EQ(1.0f, sqrf(1));
    EXPECT_FLOAT_EQ(1.0f, sqrf(-1));
}

TEST(UtilsMathTest, sqr_real)
{
    constexpr double UPPER_LIMIT = 100;
    constexpr double DX = 0.1;
    for (double k = 0; k < UPPER_LIMIT; k += DX) 
    {
        EXPECT_DOUBLE_EQ(k*k, sqr(k));
    }

    for (float k = 0; k < UPPER_LIMIT; k += DX) 
    {
        EXPECT_FLOAT_EQ(k * k, sqrf(k));
    }
}

TEST(UtilsMathTest, complex_sqr_trivial)
{
    EXPECT_EQ(real_to_complex(0), sqr(complex(0, 0)));
    EXPECT_EQ(real_to_complexf(0), sqrf(complexf(0, 0)));
    EXPECT_EQ(real_to_complex(-1), sqr(i));
    EXPECT_EQ(real_to_complexf(-1), sqrf(i_f));
}

TEST(UtilsMathTest, complex_sqr)
{
    constexpr double UPPER_LIMIT = 40;
    constexpr double DX = 0.1;
    for (double k = 0; k < UPPER_LIMIT; k += DX) 
    {
        for (double j = 0; j < UPPER_LIMIT; j += DX) 
        {
            EXPECT_EQ(complex(k,j) * complex(k, j), sqr(complex(k,j)));
        }
    }
    for (float k = 0; k < UPPER_LIMIT; k += DX) 
    {
        for (float j = 0; j < UPPER_LIMIT; j += DX) 
        {
            EXPECT_EQ(complexf(k, j) * complexf(k, j), sqrf(complexf(k, j)));
        }
    }
}

TEST(UtilsMathTest, dist_zero)
{
    double x1, x2, y1, y2;
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    double d = dist(x1, y1, x2, y2);
    EXPECT_DOUBLE_EQ(0, d);
}

TEST(UtilsMathTest, dist_345)
{
    double x1, x2, y1, y2;
    x1 = 0;
    x2 = 3.0;
    y1 = 0;
    y2 = 4.0;
    double d = dist(x1, y1, x2, y2);
    EXPECT_DOUBLE_EQ(5.0, d);
}

TEST(UtilsMathTest, dist_345_offset)
{
    double x1, x2, y1, y2;
    x1 = 0.5;
    x2 = 3.5;
    y1 = 1.0;
    y2 = 5.0;
    double d = dist(x1, y1, x2, y2);
    EXPECT_DOUBLE_EQ(5.0, d);
}

// warning: very slow
TEST(UtilsMathTest, dist_sqrt)
{
    double x1, x2, y1, y2;

    constexpr double UPPER_LIMIT = 5.0;
    constexpr double DX = 0.1;

    double k, j, l, m;
    for (k = -UPPER_LIMIT; k < UPPER_LIMIT; k += DX)
    {
        for (j = -UPPER_LIMIT; j < UPPER_LIMIT; j += DX)
        {
            for (l = -UPPER_LIMIT; l < UPPER_LIMIT; l += DX)
            {
                for (m = -UPPER_LIMIT; m < UPPER_LIMIT; m += DX)
                {
                    x1 = k;
                    x2 = j;
                    y1 = l;
                    y2 = m;
                    double d = dist(x1, y1, x2, y2);
                    EXPECT_DOUBLE_EQ(
                        sqrt(
                            (x2 - x1) * (x2 - x1) +
                            (y2 - y1) * (y2 - y1)), 
                        d);
                }
            }
        }
    }
}

//TEST(UtilsMathTest, round_zero)
//{
//    constexpr int MAX_PRECISION = 100;
//    double num = 0;
//    for (int k = 0; k < MAX_PRECISION; k++)
//    {
//        ASSERT_EQ(0, precision_round(num, k));
//    }
//}
//
//TEST(UtilsMathTest, round_one_decimal)
//{
//    double expect = 0.1;
//    double num;
//
//    num = 0.1;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = 0.11;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = 0.111;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = 0.1111111111111111111;
//    EXPECT_EQ(expect, precision_round(num, 1));
//}
//
//TEST(UtilsMathTest, round_zero_precision)
//{
//    for (double d = -100; d < 100; d += 0.00001)
//    {
//        ASSERT_DOUBLE_EQ(d, precision_round(d, 0));
//    }
//}
//
//TEST(UtilsMathTest, round_up_down)
//{
//    double expect = 0.1;
//    double num;
//
//    num = 0.05;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = 0.099999;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = expect;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = 0.1499999;
//    EXPECT_EQ(expect, precision_round(num, 1));
//}
//
//TEST(UtilsMathTest, round_up_down_negative)
//{
//    double expect = -0.1;
//    double num;
//
//    num = -0.05;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = -0.099999;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = expect;
//    EXPECT_EQ(expect, precision_round(num, 1));
//
//    num = -0.1499999;
//    EXPECT_EQ(expect, precision_round(num, 1));
//}
//
//TEST(UtilsMathTest, round_negative_precision)
//{
//    double num = 12345.6789;
//    EXPECT_EQ(12350, precision_round(num, -1));
//
//    EXPECT_EQ(12300, precision_round(num, -2));
//
//    EXPECT_EQ(12000, precision_round(num, -3));
//
//    EXPECT_EQ(10000, precision_round(num, -4));
//}
//
//TEST(UtilsMathTest, round_not_enough_precision)
//{
//    double num = 0;
//    EXPECT_THROW(precision_round(num, 1), std::logic_error);
//}

TEST(UtilsMathTest, sum_zero_elements)
{
    double arr[1] = { 9999 };
    EXPECT_DOUBLE_EQ(0, nsum(arr, 0));

    float arrf[1] = { 9999 };
    EXPECT_FLOAT_EQ(0, nsumf(arrf, 0));
}

TEST(UtilsMathTest, sum_zero)
{
    double arr[1] = { 0 };
    EXPECT_DOUBLE_EQ(0, nsum(arr, 1));

    float arrf[1] = { 0 };
    EXPECT_FLOAT_EQ(0, nsumf(arrf, 1));
}

TEST(UtilsMathTest, sum_one_element)
{
    double arr[1] = { -1 };
    EXPECT_DOUBLE_EQ(arr[0], nsum(arr, 1));

    float arrf[1] = { -1 };
    EXPECT_FLOAT_EQ(arrf[0], nsumf(arrf, 1));
}

TEST(UtilsMathTest, sum_n_element)
{
    constexpr double LIMIT = 100;
    constexpr double DX = 0.1;
    double sum = 0;
    float sumf = 0;
    std::vector<double> arr;
    std::vector<float> arrf;
    for (double k = -LIMIT; k < LIMIT; k+=DX)
    {
        sum += k;
        arr.push_back(k);
    }
    EXPECT_DOUBLE_EQ(sum, nsum(arr.data(), arr.size()));
    for (float k = -LIMIT; k < LIMIT; k += DX)
    {
        sumf += k;
        arrf.push_back(k);
    }
    EXPECT_FLOAT_EQ(sumf, nsumf(arrf.data(), arrf.size()));
}

TEST(UtilsMathTest, gaussian_trivial_1d)
{
    double sigma = 1.0;
    double mean = 0;
    double res = gaussian(mean, sigma, 0);
    EXPECT_DOUBLE_EQ(1.0 / sqrt(2 * PI), res);
}

TEST(UtilsMathTest, gaussian_sigma_1d)
{
    constexpr double UPPER_LIMIT = 100;
    constexpr double DX = 0.1;

    double sigma; // 0 is undef.
    double mean = 0;
    for (sigma = 0.1; sigma < UPPER_LIMIT; sigma += DX)
    {
        double res = gaussian(mean, sigma, 0);
        EXPECT_DOUBLE_EQ(1.0 / (sigma * sqrt(2 * PI)), res);
    }
}

TEST(UtilsMathTest, gaussian_mean_1d)
{
    constexpr double UPPER_LIMIT = 100;
    constexpr double DX = 0.1;

    double sigma = 1.0; // 0 is undef.
    double mean;
    for (mean = 0.1; mean < UPPER_LIMIT; mean += DX)
    {
        double res = gaussian(mean, sigma, mean);
        EXPECT_DOUBLE_EQ(1.0 / sqrt(2 * PI), res);
    }
}

TEST(UtilsMathTest, gaussian_1d)
{
    constexpr double UPPER_LIMIT = 100;
    constexpr double DX = 0.1;

    double sigma = 1.0; // 0 is undef.
    double mean = 0;
    for (double x = 0.1; x < UPPER_LIMIT; x += DX)
    {
        double res = gaussian(mean, sigma, x);
        double exp = 1.0 / sqrt(2 * PI) * pow(e, -sqr(x - mean) / 2);
        EXPECT_DOUBLE_EQ(exp, res);
    }
}

TEST(UtilsMathTest, gaussian_trivial_2d)
{
    double sigma_x = 1.0, sigma_y = 1.0;
    double mean_x = 0, mean_y = 0;
    double res = gaussian2d(mean_x,
        mean_y,
        sigma_x,
        sigma_y,
        0,
        0);
    EXPECT_DOUBLE_EQ(1.0 / (2 * PI), res);
}

TEST(UtilsMathTest, gaussian_2d)
{
    constexpr double UPPER_LIMIT = 10;
    constexpr double DX = 0.1;

    double sigma = 1.0; // 0 is undef.
    double mean = 0;
    for (double x = 0.1; x < UPPER_LIMIT; x += DX)
    {
        for (double y = 0.1; y < UPPER_LIMIT; y += DX)
        {
            double res = gaussian2d(mean,
                mean,
                sigma,
                sigma,
                x,
                y);
            double exp = 1.0 / (2 * PI) * pow(e, (-sqr(x - mean) / 2) + (-sqr(y - mean) / 2));
            EXPECT_DOUBLE_EQ(exp, res);
        }
    }
}


// file ext tests

TEST(FileTest, file_extension_blank)
{
    std::string name = "";
    EXPECT_EQ("", file_extension(name));
}

TEST(FileTest, file_extension_no_ext)
{
    std::string name = "Makefile";
    EXPECT_EQ("", file_extension(name));

    name = "main";
    EXPECT_EQ("", file_extension(name));
}

TEST(FileTest, file_extension_empty_ext)
{
    std::string name = "name.";
    EXPECT_EQ("", file_extension(name));
}

TEST(FileTest, file_extension_lengths)
{
    std::string name = "file.";

    name.append("a");
    EXPECT_EQ("a", file_extension(name));

    name.append("b");
    EXPECT_EQ("ab", file_extension(name));

    name.append("1");
    EXPECT_EQ("ab1", file_extension(name));

    name.append("$");
    EXPECT_EQ("ab1$", file_extension(name));
}

TEST(FileTest, file_extension_yes_ext)
{
    std::string name = "file.xxx";
    EXPECT_EQ("xxx", file_extension(name));
}

TEST(FileTest, file_extension_path_ext)
{
    std::string name = "C:/somefolder/anotherone/file.mp3";
    EXPECT_EQ("mp3", file_extension(name));
}

TEST(FileTest, file_extension_path_ext2)
{
    std::string name = "C:\\somefolder\\anotherone\\file.flac";
    EXPECT_EQ("flac", file_extension(name));
}


TEST(FileTest, file_extension_common_ext)
{
    std::string name;

    name = "image.png";
    EXPECT_EQ("png", file_extension(name));

    name = "01.jpg";
    EXPECT_EQ("jpg", file_extension(name));

    name = "CMakeLists.txt";
    EXPECT_EQ("txt", file_extension(name));
}


TEST(FileTest, file_extension_only_ext)
{
    std::string name = ".gitignore";
    EXPECT_EQ("gitignore", file_extension(name));
}

TEST(FileTest, file_extension_multiple_dot)
{
    std::string name = "backup.psd.bak";
    EXPECT_EQ("bak", file_extension(name));
}

TEST(FileTest, file_extension_only_dot)
{
    std::string name = ".......";
    EXPECT_EQ("", file_extension(name));
}

TEST(FileTest, file_extension_many_dot_ext)
{
    std::string name = ".......why";
    EXPECT_EQ("why", file_extension(name));
}

TEST(StringTest, remove_space_empty)
{
    std::string test = "";
    EXPECT_EQ("", remove_spaces(test));
}

TEST(StringTest, remove_space_nospace)
{
    std::string test = "abc123!?*()/.,;'`";
    EXPECT_EQ(test, remove_spaces(test));
}

TEST(StringTest, remove_space_tab)
{
    std::string test = "\t";
    EXPECT_EQ("", remove_spaces(test));
}

TEST(StringTest, remove_space_space)
{
    std::string test = " ";
    EXPECT_EQ("", remove_spaces(test));
}

TEST(StringTest, remove_space_two_words)
{
    std::string test = "i am";
    EXPECT_EQ("iam", remove_spaces(test));
}

TEST(StringTest, remove_space_two_words_tab)
{
    std::string test = "\ti\tam";
    EXPECT_EQ("iam", remove_spaces(test));
}

TEST(StringTest, remove_space_surround)
{
    std::string test = " i am ";
    EXPECT_EQ("iam", remove_spaces(test));
}

TEST(StringTest, count_char_empty)
{
    std::string test = "";
    for (unsigned char c = 0; c < 0xFF; c++)
    {
        EXPECT_EQ(0, count_char(test, c));
    }
}

TEST(StringTest, count_char_examples)
{
    std::string test = "abc";
    EXPECT_EQ(1, count_char(test, 'a'));
    test = "123";
    EXPECT_EQ(0, count_char(test, 'a'));
    test = "123123";
    EXPECT_EQ(2, count_char(test, '1'));
    test = "112233";
    EXPECT_EQ(2, count_char(test, '1'));
    test = " s ";
    EXPECT_EQ(2, count_char(test, ' '));
}

TEST(StringTest, count_char_ntimes)
{
    for (int k = 0; k < 10; k++)
    {
        for (unsigned char c = 0; c < 0xFF; c++)
        {
            EXPECT_EQ(k, count_char(std::string(k, c), c));
        }
    }
}

//TEST(StringTest, sig_figs_zero) // 0 is unspecified
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 0);
//    EXPECT_EQ(std::to_string(test) , res);
//}
//
//TEST(StringTest, sig_figs_one) 
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 1);
//    EXPECT_EQ("100", res);
//}
//
//TEST(StringTest, sig_figs_two)
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 2);
//    EXPECT_EQ("120", res);
//}
//
//TEST(StringTest, sig_figs_three)
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 3);
//    EXPECT_EQ("123", res);
//}
//
//TEST(StringTest, sig_figs_decimal_one)
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 4);
//    EXPECT_EQ("123.1", res);
//}
//
//TEST(StringTest, sig_figs_decimal_two)
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 5);
//    EXPECT_EQ("123.12", res);
//}
//
//TEST(StringTest, sig_figs_decimal_three)
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 6);
//    EXPECT_EQ("123.123", res);
//}
//
//TEST(StringTest, sig_figs_decimal_extra)
//{
//    double test = 123.123;
//    std::string res = numformat::sig_fig_format(test, 7);
//    EXPECT_EQ("123.1230", res);
//}
//
//TEST(StringTest, sig_figs_decimals_only)
//{
//    double test;
//    std::string res;
//
//    test = 0.123;
//    res = numformat::sig_fig_format(test, 1);
//    EXPECT_EQ("0.1", res);
//
//    test = 0.123;
//    res = numformat::sig_fig_format(test, 2);
//    EXPECT_EQ("0.12", res);
//        
//    test = 0.123;
//    res = numformat::sig_fig_format(test, 3);
//    EXPECT_EQ("0.123", res);
//
//    test = 0.123;
//    res = numformat::sig_fig_format(test, 4);
//    EXPECT_EQ("0.1230", res);
//}
//
//TEST(StringTest, sig_figs_varied)
//{
//    double test;
//    std::string res;
//    
//    test = 123.123;
//    res = numformat::sig_fig_format(test, 4);
//    EXPECT_EQ("123.1", res);
//
//    test = 12.123;
//    res = numformat::sig_fig_format(test, 4);
//    EXPECT_EQ("12.12", res);
//
//    test = 1.123;
//    res = numformat::sig_fig_format(test, 4);
//    EXPECT_EQ("1.123", res);
//
//    test = 0.123;
//    res = numformat::sig_fig_format(test, 4);
//    EXPECT_EQ("0.1230", res);
//}
//
//TEST(StringTest, fixed_decimal_zero)
//{
//    double test = 123.123;
//    std::string res = numformat::fixed_decimal_format(test, 0);
//    EXPECT_EQ("123", res);
//}
//
//TEST(StringTest, fixed_decimal_one)
//{
//    double test = 123.123;
//    std::string res = numformat::fixed_decimal_format(test, 1);
//    EXPECT_EQ("123.1", res);
//}
//
//TEST(StringTest, fixed_decimal_two)
//{
//    double test = 123.123;
//    std::string res = numformat::fixed_decimal_format(test, 2);
//    EXPECT_EQ("123.12", res);
//}
//
//TEST(StringTest, fixed_decimal_three)
//{
//    double test = 123.123;
//    std::string res = numformat::fixed_decimal_format(test, 3);
//    EXPECT_EQ("123.123", res);
//}
//
//TEST(StringTest, fixed_decimal_extra)
//{
//    double test = 123.123;
//    std::string res = numformat::fixed_decimal_format(test, 4);
//    EXPECT_EQ("123.1230", res);
//}
//
//TEST(StringTest, fixed_decimal_decimals_only)
//{
//    double test = 0.123;
//    std::string res = numformat::fixed_decimal_format(test, 4);
//    EXPECT_EQ("0.1230", res);
//}
//
//TEST(StringTest, fixed_decimal_varied)
//{
//    double test;
//    std::string res;
//    
//    test = 123.123;
//    res = numformat::fixed_decimal_format(test, 2);
//    EXPECT_EQ("123.12", res);
//
//    test = 12.123;
//    res = numformat::fixed_decimal_format(test, 2);
//    EXPECT_EQ("12.12", res);
//
//    test = 1.123;
//    res = numformat::fixed_decimal_format(test, 2);
//    EXPECT_EQ("1.12", res);
//
//    test = .123;
//    res = numformat::fixed_decimal_format(test, 2);
//    EXPECT_EQ("0.12", res);
//
//    test = .0123;
//    res = numformat::fixed_decimal_format(test, 2);
//    EXPECT_EQ("0.01", res);
//}