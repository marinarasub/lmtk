#include "imagetest.h"

using namespace ::testing;
using namespace image;

/**
* Test class for JPEG handling (I/O) and basic functions.
* More complicated functions for image shading, manipulation etc. should be tested sepereately
* 
* @see JPEG
*/
class JPEGTest : public Test
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

const std::string JPEGTest::IMG_FOLDER = "../testdata/images/in/";
const std::string JPEGTest::OUT_FOLDER = "../testdata/images/out/jpegtest/";

TEST_F(JPEGTest, write_simple)
{
    try {
        JPEG img(100, 100);
        img.fillGradient(rgbcolor::TRANSPARENT, rgbcolor::WHITE);
        img.writeFile(OUT_FOLDER + "write-out.jpeg");
    }
    catch (...) {
        FAIL() << "Failed to write jpeg file";
    }
}

TEST_F(JPEGTest, load_file)
{
    try {
        JPEG img(IMG_FOLDER + "test.jpg");
        // success
    }
    catch (...) {
        FAIL() << "Failed to load jpeg image";
    }
}

TEST_F(JPEGTest, load_write_unmodified)
{
    try {
        JPEG img(IMG_FOLDER + "test.jpg");
        img.writeFile(OUT_FOLDER + "test-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to ... jpeg image";
    }
}

TEST_F(JPEGTest, load_write_unmodified2)
{
    try {
        JPEG img(IMG_FOLDER + "test2.jpg");
        img.writeFile(OUT_FOLDER + "test2-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to ... jpeg image";
    }
}

TEST_F(JPEGTest, mirror)
{
    try {
        JPEG img(IMG_FOLDER + "test.jpg");
        img.mirror();
        img.writeFile(OUT_FOLDER + "mirror-out.jpg");
    }
    catch (...) {
        FAIL() << "Failed to load jpeg image";
    }
}

