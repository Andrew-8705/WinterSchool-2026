#include "alpha_compositing_test.hpp"

constexpr uint8_t threshold = 1;

COMMON_TEST(Test_Alpha_Compositing_Size_1x1_c1)
{
    static constexpr int width  = 1;
    static constexpr int height = 1;
    static constexpr int channels = 1;
    static constexpr float alpha = 0.5f;
    
    std::vector<uint8_t> foreground = {0};
    std::vector<uint8_t> background = {255};
    std::vector<uint8_t> image_reference = {0};
    std::vector<uint8_t> image_result = {0};

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_1x1_c3)
{
    static constexpr int width  = 1;
    static constexpr int height = 1;
    static constexpr int channels = 3;
    static constexpr float alpha = 0.5f;

    std::vector<uint8_t> foreground = {0, 128, 255};
    std::vector<uint8_t> background = {255, 128, 0};
    std::vector<uint8_t> image_reference = {0, 0, 0};
    std::vector<uint8_t> image_result = {0, 0, 0};

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_2x2_c1)
{
    static constexpr int width  = 2;
    static constexpr int height = 2;
    static constexpr int channels = 1;
    static constexpr float alpha = 0.25f;

    std::vector<uint8_t> foreground = {0, 64, 128, 255};
    std::vector<uint8_t> background = {255, 192, 128, 64};
    std::vector<uint8_t> image_reference = {0, 0, 0, 0};
    std::vector<uint8_t> image_result = {0, 0, 0, 0};

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_4x4_c4)
{
    static constexpr int width  = 4;
    static constexpr int height = 4;
    static constexpr int channels = 4;
    static constexpr float alpha = 0.75f;

    std::vector<uint8_t> foreground = {
        255, 0, 0, 255,  0, 255, 0, 255,  0, 0, 255, 255,  255, 255, 255, 255,
        128, 128, 128, 255,  64, 64, 64, 255,  32, 32, 32, 255,  16, 16, 16, 255
    };
    std::vector<uint8_t> background = {
        0, 0, 0, 255,  255, 0, 0, 255,  0, 255, 0, 255,  0, 0, 255, 255,
        255, 255, 255, 255,  192, 192, 192, 255,  128, 128, 128, 255,  64, 64, 64, 255
    };
    std::vector<uint8_t> image_reference(4 * 4 * 4, 0);
    std::vector<uint8_t> image_result(4 * 4 * 4, 0);

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_2x4_c1)
{
    static constexpr int width  = 2;
    static constexpr int height = 4;
    static constexpr int channels = 1;
    static constexpr float alpha = 0.3f;

    std::vector<uint8_t> foreground = {0, 50, 100, 150, 200, 250, 50, 100};
    std::vector<uint8_t> background = {255, 205, 155, 105, 55, 5, 205, 155};
    std::vector<uint8_t> image_reference(2 * 4, 0);
    std::vector<uint8_t> image_result(2 * 4, 0);

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_4x2_c3)
{
    static constexpr int width  = 4;
    static constexpr int height = 2;
    static constexpr int channels = 3;
    static constexpr float alpha = 0.6f;

    std::vector<uint8_t> foreground = {
        255, 0, 0,  0, 255, 0,  0, 0, 255,  128, 128, 128,
        64, 64, 64,  192, 192, 192,  32, 32, 32,  16, 16, 16
    };
    std::vector<uint8_t> background = {
        0, 0, 255,  255, 0, 0,  0, 255, 0,  255, 255, 255,
        128, 128, 128,  64, 64, 64,  192, 192, 192,  16, 16, 16
    };
    std::vector<uint8_t> image_reference(4 * 2 * 3, 0);
    std::vector<uint8_t> image_result(4 * 2 * 3, 0);

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_16x16_c4)
{
    static constexpr int width  = 16;
    static constexpr int height = 16;
    static constexpr int channels = 4;
    static constexpr float alpha = 0.8f;

    std::vector<uint8_t> foreground(width * height * channels, 128);
    std::vector<uint8_t> background(width * height * channels, 64);
    std::vector<uint8_t> image_reference(width * height * channels, 0);
    std::vector<uint8_t> image_result(width * height * channels, 0);

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_8x16_c3)
{
    static constexpr int width  = 8;
    static constexpr int height = 16;
    static constexpr int channels = 3;
    static constexpr float alpha = 0.4f;

    std::vector<uint8_t> foreground(width * height * channels);
    std::vector<uint8_t> background(width * height * channels);
    std::vector<uint8_t> image_reference(width * height * channels, 0);
    std::vector<uint8_t> image_result(width * height * channels, 0);

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(0, 255);
    std::generate(foreground.begin(), foreground.end(), [&]() { return dist(rng); });
    std::generate(background.begin(), background.end(), [&]() { return dist(rng); });

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}

