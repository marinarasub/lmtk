#include "imagetest.h"

using namespace ::testing;
using namespace image;


// NOTE: ALL ARE DEPRECATED RIGHT NOW

class ImageTest : public Test
{
public:
    const static std::string IMG_FOLDER;
    const static std::string OUT_FOLDER;

    Image img;

protected:

    void SetUp() override
    {
        img = Image(100, 100);
        // make sure no two pixels are equal
        for (size_t x = 0; x < img.width(); x++)
        {
            for (size_t y = 0; y < img.height(); y++)
            {
                img.setRGBAPixel(RGBAPixel(x, y, (x+y)/2, 255, 8), x, y);
            }
        }
    }

    void TearDown() override
    {
    }
};

const std::string ImageTest::IMG_FOLDER = "../testdata/images/in/";
const std::string ImageTest::OUT_FOLDER = "../testdata/images/out/imgtest/";

TEST_F(ImageTest, edge_handler_default)
{
    constexpr int VALID = 0;
    // x < 0
    try {
        img.getRGBAPixel(-1, VALID);
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // x >= img.width()
    try {
        img.getRGBAPixel(VALID, -1);
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // y < 0
    try {
        img.getRGBAPixel(img.width(), VALID);
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // y >= img.height()
    try {
        img.getRGBAPixel(VALID, img.height());
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // upper left
    try {
        img.getRGBAPixel(-1, -1);
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // upper right
    try {
        img.getRGBAPixel(img.width(), -1);
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // lower left
    try {
        img.getRGBAPixel(-1, img.height());
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
    // lower right
    try {
        img.getRGBAPixel(img.width(), img.height());
        FAIL() << "Expected exception";
    }
    catch (std::exception e) {
    }
}

TEST_F(ImageTest, edge_handler_extend)
{
    constexpr int VALID = 0;
    constexpr EdgeHandlingMethod METHOD = EdgeHandlingMethod::EXTEND;
    RGBAPixel p;

    // x: (-1, 0) -> (0, 0)
    try {
        p = img.getRGBAPixel(-1, VALID, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(0, VALID) , p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // y: (0, -1) -> (0, 0)
    try {
        p = img.getRGBAPixel(VALID, -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(VALID, 0), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // x: (w, 0) -> (w-1, 0)
    try {
        p = img.getRGBAPixel(img.width(), VALID, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-1, VALID), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // y: (0, h) -> (0, h-1)
    try {
        p = img.getRGBAPixel(VALID, img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(VALID, img.height()-1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // UL: (-1, -1) -> (0, 0)
    try {
        p = img.getRGBAPixel(-1, -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(0, 0), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // UR: (w, -1) -> (w-1, 0)
    try {
        p = img.getRGBAPixel(img.width(), -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-1, 0), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // LL: (-1, h) -> (0, h-1)
    try {
        p = img.getRGBAPixel(-1, img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(0, img.height()-1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // LR: (w, h) -> (w-1, h-1)
    try {
        p = img.getRGBAPixel(img.width(), img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-1, img.height()-1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
}

TEST_F(ImageTest, edge_handler_tile)
{
    constexpr int VALID = 0;
    constexpr EdgeHandlingMethod METHOD = EdgeHandlingMethod::TILE;
    RGBAPixel p;

    // x: (-1, 0) -> (w-1, 0)
    try {
        p = img.getRGBAPixel(-1, VALID, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-1, VALID), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // y: (0, -1) -> (0, h-1)
    try {
        p = img.getRGBAPixel(VALID, -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(VALID, img.height()-1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // x: (w, 0) -> (0, 0)
    try {
        p = img.getRGBAPixel(img.width(), VALID, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(0, VALID), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // y: (0, h) -> (0, 0)
    try {
        p = img.getRGBAPixel(VALID, img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(VALID, 0), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // UL: (-1, -1) -> (w-1, h-1)
    try {
        p = img.getRGBAPixel(-1, -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width() - 1, img.height() - 1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // UR: (w, -1) -> (0, h-1)
    try {
        p = img.getRGBAPixel(img.width(), -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(0, img.height() - 1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // LL: (-1, h) -> (w-1, 0)
    try {
        p = img.getRGBAPixel(-1, img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width() - 1, 0), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // LR: (w, h) -> (0, 0)
    try {
        p = img.getRGBAPixel(img.width(), img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(0, 0), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
}

TEST_F(ImageTest, edge_handler_mirror)
{
    constexpr int VALID = 0;
    constexpr EdgeHandlingMethod METHOD = EdgeHandlingMethod::MIRROR;
    RGBAPixel p;

    // x: (-1, 0) -> (1, 0)
    try {
        p = img.getRGBAPixel(-1, VALID, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(1, VALID), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // y: (0, -1) -> (0, 1)
    try {
        p = img.getRGBAPixel(VALID, -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(VALID, 1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // x: (w, 0) -> (w-2, 0)
    try {
        p = img.getRGBAPixel(img.width(), VALID, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-2, VALID), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // y: (0, h) -> (0, h-2)
    try {
        p = img.getRGBAPixel(VALID, img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(VALID, img.height() - 2), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // UL: (-1, -1) -> (1, 1)
    try {
        p = img.getRGBAPixel(-1, -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(1, 1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // UR: (w, -1) -> (w-2, 1)
    try {
        p = img.getRGBAPixel(img.width(), -1, METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-2, 1), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // LL: (-1, h) -> (1, h-2)
    try {
        p = img.getRGBAPixel(-1, img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(1, img.height()-2), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
    // LR: (w, h) -> (w-2, h-2)
    try {
        p = img.getRGBAPixel(img.width(), img.height(), METHOD);
        EXPECT_EQ(*img.getRGBAPixel(img.width()-2, img.height()-2), p);
    }
    catch (std::exception e) {
        FAIL() << e.what();
    }
}

TEST_F(ImageTest, edge_extend_file)
{
    constexpr int BEYOND = 25;
    try
    {
        PNG out(img.width() + 2*BEYOND, img.height() + 2*BEYOND);
        for (int x = 0; x < out.width(); x++)
        {
            for (int y = 0; y < out.height(); y++)
            {
                out.setRGBAPixel(
                    img.getRGBAPixel(
                        x - BEYOND,
                        y - BEYOND, 
                        EdgeHandlingMethod::EXTEND), 
                    x, 
                    y);
            }
        }
        out.writeFile(OUT_FOLDER + "extend.png");
    }
    catch (std::exception e)
    {
        FAIL() << e.what();
    }
}

TEST_F(ImageTest, edge_tile_file)
{
    constexpr int BEYOND = 25;
    try
    {
        PNG out(img.width() + 2 * BEYOND, img.height() + 2 * BEYOND);
        for (int x = 0; x < out.width(); x++)
        {
            for (int y = 0; y < out.height(); y++)
            {
                out.setRGBAPixel(
                    img.getRGBAPixel(
                        x - BEYOND,
                        y - BEYOND,
                        EdgeHandlingMethod::TILE),
                    x,
                    y);
            }
        }
        out.writeFile(OUT_FOLDER + "tile.png");
    }
    catch (std::exception e)
    {
        FAIL() << e.what();
    }
}

TEST_F(ImageTest, edge_mirror_file)
{
    constexpr int BEYOND = 25;
    try
    {
        PNG out(img.width() + 2 * BEYOND, img.height() + 2 * BEYOND);
        for (int x = 0; x < out.width(); x++)
        {
            for (int y = 0; y < out.height(); y++)
            {
                out.setRGBAPixel(
                    img.getRGBAPixel(
                        x - BEYOND,
                        y - BEYOND,
                        EdgeHandlingMethod::MIRROR),
                    x,
                    y);
            }
        }
        out.writeFile(OUT_FOLDER + "mirror.png");
    }
    catch (std::exception e)
    {
        FAIL() << e.what();
    }
}
