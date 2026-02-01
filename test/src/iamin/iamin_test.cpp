#include "iamin_test.hpp"

COMMON_TEST(Test_Iamin_Size_1)
{
    static constexpr size_t n = 1;
    
    std::vector<float> x = {-1.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 0);
}

COMMON_TEST(Test_Iamin_Size_2_Pos_0)
{
    static constexpr size_t n = 2;
    
    std::vector<float> x = {-1.0f, 2.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 0);
}

COMMON_TEST(Test_Iamin_Size_2_Pos_1)
{
    static constexpr size_t n = 2;
    std::vector<float> x = {-3.0f, -1.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 1);
}

COMMON_TEST(Test_Iamin_Size_3_Pos_1)
{
    static constexpr size_t n = 3;
    
    std::vector<float> x = {3.0f, -1.0f, 4.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 1);
}

COMMON_TEST(Test_Iamin_Size_3_Pos_2)
{
    static constexpr size_t n = 3;
    
    std::vector<float> x = {3.0f, -1.0f, 0.5f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 2);
}

COMMON_TEST(Test_Iamin_Size_4)
{
    static constexpr size_t n = 4;
    std::vector<float> x = {3.3f, -1.4f, 4.7f, 3.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 1);
}

COMMON_TEST(Test_Dot_Size_8_Pos_1)
{
    static constexpr size_t n = 8;
    std::vector<float> x = {3.3f, -1.4f, 4.7f, 3.0f, 3.3f, -1.4f, 4.7f, 3.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 1);
}

COMMON_TEST(Test_Dot_Size_8_Pos_5)
{
    static constexpr size_t n = 8;
    std::vector<float> x = {3.3f, -1.5f, 4.7f, 3.0f, 3.3f, -1.4f, 4.7f, 3.0f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 5);
}

COMMON_TEST(Test_Dot_Size_8_Pos_7)
{
    static constexpr size_t n = 8;
    std::vector<float> x = {3.3f, -1.5f, 4.7f, 3.0f, 3.3f, -1.4f, 4.7f, 0.1f};

    int result = IAMIN_FUNC(n, x.data());

    EXPECT_EQ(result, 7);
}

constexpr size_t nIndex{0U};

template <typename T>
class Iamin : public ::testing::Test
{
public:
    static constexpr size_t n = std::tuple_element_t<nIndex, T>{};

    std::vector<float> x;

    void prepareData(int n) {
        x.resize(n);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);

        std::generate(x.begin(), x.end(), [&] { return dist(rng); });
    }
};

#define TEST_IAMIN(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesIamin = testing::Types<TEST_IAMIN(1),
                                TEST_IAMIN(2),
                                TEST_IAMIN(3),
                                TEST_IAMIN(4),
                                TEST_IAMIN(5),
                                TEST_IAMIN(6),
                                TEST_IAMIN(7),
                                TEST_IAMIN(8),
                                TEST_IAMIN(9),
                                TEST_IAMIN(10),
                                TEST_IAMIN(11),
                                TEST_IAMIN(12),
                                TEST_IAMIN(13),
                                TEST_IAMIN(14),
                                TEST_IAMIN(15),
                                TEST_IAMIN(16),
                                TEST_IAMIN(31),
                                TEST_IAMIN(32),
                                TEST_IAMIN(33),
                                TEST_IAMIN(63),
                                TEST_IAMIN(64),
                                TEST_IAMIN(65)>;

TYPED_TEST_SUITE(Iamin, TypesIamin);

TYPED_TEST(Iamin, Test_Rand_Values) {
    constexpr size_t n = TestFixture::n;
    TestFixture::prepareData(n);

    int reference = iamin_ref(n, this->x.data());
    int result = IAMIN_FUNC(n, this->x.data());

    EXPECT_EQ(result, reference);
}
