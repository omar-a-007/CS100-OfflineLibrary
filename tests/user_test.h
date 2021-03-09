#ifndef __USER_TEST_HPP__
#define __USER_TEST_HPP__

#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <sstream>

#include "../headers/library.h"

using namespace std;

TEST(UserTest, login_success) {
    Library lib;
    User u;

    EXPECT_EQ(u.getUsername(), "");
    EXPECT_EQ(u.getPrivelageLevel(), 0);
    
    EXPECT_TRUE(u.login("admin", "pass"));
    
    EXPECT_EQ(u.getUsername(), "admin");
    EXPECT_EQ(u.getPrivelageLevel(), 2);
}

TEST(UserTest, login_FAIL) {
    Library lib;
    User u;

    EXPECT_FALSE(u.login("admin", "invalid"));
}

TEST(UserTest, createAccount_success) {
    Library lib;
    User u;

    EXPECT_TRUE(u.createAccount("a", "abc", 1));
    EXPECT_TRUE(u.login("a", "abc"));
}

TEST(UserTest, STATIC_createAccount_success) {
    Library lib;

    EXPECT_TRUE(User::createAccount("AAA", "BBB", 2));
}

TEST(UserTest, createAccount_FAIL_AlreadyExists) {
    Library lib;
    User u;

    EXPECT_FALSE(u.createAccount("admin", "abc", 1));
}

TEST(UserTest, deleteAccount_success) {
    Library lib;
    User u;

    EXPECT_TRUE(u.createAccount("b", "abc", 1));
    EXPECT_TRUE(u.login("b", "abc"));
    EXPECT_TRUE(u.deleteAccount("abc"));

    // A deleted account should be logged out
    EXPECT_EQ(u.getUsername(), "");
    EXPECT_EQ(u.getPrivelageLevel(), 0);
}

TEST(UserTest, deleteAccount_FAIL_invalidPass) {
    Library lib;
    User u;

    EXPECT_TRUE(u.createAccount("c", "abc", 1));
    EXPECT_TRUE(u.login("c", "abc"));
    EXPECT_FALSE(u.deleteAccount("bbb"));

    // Account not deleted, stay logged in
    EXPECT_EQ(u.getUsername(), "c");
    EXPECT_EQ(u.getPrivelageLevel(), 1);
}

TEST(UserTest, changePassword_success) {
    Library lib;
    User u;

    EXPECT_TRUE(u.createAccount("d", "abc", 1));
    EXPECT_TRUE(u.login("d", "abc"));
    EXPECT_TRUE(u.changePassword("abc", "def"));
}

TEST(UserTest, changePassword_FAIL_invalidPassword) {
    Library lib;
    User u;

    EXPECT_TRUE(u.createAccount("e", "abc", 1));
    EXPECT_TRUE(u.login("e", "abc"));
    EXPECT_FALSE(u.changePassword("zzz", "def"));
}

TEST(UserTest, changePassword_FAIL_notLoggedIn) {
    Library lib;
    User u;

    EXPECT_FALSE(u.changePassword("zzz", "def"));
}

TEST(UserTest, logout) {
    Library lib;
    User u;

    EXPECT_TRUE(u.login("admin", "pass"));
    u.logout();
    EXPECT_EQ(u.getUsername(), "");
    EXPECT_EQ(u.getPrivelageLevel(), 0);
}

#endif