COMMON_TEST(Test_Alpha_Compositing_Size_16x8_c3)
{
    static constexpr int width  = 16;
    static constexpr int height = 8;
    static constexpr int channels = 3;
    static constexpr float alpha = 0.7f;

    std::vector<uint8_t> foreground(width * height * channels);
    std::vector<uint8_t> background(width * height * channels);
    std::vector<uint8_t> image_reference(width * height * channels, 0);
    std::vector<uint8_t> image_result(width * height * channels, 0);

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(0, 255);
    std::generate(foreground.begin(), foreground.end(), [&]() { return dist(rng); });
    std::generate(background.begin(), background.end(), [&]() { return dist(rng); });

    alpha_compositing_ref(foreground.data(), background.data(), alpha, image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(foreground.data(), background.data(), alpha, image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(image_result, image_reference, threshold);
}


constexpr size_t widthIndex{0U};
constexpr size_t heightIndex{1U};
constexpr size_t channelsIndex{2U};

template <typename T>
class AlphaCompositing : public ::testing::Test
{
public:
    static constexpr size_t width    = std::tuple_element_t<widthIndex, T>{};
    static constexpr size_t height   = std::tuple_element_t<heightIndex, T>{};
    static constexpr size_t channels = std::tuple_element_t<channelsIndex, T>{};

    std::vector<uint8_t> foreground;
    std::vector<uint8_t> background;
    std::vector<uint8_t> image_reference;
    std::vector<uint8_t> image_result;

    void prepareData(size_t width, size_t height, size_t channels) {
        size_t totalSize = width * height * channels;

        foreground.resize(totalSize);
        background.resize(totalSize);
        image_reference.resize(totalSize);
        image_result.resize(totalSize);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<uint8_t> dist(0, 255);

        std::generate(foreground.begin(), foreground.end(), [&]() { return dist(rng); });
        std::generate(background.begin(), background.end(), [&]() { return dist(rng); });

        std::fill(image_reference.begin(), image_reference.end(), 0);
        std::fill(image_result.begin(), image_result.end(), 0);
    }
};

#define TEST_ALPHACOMPOSITING(width, height, channels) std::tuple<std::integral_constant<size_t, (width)>, \
                                                                  std::integral_constant<size_t, (height)>, \
                                                                  std::integral_constant<size_t, (channels)>>

using TypesAlphaCompositing = testing::Types<TEST_ALPHACOMPOSITING(1U, 1U, 1U),
                                             TEST_ALPHACOMPOSITING(1U, 1U, 4U),
                                             TEST_ALPHACOMPOSITING(4U, 4U, 1U),
                                             TEST_ALPHACOMPOSITING(4U, 4U, 3U),
                                             TEST_ALPHACOMPOSITING(16U, 8U, 4U),
                                             TEST_ALPHACOMPOSITING(8U, 16U, 1U),
                                             TEST_ALPHACOMPOSITING(16U, 16U, 3U),
                                             TEST_ALPHACOMPOSITING(32U, 16U, 1U),
                                             TEST_ALPHACOMPOSITING(32U, 32U, 4U),  
                                             TEST_ALPHACOMPOSITING(16U, 32U, 4U),
                                             TEST_ALPHACOMPOSITING(128U, 64U, 3U),
                                             TEST_ALPHACOMPOSITING(64U, 128U, 3U),
                                             TEST_ALPHACOMPOSITING(128U, 64U, 1U),
                                             TEST_ALPHACOMPOSITING(64U, 128U, 4U),
                                             TEST_ALPHACOMPOSITING(128U, 128U, 1U),  
                                             TEST_ALPHACOMPOSITING(128U, 128U, 4U)>;

TYPED_TEST_SUITE(AlphaCompositing, TypesAlphaCompositing);

TYPED_TEST(AlphaCompositing, Test_Rand_Values) {
    constexpr size_t width = TestFixture::width;
    constexpr size_t height = TestFixture::height;
    constexpr size_t channels = TestFixture::channels;
    constexpr float alpha = 0.4f;

    TestFixture::prepareData(width, height, channels);

    alpha_compositing_ref(this->foreground.data(), this->background.data(), alpha, this->image_reference.data(), width, height, channels);
    ALPHA_COMPOSTING_FUNC(this->foreground.data(), this->background.data(), alpha, this->image_result.data(), width, height, channels);

    EXPECT_NEAR_VECTOR_VECTOR(this->image_result, this->image_reference, threshold);
}
