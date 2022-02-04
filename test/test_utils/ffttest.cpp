#include "ffttest.h"
#include <string>

using namespace utils;


class FourierTest : public ::testing::Test
{
    static const std::string CSV_OUT_FOLDER;

    void TearDown() override
    {

    }

public:

    template <typename T>
    // data is array of vector ptrs
    void dataOut(std::string path, std::vector<T>* datasets[], int num_datasets) 
    {
        //static_assert(std::is_fundamental<T>::value); // c++17
        // output to text
        FILE* fp = fopen((CSV_OUT_FOLDER + path).c_str(), "w");
        if (!fp) FAIL() << "could not open file for csv";

        // find min size for write all
        int min_size = INT32_MAX;
        for (int i = 0; i < num_datasets; i++)
        {
            min_size = fmin(min_size, datasets[i]->size());
        }
        // write to file for plotting
        // header TODO
        for (int k = 0; k < min_size; k++)
        {
            T txt;
            fprintf(fp, std::to_string(k).c_str());
            fprintf(fp, ", ");
            for (int i = 0; i < num_datasets; i++)
            {
                txt = (*datasets[i])[k];
                fprintf(fp, std::to_string(txt).c_str());
                i == num_datasets-1 ? fprintf(fp, ",") : fprintf(fp, ", ");
            }
            fprintf(fp, "\n");
        }

        fclose(fp);
    }
};

const std::string FourierTest::CSV_OUT_FOLDER = "../testlogs/";

// WATCH OUT FOR i, e
#define i math::IMAGINARY_UNIT
#define i_f math::IMAGINARY_UNIT_F
#define e math::EULER
TEST(FFTUtilsTest, eitheta)
{
    constexpr double UPPER_LIMIT = 100000;
    constexpr double DX = 0.1;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        EXPECT_EQ(std::pow(e, i * k), fft::eitheta(k));
    }
}

TEST(FFTUtilsTest, cis)
{
    constexpr double UPPER_LIMIT = 100000;
    constexpr double DX = 0.1;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        EXPECT_EQ(cos(k) + i * sin(k), fft::cis(k));
    }
}


TEST(FFTUtilsTest, cis_same_eitheta)
{
    constexpr double UPPER_LIMIT = 100000;
    constexpr double DX = 0.1;
    constexpr double MAX_ERR = 0.00001;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        math::complex cis_res = fft::cis(k);
        math::complex ei_res = fft::eitheta(k);
        EXPECT_NEAR(cis_res.real(), ei_res.real(), MAX_ERR);
        EXPECT_NEAR(cis_res.imag(), ei_res.imag(), MAX_ERR);
    }
}




// same but inverse

TEST(FFTUtilsTest, eitheta_inv)
{
    constexpr double UPPER_LIMIT = 100000;
    constexpr double DX = 0.1;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        EXPECT_EQ(std::pow(e, -i * k), fft::eitheta_inv(k));
    }
}

TEST(FFTUtilsTest, cis_inv)
{
    constexpr double UPPER_LIMIT = 100000;
    constexpr double DX = 0.1;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        EXPECT_EQ(cos(k) + -i * sin(k), fft::cis_inv(k));
    }
}


TEST(FFTUtilsTest, cis_inv_same_eitheta_inv)
{
    constexpr double UPPER_LIMIT = 100000;
    constexpr double DX = 0.1;
    constexpr double MAX_ERR = 0.00001;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        math::complex cis_res = fft::cis_inv(k);
        math::complex ei_res = fft::eitheta_inv(k);
        EXPECT_NEAR(cis_res.real(), ei_res.real(), MAX_ERR);
        EXPECT_NEAR(cis_res.imag(), ei_res.imag(), MAX_ERR);
    }
}



TEST_F(FourierTest, easy_sin_tofile)
{
    const std::string CSV_OUT = "basic.csv";

    // create sine
    constexpr int LENGTH = 100; //  then this is 10 sec
    constexpr int sample_rate = 10; // 10 is 1 sec
    std::vector<float> buffer = std::vector<float>(LENGTH);
    for (int k = 0; k < LENGTH; k++)
    {
        buffer[k] = sin(k / (float)sample_rate);
    }
    std::vector<math::complex>* out = fft::dft(buffer);
    std::vector<float>* spec = fft::power_spec(*out);
    dataOut<float>(CSV_OUT, &spec, 1);
    delete spec;
    delete out;
}

TEST_F(FourierTest, cos_tofile)
{
    constexpr char* CSV_OUT = "cos.csv";

    // create sine
    constexpr int LENGTH = 1000; //  then this is 10 sec
    constexpr int sample_rate = 100; // 10 is 1 sec
    std::vector<float> buffer = std::vector<float>(LENGTH);
    for (int k = 0; k < LENGTH; k++)
    {
        buffer[k] = cos(k / (float)sample_rate);
    }
    std::vector<math::complex>* out = fft::dft(buffer);
    std::vector<float>* spec = fft::power_spec(*out);
    std::vector<float>* rev = fft::idft(*out);

    std::vector<float>* write[3] = { &buffer, rev, spec };
    dataOut<float>(CSV_OUT, write, 3);

    delete out;
    delete rev;
    delete spec;
}

