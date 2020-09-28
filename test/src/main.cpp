#include <continental/fuzzy/service/fuzzy/FuzzyService.h>
#include <gtest/gtest.h>

using namespace continental::fuzzy::service::fuzzy;

TEST(ContinentalFuzzyTest, Test1)
{
    new FuzzyService;
    EXPECT_EQ(1546, 1546);
    EXPECT_DOUBLE_EQ(-51.428723629, -51.428723629);
}

TEST(ContinentalFuzzyTest, Test2)
{
    EXPECT_EQ(100, 100);
    EXPECT_EQ(100, 100);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
