#include "symv_test.hpp"

constexpr float threshold = 1e-3;

COMMON_TEST(Test_Symv_Size_1x1)
{
    static constexpr size_t n = 1;
    static constexpr float alpha = 1.5f;
    
    std::vector<float> A = {-1.0f};
    std::vector<float> x = {-1.0f};
    std::vector<float> y_reference = {1.0f};
    std::vector<float> y_result = y_reference;

    symv_ref(n, alpha, A.data(), x.data(), y_reference.data());
    SYMV_FUNC(n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Symv_Size_2x2)
{
    static constexpr size_t n = 2;
    static constexpr float alpha = 2.0f;

    std::vector<float> A = {1.0f, 2.0f,
                            3.0f, 4.0f};
    std::vector<float> x = {0.5f, 1.0f};
    std::vector<float> y_reference = {0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    symv_ref(n, alpha, A.data(), x.data(), y_reference.data());
    SYMV_FUNC(n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Symv_Size_3x3)
{
    static constexpr size_t n = 3;
    static constexpr float alpha = 0.5f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f,
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f};
    std::vector<float> x = {1.0f, 0.5f, 0.25f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    symv_ref(n, alpha, A.data(), x.data(), y_reference.data());
    SYMV_FUNC(n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}


COMMON_TEST(Test_Symv_Size_4x4)
{
    static constexpr size_t n = 4;
    static constexpr float alpha = 1.0f;

    std::vector<float> A = {1.0f, 2.0f, 3.0f, 4.0f,
                            5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f};
    std::vector<float> x = {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<float> y_reference = {0.0f, 0.0f, 0.0f, 0.0f};
    std::vector<float> y_result = y_reference;

    symv_ref(n, alpha, A.data(), x.data(), y_reference.data());
    SYMV_FUNC(n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

COMMON_TEST(Test_Symv_Size_8x8)
{
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

    symv_ref(n, alpha, A.data(), x.data(), y_reference.data());
    SYMV_FUNC(n, alpha, A.data(), x.data(), y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(y_result, y_reference, threshold);
}

constexpr size_t nIndex{0U};

template <typename T>
class Symv : public ::testing::Test
{
public:
    static constexpr size_t n = std::tuple_element_t<nIndex, T>{};

    std::vector<float> A;
    std::vector<float> x;
    std::vector<float> y_reference;
    std::vector<float> y_result;

    void prepareData(size_t n) {

        A.resize(n * n);
        x.resize(n);
        y_reference.resize(n);
        y_result.resize(n);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

        std::generate(A.begin(), A.end(), [&] { return dist(rng); });
        std::generate(x.begin(), x.end(), [&] { return dist(rng); });
        std::generate(y_reference.begin(), y_reference.end(), [&] { return dist(rng); });
        y_result = y_reference;
    }
};

#define TEST_SYMV(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesSymv = testing::Types<TEST_SYMV(1U),
                                 TEST_SYMV(2U),
                                 TEST_SYMV(3U),
                                 TEST_SYMV(4U),
                                 TEST_SYMV(5U),
                                 TEST_SYMV(6U),
                                 TEST_SYMV(7U),
                                 TEST_SYMV(8U),
                                 TEST_SYMV(15U),
                                 TEST_SYMV(16U),
                                 TEST_SYMV(17U),
                                 TEST_SYMV(31U),
                                 TEST_SYMV(32U),
                                 TEST_SYMV(33U),
                                 TEST_SYMV(63U),
                                 TEST_SYMV(64U),
                                 TEST_SYMV(65U),
                                 TEST_SYMV(127U),
                                 TEST_SYMV(128U),
                                 TEST_SYMV(129U)>;

TYPED_TEST_SUITE(Symv, TypesSymv);

TYPED_TEST(Symv, Test_Rand_Values) {
    constexpr size_t n = TestFixture::n;
    TestFixture::prepareData(n);

    symv_ref(n, 1.5f, this->A.data(), this->x.data(), this->y_reference.data());
    SYMV_FUNC(n, 1.5f, this->A.data(), this->x.data(), this->y_result.data());

    EXPECT_NEAR_VECTOR_VECTOR(this->y_result, this->y_reference, threshold);
}