TEST_F(FourierTest, mult_sin_tofile)
{
    constexpr char* CSV_OUT = "sin.csv";

    // create sine
    constexpr int LENGTH = 1000; //  then this is 10 sec
    constexpr int sample_rate = 100; // 10 is 1 sec
    std::vector<float> buffer = std::vector<float>(LENGTH);
    for (int k = 0; k < LENGTH; k++)
    {
        float res = 0;
        res = sin(k / sample_rate) + 
            0.7 * sin(55*k / sample_rate) + 
            0.5 * sin(200*k / sample_rate) +
            0.66 * sin(1000 * k / sample_rate) + 
            -0.36 * sin(600 * k / sample_rate);
        buffer[k] = res;

    }
    std::vector<math::complex>* out = fft::dft(buffer);
    std::vector<float>* spec = fft::power_spec(*out);
    std::vector<float>* rev = fft::idft(*out);

    std::vector<float>* write[3] = { &buffer, rev, spec };
    dataOut<float>(CSV_OUT, write, 3);

    delete out;
    delete rev;
    delete spec;
}

//TEST_F(FourierTest, dft_equals_fft)
//{
//    constexpr char* CSV_OUT = "dftfft.csv";
//
//    // create sine
//    constexpr int LENGTH = 1000; //  then this is 10 sec
//    constexpr int sample_rate = 10; // 10 is 1 sec
//    std::vector<float> buffer = std::vector<float>(LENGTH);
//    for (int k = 0; k < LENGTH; k++)
//    {
//        float res = 0;
//        res = sin(k / sample_rate) +
//            0.7 * sin(55 * k / sample_rate) +
//            0.5 * sin(200 * k / sample_rate) +
//            0.66 * sin(1000 * k / sample_rate) +
//            -0.36 * sin(600 * k / sample_rate);
//        buffer[k] = res;
//
//    }
//    std::vector<math::complex>* dft_out = fft::dft(buffer);
//    std::vector<math::complex>* fft_out = fft::fft(buffer);
//
//    for (int k = 0; k < LENGTH; k++)
//    {
//        EXPECT_EQ((*dft_out)[k], (*fft_out)[k]);
//    }
//
//    std::vector<float>* dft_pwr = fft::power_spec(*dft_out);
//    std::vector<float>* fft_pwr = fft::power_spec(*fft_out);
//    std::vector<float>* write[2] = { dft_pwr, fft_pwr };
//    dataOut<float>(CSV_OUT, write, 2);
//
//    delete dft_out;
//    delete fft_out;
//    delete dft_pwr;
//    delete fft_pwr;
//}

TEST_F(FourierTest, speed)
{
    constexpr char* CSV_OUT = "sin.csv";

    // create sine
    constexpr int LENGTH = 4000; //  then this is 10 sec
    constexpr int sample_rate = 1000; // 1000 is 1 sec
    std::vector<float> buffer = std::vector<float>(LENGTH);
    for (int k = 0; k < LENGTH; k++)
    {
        float res = 0;
        res = sin(k / sample_rate) +
            0.7 * sin(55 * k / sample_rate) +
            0.5 * sin(200 * k / sample_rate) +
            0.66 * sin(1000 * k / sample_rate) +
            -0.36 * sin(600 * k / sample_rate);
        buffer[k] = res;

    }
    std::vector<math::complex>* out = fft::dft(buffer);
    std::vector<float>* spec = fft::power_spec(*out);
    std::vector<float>* rev = fft::idft(*out);
    delete out;
    delete rev;
    delete spec;
}



// PERFORMANCE TESTS

TEST(FFTUtilsTest_long, cis_inv_speed)
{
    constexpr double UPPER_LIMIT = 10000;
    constexpr double DX = 0.001;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        math::complex cis_res = fft::cis_inv(k);
    }
}

TEST(FFTUtilsTest_long, eitheta_inv_speed)
{
    constexpr double UPPER_LIMIT = 10000;
    constexpr double DX = 0.001;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        math::complex ei_res = fft::eitheta_inv(k);
    }
}

TEST(FFTUtilsTest_long, cis_speed)
{
    constexpr double UPPER_LIMIT = 10000;
    constexpr double DX = 0.001;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        math::complex cis_res = fft::cis(k);
    }
}

TEST(FFTUtilsTest_long, eitheta_speed)
{
    constexpr double UPPER_LIMIT = 10000;
    constexpr double DX = 0.001;
    for (double k = 0; k < UPPER_LIMIT; k += DX)
    {
        math::complex ei_res = fft::eitheta(k);
    }
}