#include <gtest/gtest.h>

struct Converter
{
    int files;

    Converter(){}

    explicit Converter(const int count) : files(count){}
};

TEST(ConverterTest, StartsEmpty)
{
    Converter c;
    EXPECT_EQ(0, 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
