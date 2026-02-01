#include "abs_test.hpp"

constexpr float threshold = 0.0;

COMMON_TEST(Test_Abs_Size_1)
{
    static constexpr int length = 1;
    
    std::vector<float> source    = {-1.0f};
    std::vector<float> reference = {0.0f};
    std::vector<float> result    = {0.0f};

    fabsf_ref(source.data(), reference.data(), length);

    FABSF_FUNC(source.data(), result.data(), length);

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Abs_Size_2)
{
    static constexpr int length = 2;

    std::vector<float> source    = {-1.0f, -2.0f};
    std::vector<float> reference = {0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f};

    fabsf_ref(source.data(), reference.data(), length);

    FABSF_FUNC(source.data(), result.data(), length);

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Abs_Size_3)
{
    static constexpr int length = 3;

    std::vector<float> source    = {-1.0f, -2.0f, -4.0f};
    std::vector<float> reference = {0.0f, 0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f, 0.0f};

    fabsf_ref(source.data(), reference.data(), length);

    FABSF_FUNC(source.data(), result.data(), length);

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Abs_Size_4)
{
    static constexpr int length = 4;

    std::vector<float> source    = {-1.0f, 2.0f, -4.0f, -67.0f};
    std::vector<float> reference = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f, 0.0f, 0.0f};

    fabsf_ref(source.data(), reference.data(), length);

    FABSF_FUNC(source.data(), result.data(), length);

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Abs_Size_8)
{
    static constexpr int length = 8;

    std::vector<float> source    = {-1.0f,  2.0f, -4.0f, -67.0f,
                                    -7.0f, -7.0f, -3.0f, 10.0f};
    std::vector<float> reference = {0.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f};

    fabsf_ref(source.data(), reference.data(), length);

    FABSF_FUNC(source.data(), result.data(), length);

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

constexpr size_t lengthIndex{0U};

template <typename T>
class Abs : public ::testing::Test
{
public:
    static constexpr size_t length = std::tuple_element_t<lengthIndex, T>{};

    std::vector<float> source;
    std::vector<float> reference;
    std::vector<float> result;

    void prepareData(int length) {
        source.resize(length);
        reference.resize(length);
        result.resize(length);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(-1000.0f, 100.0f);

        std::generate(source.begin(), source.end(), [&] { return dist(rng); });
        std::generate(reference.begin(), reference.end(), [&] { return dist(rng); });
        std::generate(result.begin(), result.end(), [&] { return dist(rng); });
    }
};

#define TEST_ABS(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesAbs = testing::Types<TEST_ABS(1),
                                TEST_ABS(2),
                                TEST_ABS(3),
                                TEST_ABS(4),
                                TEST_ABS(5),
                                TEST_ABS(6),
                                TEST_ABS(7),
                                TEST_ABS(8),
                                TEST_ABS(9),
                                TEST_ABS(10),
                                TEST_ABS(11),
                                TEST_ABS(12),
                                TEST_ABS(13),
                                TEST_ABS(14),
                                TEST_ABS(15),
                                TEST_ABS(16),
                                TEST_ABS(31),
                                TEST_ABS(32),
                                TEST_ABS(33),
                                TEST_ABS(63),
                                TEST_ABS(64),
                                TEST_ABS(65)>;

TYPED_TEST_SUITE(Abs, TypesAbs);

TYPED_TEST(Abs, Test_Rand_Values) {
    constexpr size_t length = TestFixture::length;
    TestFixture::prepareData(length);

    fabsf_ref(this->source.data(), this->reference.data(), length);
    FABSF_FUNC(this->source.data(), this->result.data(), length);

    EXPECT_NEAR_VECTOR_VECTOR(this->result, this->reference, threshold);
}
