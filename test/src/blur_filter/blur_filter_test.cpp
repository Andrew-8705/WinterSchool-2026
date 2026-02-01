#include "blur_filter_test.hpp"

COMMON_TEST(Test_Blur_Filter_Size_1x1_Filter_1x1)
{
    static constexpr int width  = 1;
    static constexpr int height = 1;
    static constexpr int kernel_size = 1;
    
    std::vector<uint8_t> source = {1, 2, 3};
    std::vector<uint8_t> dst_reference = {0, 0, 0};
    std::vector<uint8_t> dst_result = {0, 0, 0};

    blur_filter_ref(source.data(), dst_reference.data(), width, height, kernel_size);
    BLUR_FILTER_FUNC(source.data(), dst_result.data(), width, height, kernel_size);

    EXPECT_EQ_VECTOR_VECTOR(dst_result, dst_reference);
}

COMMON_TEST(Test_Blur_Filter_Size_3x3_Filter_1x1)
{
    static constexpr int width = 3;
    static constexpr int height = 3;
    static constexpr int kernel_size = 1;
    static constexpr int channels = 3;

    std::vector<uint8_t> source = {
        10, 20, 30, 40, 50, 60, 70, 80, 90,
        15, 25, 35, 45, 55, 65, 75, 85, 95,
        20, 30, 40, 50, 60, 70, 80, 90, 100
    };
    std::vector<uint8_t> dst_reference(width*height*channels, 0);
    std::vector<uint8_t> dst_result(width*height*channels, 0);

    blur_filter_ref(source.data(), dst_reference.data(), width, height, kernel_size);
    BLUR_FILTER_FUNC(source.data(), dst_result.data(), width, height, kernel_size);

    EXPECT_EQ_VECTOR_VECTOR(dst_result, dst_reference);
}

COMMON_TEST(Test_Blur_Filter_Size_3x3_Filter_3x3)
{
    static constexpr int width = 3;
    static constexpr int height = 3;
    static constexpr int kernel_size = 3;
    static constexpr int channels = 3;

    std::vector<uint8_t> source = {
        10, 20, 30, 40, 50, 60, 70, 80, 90,
        15, 25, 35, 45, 55, 65, 75, 85, 95,
        20, 30, 40, 50, 60, 70, 80, 90, 100
    };
    std::vector<uint8_t> dst_reference(width*height*channels, 0);
    std::vector<uint8_t> dst_result(width*height*channels, 0);

    blur_filter_ref(source.data(), dst_reference.data(), width, height, kernel_size);
    BLUR_FILTER_FUNC(source.data(), dst_result.data(), width, height, kernel_size);

    EXPECT_EQ_VECTOR_VECTOR(dst_result, dst_reference);
}

COMMON_TEST(Test_Blur_Filter_Size_5x5_Filter_5x5)
{
    static constexpr int width = 5;
    static constexpr int height = 5;
    static constexpr int kernel_size = 5;
    static constexpr int channels = 3;

    std::vector<uint8_t> source = {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
        110, 120, 130, 140, 150, 160, 170, 180, 190, 200,
        210, 220, 230, 240, 250, 255, 245, 235, 225, 215,
        205, 195, 185, 175, 165, 155, 145, 135, 125, 115,
        105, 95, 85, 75, 65, 55, 45, 35, 25, 15
    };
    std::vector<uint8_t> dst_reference(width*height*channels, 0);
    std::vector<uint8_t> dst_result(width*height*channels, 0);

    blur_filter_ref(source.data(), dst_reference.data(), width, height, kernel_size);
    BLUR_FILTER_FUNC(source.data(), dst_result.data(), width, height, kernel_size);

    EXPECT_EQ_VECTOR_VECTOR(dst_result, dst_reference);
}

COMMON_TEST(Test_Blur_Filter_Size_7x7_Filter_3x3)
{
    static constexpr int width = 7;
    static constexpr int height = 7;
    static constexpr int kernel_size = 3;
    static constexpr int channels = 3;

    std::vector<uint8_t> source(width*height*channels, 41);
    std::vector<uint8_t> dst_reference(width*height*channels, 0);
    std::vector<uint8_t> dst_result(width*height*channels, 0);

    blur_filter_ref(source.data(), dst_reference.data(), width, height, kernel_size);
    BLUR_FILTER_FUNC(source.data(), dst_result.data(), width, height, kernel_size);

    EXPECT_EQ_VECTOR_VECTOR(dst_result, dst_reference);
}

constexpr size_t widthIndex{0U};
constexpr size_t heightIndex{1U};
constexpr size_t kernelSizeIndex{2U};

template <typename T>
class BlurFilter : public ::testing::Test
{
public:
    static constexpr size_t width      = std::tuple_element_t<widthIndex, T>{};
    static constexpr size_t height     = std::tuple_element_t<heightIndex, T>{};
    static constexpr size_t kernelSize = std::tuple_element_t<kernelSizeIndex, T>{};
    static constexpr size_t channels   = 3;

    std::vector<uint8_t> source;
    std::vector<uint8_t> dst_reference;
    std::vector<uint8_t> dst_result;

    void prepareData(size_t width, size_t height) {
        size_t totalSize = width * height * channels;

        source.resize(totalSize);
        dst_reference.resize(totalSize);
        dst_result.resize(totalSize);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<uint8_t> dist(0, 255);

        std::generate(source.begin(), source.end(), [&]() { return dist(rng); });

        std::fill(dst_reference.begin(), dst_reference.end(), 0);
        std::fill(dst_result.begin(), dst_result.end(), 0);
    }
};


#define TEST_BLUR(width, height, kernelSize) std::tuple<std::integral_constant<size_t, (width)>, \
                                                        std::integral_constant<size_t, (height)>, \
                                                        std::integral_constant<size_t, (kernelSize)>>



using TypesBlurFilter = testing::Types<TEST_BLUR(1U, 1U, 1U),
                                       TEST_BLUR(1U, 1U, 2U),
                                       TEST_BLUR(4U, 4U, 1U),
                                       TEST_BLUR(4U, 4U, 3U),
                                       TEST_BLUR(16U, 8U, 4U),
                                       TEST_BLUR(8U, 16U, 1U),
                                       TEST_BLUR(16U, 16U, 3U),
                                       TEST_BLUR(32U, 16U, 2U),
                                       TEST_BLUR(32U, 32U, 4U),  
                                       TEST_BLUR(16U, 32U, 4U),
                                       TEST_BLUR(128U, 64U, 3U),
                                       TEST_BLUR(64U, 128U, 3U),
                                       TEST_BLUR(128U, 64U, 1U),
                                       TEST_BLUR(64U, 128U, 2U),
                                       TEST_BLUR(128U, 128U, 3U),  
                                       TEST_BLUR(128U, 128U, 6U)>;

TYPED_TEST_SUITE(BlurFilter, TypesBlurFilter);

TYPED_TEST(BlurFilter, Test_Rand_Values) {
    constexpr size_t width       = TestFixture::width;
    constexpr size_t height      = TestFixture::height;
    constexpr size_t kernel_size = TestFixture::kernelSize;

    TestFixture::prepareData(width, height);

    blur_filter_ref(this->source.data(), this->dst_reference.data(), width, height, kernel_size);
    BLUR_FILTER_FUNC(this->source.data(), this->dst_result.data(), width, height, kernel_size);

    EXPECT_EQ_VECTOR_VECTOR(this->dst_result, this->dst_reference);
}
