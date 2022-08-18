#include <gtest/gtest.h>

void print(auto &&r)
{
    std::ranges::for_each(std::forward<decltype(r)>(r), [](auto &&i) { std::cout << i << ' '; });
}

TEST(EverydayProblems, Transform)
{
    auto in = std::vector<int>{ 1, 2, 3, 4 };
    auto out = std::vector<int>(in.size());
    auto lambda = [](auto &&i) { return i * i; };

    std::ranges::transform(in, out.begin(), lambda);

    // print(out);
    // Output: 1 4 9 16

    EXPECT_EQ(out.front(), 1);
    EXPECT_EQ(out.back(), 16);
}

TEST(EverydayProblems, Fill)
{
    std::vector<int> in_vector(4);
    std::ranges::fill(in_vector, -1);

    // print(in_vector);
    // Output: -1 -1 -1 -1

    EXPECT_EQ(in_vector.front(), -1);
    EXPECT_EQ(in_vector.back(), -1);
}

