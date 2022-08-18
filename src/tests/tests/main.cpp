#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    constexpr const int tests_run_okay{ 0 };
    constexpr const int tests_run_with_error{ 1 };

    return RUN_ALL_TESTS();
}
