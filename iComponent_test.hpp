#ifndef __ICOMPONENT_TEST_HPP__
#define __ICOMPONENT_TEST_HPP__

#include "gtest/gtest.h"
#include "headers/iComponent.h"

//Test
TEST(GetTitle, Lowercase){
    Media * m1 = new Media(title, author, 1, 10.00);
    EXPECT_EQ(m1->getTitle(), title);
    setTitle(new_title);
    setQuantityAvailable(5);
    setCost(20.00);
    EXPECT_EQ(m1->getTitle(), new_title);
    EXPECT_EQ(m1->getQuantityAvaialable(), 5);
}

TEST(GetTitle, Uppercase){
    Media * m1 = new Media(TITLE, author, 1, 10.00);
    EXPECT_EQ(m1->getTitle(), TITLE);
    setTitle(NEW_TITLE);
    setQuantityAvailable(5);
    setCost(20.00);
    EXPECT_EQ(m1->getTitle(), new_title);
    EXPECT_EQ(m1->getQuantityAvaialable(), 5);
}

TEST(GetTitle, Empty){
    Media * m2 = new Media(, author, 1, 10.00);
    EXPECT_EQ(m1->getTitle(), NULL);
    setTitle();
    setQuantityAvailable(5);
    setCost(20.00);
    EXPECT_EQ(m1->getTitle(), NULL);
    EXPECT_EQ(m1->getQuantityAvaialable(), 5);
}

TEST(GetQuantity, Positive){
    Media * m2 = new Media(title, author, 1, 10.00);
    setQuantityAvailable(5);
    EXPECT_EQ(m1->getQuantityAvaialable(), 5);
}

TEST(GetQuantity, Negative){
    Media * m2 = new Media(title, author, 1, 10.00);
    setQuantityAvailable(-5);
    EXPECT_EQ(m1->getQuantityAvaialable(), -5);
}

TEST(GetQuantity, Zero){
    Media * m2 = new Media(title, author, 1, 10.00);
    setQuantityAvailable(0);
    EXPECT_EQ(m1->getQuantityAvaialable(), 0);
}

TEST(GetQuantity, LargeNumber){
    Media * m2 = new Media(title, author, 1, 10.00);
    setQuantityAvailable(1000000);
    EXPECT_EQ(m1->getQuantityAvaialable(), 1000000);
}

#endif
