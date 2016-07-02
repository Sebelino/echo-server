/* Copyright 2016 Sebastian Olsson */

#include <gtest/gtest.h>

#ifndef SERVER_H
    #define SERVER_H
#include "../src/server.hpp"

TEST(SquareRootTest, PositiveNos) {
    EXPECT_EQ(18.0, square_root(324));
    EXPECT_EQ(25.4, square_root(645.16));
    EXPECT_EQ(4, square_root(16));
}

TEST(SquareRootTest, ZeroAndNegativeNos) {
    ASSERT_EQ(0.0, square_root(0.0));
    EXPECT_ANY_THROW({
        square_root(-22.0);
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif // SERVER_H
