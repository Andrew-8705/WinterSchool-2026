#include "gemv_test.hpp"

constexpr float threshold = 1e-3;

COMMON_TEST(Test_Gemv_Size_1x1)
{
    static constexpr size_t m = 1;
    static constexpr size_t n = 1;
    static constexpr float alpha = 1.5f;
    
    std::vector<float> A = {-1.0f};
    std::vector<float> x = {-1.0f};
    std::vector<float> y_reference = {1.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_2x2)
{
    static constexpr size_t m = 2;
    static constexpr size_t n = 2;
    static constexpr float alpha = 2.0f;

    std::vector<float> A = {1.0f, 2.0f,
                            3.0f, 4.0f};
    std::vector<float> x = {0.5f, 1.0f};
    std::vector<float> y_reference = {0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_3x3)
{
    static constexpr size_t m = 3;
    static constexpr size_t n = 3;
    static constexpr float alpha = 0.5f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f,
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f};
    std::vector<float> x = {1.0f, 0.5f, 0.25f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_4x3)
{
    static constexpr size_t m = 4;
    static constexpr size_t n = 3;
    static constexpr float alpha = 1.0f;

    std::vector<float> A = {1.0f, 0.0f, 2.0f,
                            3.0f, 4.0f, 5.0f,
                            6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f};
    std::vector<float> x = {1.0f, 2.0f, 3.0f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_3x4)
{
    static constexpr size_t m = 3;
    static constexpr size_t n = 4;
    static constexpr float alpha = 0.5f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f, 4.0f,
                            5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f};
    std::vector<float> x = {0.5f, 1.0f, 1.5f, 2.0f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_4x4)
{
    static constexpr size_t m = 4;
    static constexpr size_t n = 4;
    static constexpr float alpha = 1.0f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f, 4.0f,
                            5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f};
    std::vector<float> x = {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_4x8)
{
    static constexpr size_t m = 4;
    static constexpr size_t n = 8;
    static constexpr float alpha = 0.5f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f,
                            17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f,
                            25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f};
    std::vector<float> x = {0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_8x4)
{
    static constexpr size_t m = 8;
    static constexpr size_t n = 4;
    static constexpr float alpha = 2.0f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f, 4.0f,
                            5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f,
                            17.0f, 18.0f, 19.0f, 20.0f,
                            21.0f, 22.0f, 23.0f, 24.0f,
                            25.0f, 26.0f, 27.0f, 28.0f,
                            29.0f, 30.0f, 31.0f, 32.0f};
    std::vector<float> x = {1.0f, 0.5f, 0.25f, 0.125f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Gemv_Size_8x8)
{
    static constexpr size_t m = 8;
    static constexpr size_t n = 8;
    static constexpr float alpha = 1.0f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f,
                            17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f, 24.0f,
                            25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f, 31.0f, 32.0f,
                            33.0f, 34.0f, 35.0f, 36.0f, 37.0f, 38.0f, 39.0f, 40.0f,
                            41.0f, 42.0f, 43.0f, 44.0f, 45.0f, 46.0f, 47.0f, 48.0f,
                            49.0f, 50.0f, 51.0f, 52.0f, 53.0f, 54.0f, 55.0f, 56.0f,
                            57.0f, 58.0f, 59.0f, 60.0f, 61.0f, 62.0f, 63.0f, 64.0f};
    std::vector<float> x = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    gemv_ref(m, n, alpha, A.data(), x.data(), y_reference.data());
    GEMV_FUNC(m, n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}


constexpr size_t mIndex{0U};
constexpr size_t nIndex{1U};

template <typename T>
class Gemv : public ::testing::Test
{
public:
    static constexpr size_t m = std::tuple_element_t<mIndex, T>{};
    static constexpr size_t n = std::tuple_element_t<nIndex, T>{};

    std::vector<float> A;
    std::vector<float> x;
    std::vector<float> y_reference;
    std::vector<float> y_result;

    void prepareData(size_t m, size_t n) {

        A.resize(m * n);
        x.resize(n);
        y_reference.resize(m);
        y_result.resize(m);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(-3.0f, 3.0f);

        std::generate(A.begin(), A.end(), [&] { return dist(rng); });
        std::generate(x.begin(), x.end(), [&] { return dist(rng); });
        std::generate(y_reference.begin(), y_reference.end(), [&] { return dist(rng); });
        y_result = y_reference;
    }
};

#define TEST_GEMV(m, n) std::tuple<std::integral_constant<size_t, (m)>, \
                                   std::integral_constant<size_t, (n)>>

using TypesGemv = testing::Types<TEST_GEMV(1U, 1U),
                                 TEST_GEMV(2U, 1U),
                                 TEST_GEMV(3U, 1U),
                                 TEST_GEMV(4U, 1U),
                                 TEST_GEMV(5U, 1U),
                                 TEST_GEMV(6U, 1U),
                                 TEST_GEMV(7U, 1U),
                                 TEST_GEMV(8U, 1U),
                                 TEST_GEMV(1U, 2U),
                                 TEST_GEMV(2U, 2U),
                                 TEST_GEMV(3U, 2U),
                                 TEST_GEMV(4U, 2U),
                                 TEST_GEMV(5U, 2U),
                                 TEST_GEMV(6U, 2U),
                                 TEST_GEMV(7U, 2U),
                                 TEST_GEMV(8U, 2U),
                                 TEST_GEMV(1U, 3U),
                                 TEST_GEMV(2U, 3U),
                                 TEST_GEMV(3U, 3U),
                                 TEST_GEMV(4U, 3U),
                                 TEST_GEMV(5U, 3U),
                                 TEST_GEMV(6U, 3U),
                                 TEST_GEMV(7U, 3U),
                                 TEST_GEMV(8U, 3U),
                                 TEST_GEMV(1U, 4U),
                                 TEST_GEMV(2U, 4U),
                                 TEST_GEMV(3U, 4U),
                                 TEST_GEMV(4U, 4U),
                                 TEST_GEMV(5U, 4U),
                                 TEST_GEMV(6U, 4U),
                                 TEST_GEMV(7U, 4U),
                                 TEST_GEMV(8U, 4U),
                                 TEST_GEMV(1U, 5U),
                                 TEST_GEMV(2U, 5U),
                                 TEST_GEMV(3U, 5U),
                                 TEST_GEMV(4U, 5U),
                                 TEST_GEMV(5U, 5U),
                                 TEST_GEMV(6U, 5U),
                                 TEST_GEMV(7U, 5U),
                                 TEST_GEMV(8U, 5U),
                                 TEST_GEMV(1U, 6U),
                                 TEST_GEMV(2U, 6U),
                                 TEST_GEMV(3U, 6U),
                                 TEST_GEMV(4U, 6U),
                                 TEST_GEMV(5U, 6U),
                                 TEST_GEMV(6U, 6U),
                                 TEST_GEMV(7U, 6U),
                                 TEST_GEMV(8U, 6U),
                                 TEST_GEMV(1U, 7U),
                                 TEST_GEMV(2U, 7U),
                                 TEST_GEMV(3U, 7U),
                                 TEST_GEMV(4U, 7U),
                                 TEST_GEMV(5U, 7U),
                                 TEST_GEMV(6U, 7U),
                                 TEST_GEMV(7U, 7U),
                                 TEST_GEMV(8U, 7U),
                                 TEST_GEMV(1U, 8U),
                                 TEST_GEMV(2U, 8U),
                                 TEST_GEMV(3U, 8U),
                                 TEST_GEMV(4U, 8U),
                                 TEST_GEMV(5U, 8U),
                                 TEST_GEMV(6U, 8U),
                                 TEST_GEMV(7U, 8U),
                                 TEST_GEMV(8U, 8U),
                                 TEST_GEMV(16U, 16U),
                                 TEST_GEMV(32U, 32U),
                                 TEST_GEMV(63U, 63U),
                                 TEST_GEMV(64U, 64U),
                                 TEST_GEMV(65U, 65U),
                                 TEST_GEMV(128U, 128U)>;

TYPED_TEST_SUITE(Gemv, TypesGemv);

TYPED_TEST(Gemv, Test_Rand_Values) {
    constexpr size_t m = TestFixture::m;
    constexpr size_t n = TestFixture::n;
    TestFixture::prepareData(m, n);

    gemv_ref(m, n, 1.5f, this->A.data(), this->x.data(), this->y_reference.data());
    GEMV_FUNC(m, n, 1.5f, this->A.data(), this->x.data(), this->y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(this->y_result, this->y_reference, threshold);
}
