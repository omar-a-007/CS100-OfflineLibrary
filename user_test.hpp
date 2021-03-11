#ifndef __USER_TEST_HPP__
#define __USER_TEST_HPP__

#include "gtest/gtest.h"
#include "headers/user.h"

//Test getPrivelageLevel()
TEST(pLevel, Default){
    EXPECT_EQ(getPrivelageLevel(), 0);
}

TEST(pLevel, Positive){
    setPrivelageLevel(1);
    EXPECT_EQ(getPrivelageLevel(), 1);
}

TEST(pLevel, Negative){
    setPrivelageLevel(-1);
    EXPECT_EQ(getPrivelageLevel(), -1);
}

TEST(pLevel, LargeNumber){
    setPrivelageLevel(10000);
    EXPECT_EQ(getPrivelageLevel(), 10000);
}

//Test getUsername()
TEST(gName, Empty){
    User(, password);
    EXPECT_EQ(getUsername(), NULL);
}

TEST(gName, Lowercase){
    User(email, password);
    EXPECT_EQ(getUsername(), email);
}

TEST(gName, Uppercase){
    User(EMAIL, password);
    EXPECT_EQ(getUsername(),EMAIL);
}

//TEST

#endif
