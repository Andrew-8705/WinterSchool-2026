#include "axpby_test.hpp"

constexpr float threshold = 1e-5;

COMMON_TEST(Test_Axpby_Size_1)
{
    static constexpr int length = 1;
    
    std::vector<float> source    = {-1.0f};
    std::vector<float> reference = {0.0f};
    std::vector<float> result    = {0.0f};

    axpby_ref(length, 1.5, source.data(), 1.5, reference.data());

    AXPBY_FUNC(length, 1.5, source.data(), 1.5, result.data());

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Axpby_Size_2)
{
    static constexpr int length = 2;

    std::vector<float> source    = {-1.0f, -2.0f};
    std::vector<float> reference = {0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f};

    axpby_ref(length, 1.5, source.data(), 1.5, reference.data());

    AXPBY_FUNC(length, 1.5, source.data(), 1.5, result.data());

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Axpby_Size_3)
{
    static constexpr int length = 3;

    std::vector<float> source    = {-1.0f, -2.0f, -4.0f};
    std::vector<float> reference = {0.0f, 0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f, 0.0f};

    axpby_ref(length, 1.5, source.data(), 1.5, reference.data());

    AXPBY_FUNC(length, 1.5, source.data(), 1.5, result.data());

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Axpby_Size_4)
{
    static constexpr int length = 4;

    std::vector<float> source    = {-1.0f, 2.0f, -4.0f, -67.0f};
    std::vector<float> reference = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f, 0.0f, 0.0f};

    axpby_ref(length, 1.5, source.data(), 1.5, reference.data());

    AXPBY_FUNC(length, 1.5, source.data(), 1.5, result.data());

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

COMMON_TEST(Test_Axpby_Size_8)
{
    static constexpr int length = 8;

    std::vector<float> source    = {-1.0f,  2.0f, -4.0f, -67.0f,
                                    -7.0f, -7.0f, -3.0f, 10.0f};
    std::vector<float> reference = {0.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> result    = {0.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f};

    axpby_ref(length, 1.5, source.data(), 1.5, reference.data());

    AXPBY_FUNC(length, 1.5, source.data(), 1.5, result.data());

    EXPECT_NEAR_VECTOR_VECTOR(result, reference, threshold);
}

constexpr size_t lengthIndex{0U};

template <typename T>
class Axpby : public ::testing::Test
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
        result = reference;
    }
};

#define TEST_AXPBY(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesAxpby = testing::Types<TEST_AXPBY(1),
                                  TEST_AXPBY(2),
                                  TEST_AXPBY(3),
                                  TEST_AXPBY(4),
                                  TEST_AXPBY(5),
                                  TEST_AXPBY(6),
                                  TEST_AXPBY(7),
                                  TEST_AXPBY(8),
                                  TEST_AXPBY(9),
                                  TEST_AXPBY(10),
                                  TEST_AXPBY(11),
                                  TEST_AXPBY(12),
                                  TEST_AXPBY(13),
                                  TEST_AXPBY(14),
                                  TEST_AXPBY(15),
                                  TEST_AXPBY(16),
                                  TEST_AXPBY(31),
                                  TEST_AXPBY(32),
                                  TEST_AXPBY(33),
                                  TEST_AXPBY(63),
                                  TEST_AXPBY(64),
                                  TEST_AXPBY(65)>;

TYPED_TEST_SUITE(Axpby, TypesAxpby);

TYPED_TEST(Axpby, Test_Rand_Values) {
    constexpr size_t length = TestFixture::length;
    TestFixture::prepareData(length);

    axpby_ref(length, 1.5, this->source.data(), 1.5, this->reference.data());
    AXPBY_FUNC(length, 1.5, this->source.data(), 1.5, this->result.data());

    EXPECT_NEAR_VECTOR_VECTOR(this->result, this->reference, threshold);
}
