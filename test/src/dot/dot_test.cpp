#include "dot_test.hpp"

constexpr float threshold = 1e-3;

COMMON_TEST(Test_Dot_Size_1)
{
    static constexpr size_t n = 1;
    
    std::vector<float> x = {-1.0f};
    std::vector<float> y = {1.0f};

    float result = DOT_FUNC(x.data(), y.data(), n);

    EXPECT_NEAR(result, -1.0f, threshold);
}

COMMON_TEST(Test_Dot_Size_2)
{
    static constexpr size_t n = 2;
    
    std::vector<float> x = {-1.0f, 2.0f};
    std::vector<float> y = {1.0f, -3.0f};

    float result = DOT_FUNC(x.data(), y.data(), n);

    EXPECT_NEAR(result, -7.0f, threshold);
}

COMMON_TEST(Test_Dot_Size_3)
{
    static constexpr size_t n = 3;
    
    std::vector<float> x = {3.0f, -1.0f, 4.0f};
    std::vector<float> y = {1.0f, -3.0f, 10.0f};

    float result = DOT_FUNC(x.data(), y.data(), n);

    EXPECT_NEAR(result, 46.0f, threshold);
}

COMMON_TEST(Test_Dot_Size_4)
{
    static constexpr size_t n = 4;
    std::vector<float> x = {3.3f, -1.4f, 4.7f, 3.0f};
    std::vector<float> y = {1.1f, -3.4f, 10.4f, 1.5f};

    float result = DOT_FUNC(x.data(), y.data(), n);

    EXPECT_NEAR(result, 61.77f, threshold);
}

COMMON_TEST(Test_Dot_Size_8)
{
    static constexpr size_t n = 8;
    std::vector<float> x = {3.3f, -1.4f, 4.7f, 3.0f, 3.3f, -1.4f, 4.7f, 3.0f};
    std::vector<float> y = {1.1f, -3.4f, 10.4f, 1.5f, 1.1f, -3.4f, 10.4f, 1.5f};

    float result = DOT_FUNC(x.data(), y.data(), n);

    EXPECT_NEAR(result, 123.54f, threshold);
}

constexpr size_t nIndex{0U};

template <typename T>
class Dot : public ::testing::Test
{
public:
    static constexpr size_t n = std::tuple_element_t<nIndex, T>{};

    std::vector<float> x;
    std::vector<float> y;

    void prepareData(int n) {
        x.resize(n);
        y.resize(n);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

        std::generate(x.begin(), x.end(), [&] { return dist(rng); });
        std::generate(y.begin(), y.end(), [&] { return dist(rng); });
    }
};

#define TEST_DOT(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesDot = testing::Types<TEST_DOT(1),
                                TEST_DOT(2),
                                TEST_DOT(3),
                                TEST_DOT(4),
                                TEST_DOT(5),
                                TEST_DOT(6),
                                TEST_DOT(7),
                                TEST_DOT(8),
                                TEST_DOT(9),
                                TEST_DOT(10),
                                TEST_DOT(11),
                                TEST_DOT(12),
                                TEST_DOT(13),
                                TEST_DOT(14),
                                TEST_DOT(15),
                                TEST_DOT(16),
                                TEST_DOT(31),
                                TEST_DOT(32),
                                TEST_DOT(33),
                                TEST_DOT(63),
                                TEST_DOT(64),
                                TEST_DOT(65)>;

TYPED_TEST_SUITE(Dot, TypesDot);

TYPED_TEST(Dot, Test_Rand_Values) {
    constexpr size_t n = TestFixture::n;
    TestFixture::prepareData(n);

    float reference = dot_ref(this->x.data(), this->y.data(), n);
    float result = DOT_FUNC(this->x.data(), this->y.data(), n);

    EXPECT_NEAR(result, reference, threshold);
}
