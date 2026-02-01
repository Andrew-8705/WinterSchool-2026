#include "nrm2_test.hpp"

constexpr float threshold = 1e-3;

COMMON_TEST(Test_Nrm2_Size_1)
{
    static constexpr size_t n = 1;
    
    std::vector<float> x = {-1.0f};

    float reference = nrm2_ref(n, x.data());
    float result = NRM2_FUNC(n, x.data());

    EXPECT_NEAR(result, reference, threshold);
}

COMMON_TEST(Test_Nrm2_Size_2)
{
    static constexpr size_t n = 2;
    
    std::vector<float> x = {1.0f, 1e20f};

    float reference = nrm2_ref(n, x.data());
    float result = NRM2_FUNC(n, x.data());

    EXPECT_NEAR(result, reference, threshold);
}

COMMON_TEST(Test_Nrm2_Size_3)
{
    static constexpr size_t n = 3;
    
    std::vector<float> x = {3.0f, -1.0f, 4.0f};
    std::vector<float> y = {1.0f, -3.0f, 10.0f};

    float reference = nrm2_ref(n, x.data());
    float result = NRM2_FUNC(n, x.data());

    EXPECT_NEAR(result, reference, threshold);
}

COMMON_TEST(Test_Nrm2_Size_4)
{
    static constexpr size_t n = 4;
    std::vector<float> x = {3.3f, -1.4f, 4.7f, 3.0f};

    float reference = nrm2_ref(n, x.data());
    float result = NRM2_FUNC(n, x.data());

    EXPECT_NEAR(result, reference, threshold);
}

COMMON_TEST(Test_Nrm2_Size_8)
{
    static constexpr size_t n = 8;
    std::vector<float> x = {3.3f, -1.4f, 4.7f, 3.0f, 3.3f, -1.4f, 4.7f, 3.0f};

    float reference = nrm2_ref(n, x.data());
    float result = NRM2_FUNC(n, x.data());

    EXPECT_NEAR(result, reference, threshold);
}

constexpr size_t nIndex{0U};

template <typename T>
class Nrm2 : public ::testing::Test
{
public:
    static constexpr size_t n = std::tuple_element_t<nIndex, T>{};

    std::vector<float> x;

    void prepareData(int n) {
        x.resize(n);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

        std::generate(x.begin(), x.end(), [&] { return dist(rng); });
    }
};

#define TEST_NRM2(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesNrm2 = testing::Types<TEST_NRM2(1),
                                 TEST_NRM2(2),
                                 TEST_NRM2(3),
                                 TEST_NRM2(4),
                                 TEST_NRM2(5),
                                 TEST_NRM2(6),
                                 TEST_NRM2(7),
                                 TEST_NRM2(8),
                                 TEST_NRM2(9),
                                 TEST_NRM2(10),
                                 TEST_NRM2(11),
                                 TEST_NRM2(12),
                                 TEST_NRM2(13),
                                 TEST_NRM2(14),
                                 TEST_NRM2(15),
                                 TEST_NRM2(16),
                                 TEST_NRM2(31),
                                 TEST_NRM2(32),
                                 TEST_NRM2(33),
                                 TEST_NRM2(63),
                                 TEST_NRM2(64),
                                 TEST_NRM2(65),
                                 TEST_NRM2(128)>;

TYPED_TEST_SUITE(Nrm2, TypesNrm2);

TYPED_TEST(Nrm2, Test_Rand_Values) {
    constexpr size_t n = TestFixture::n;
    TestFixture::prepareData(n);

    float reference = nrm2_ref(n, this->x.data());
    float result = NRM2_FUNC(n, this->x.data());

    EXPECT_NEAR(result, reference, threshold);
}
