#include "strlen_test.hpp"

COMMON_TEST(Test_Strlen_Size_0)
{   
    std::string str = {"\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 0);
}

COMMON_TEST(Test_Strlen_Size_1)
{   
    std::string str = {"A\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 1);
}

COMMON_TEST(Test_Strlen_Size_2)
{   
    std::string str = {"Aq\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 2);
}

COMMON_TEST(Test_Strlen_Size_4)
{   
    std::string str = {"Aqpv\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 4);
}

COMMON_TEST(Test_Strlen_Size_7)
{   
    std::string str = {"Aqpvaxx\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 7);
}

COMMON_TEST(Test_Strlen_Size_8)
{   
    std::string str = {"Aqpva 1x\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 8);
}

COMMON_TEST(Test_Strlen_Size_16)
{   
    std::string str = {"Aqpvax1x qpvax1x\0"};

    strlen_ref(str.c_str());

    int result = STRLEN_FUNC(str.c_str());

    EXPECT_EQ(result, 16);
}

constexpr size_t lengthIndex{0U};

template <typename T>
class Strlen : public ::testing::Test
{
public:
    static constexpr size_t length = std::tuple_element_t<lengthIndex, T>{};

    std::string str;

    void prepareData(int length) {
        str.resize(length);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<char> dist('a', 'z');

        std::generate(str.begin(), str.end()-1, [&] { return dist(rng); });
        str[length-1] = '\0';
    }
};

#define TEST_STRLEN(n) std::tuple<std::integral_constant<size_t, (n)>>

using TypesStrlen = testing::Types<TEST_STRLEN(1),
                                   TEST_STRLEN(2),
                                   TEST_STRLEN(3),
                                   TEST_STRLEN(4),
                                   TEST_STRLEN(5),
                                   TEST_STRLEN(6),
                                   TEST_STRLEN(7),
                                   TEST_STRLEN(8),
                                   TEST_STRLEN(9),
                                   TEST_STRLEN(10),
                                   TEST_STRLEN(11),
                                   TEST_STRLEN(12),
                                   TEST_STRLEN(13),
                                   TEST_STRLEN(14),
                                   TEST_STRLEN(15),
                                   TEST_STRLEN(16),
                                   TEST_STRLEN(31),
                                   TEST_STRLEN(32),
                                   TEST_STRLEN(33),
                                   TEST_STRLEN(63),
                                   TEST_STRLEN(64),
                                   TEST_STRLEN(65)>;

TYPED_TEST_SUITE(Strlen, TypesStrlen);

TYPED_TEST(Strlen, Test) {
    constexpr size_t length = TestFixture::length;
    TestFixture::prepareData(length);

    auto reference = strlen_ref(this->str.c_str());
    auto result = STRLEN_FUNC(this->str.c_str());

    EXPECT_EQ(result, reference);
}
