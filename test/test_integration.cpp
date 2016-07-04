/**
 * test_integration.cpp
 * Purpose: Integration test suite for server/client.
 *
 * @author Sebastian Olsson
 */

#ifndef SERVER_H
#define SERVER_H

#include <gtest/gtest.h>


TEST(EchoTest, HelloWorld) {
    // Unimplemented
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif // SERVER_H
