#ifndef __LIBRARY_TEST_H__
#define __LIBRARY_TEST_H__

#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <sstream>

#include "../headers/library.h"

using namespace std;

TEST(LibraryTest, login_success) {
    Library lib;
    EXPECT_EQ(lib.getUsername(), "");
    EXPECT_EQ(lib.getPrivelageLevel(), 0);    
    EXPECT_TRUE(lib.login("admin", "pass"));   
    EXPECT_EQ(lib.getUsername(), "admin");
    EXPECT_EQ(lib.getPrivelageLevel(), 2);
}

TEST(LibraryTest, login_FAIL) {
    Library lib;
    EXPECT_FALSE(lib.login("admin", "invalid"));
}

TEST(LibraryTest, createAccount_success) {
    Library lib;  
    EXPECT_TRUE(lib.createAccount("a", "abc", 1));
    EXPECT_TRUE(lib.login("a", "abc"));
}

TEST(LibraryTest, STATIC_createAccount_success) {
    Library lib;
    EXPECT_TRUE(User::createAccount("AAA", "BBB", 2));
}

TEST(LibraryTest, createAccount_FAIL_AlreadyExists) {
    Library lib;
    EXPECT_FALSE(lib.createAccount("admin", "abc", 1));
}

TEST(LibraryTest, deleteAccount_success) {
    Library lib;
    EXPECT_TRUE(lib.createAccount("b", "abc", 1));
    EXPECT_TRUE(lib.login("b", "abc"));
    EXPECT_TRUE(lib.deleteAccount("abc"));
    // A deleted account should be logged out
    EXPECT_EQ(lib.getUsername(), "");
    EXPECT_EQ(lib.getPrivelageLevel(), 0);
}

TEST(LibraryTest, deleteAccount_FAIL_invalidPass) {
    Library lib;
    EXPECT_TRUE(lib.createAccount("c", "abc", 1));
    EXPECT_TRUE(lib.login("c", "abc"));
    EXPECT_FALSE(lib.deleteAccount("bbb"));
    // Account not deleted, stay logged in
    EXPECT_EQ(lib.getUsername(), "c");
    EXPECT_EQ(lib.getPrivelageLevel(), 1);
}

TEST(LibraryTest, changePassword_success) {
    Library lib;
    EXPECT_TRUE(lib.createAccount("d", "abc", 1));
    EXPECT_TRUE(lib.login("d", "abc"));
    EXPECT_TRUE(lib.changePassword("abc", "def"));
}

TEST(LibraryTest, changePassword_FAIL_invalidPassword) {
    Library lib;
    EXPECT_TRUE(lib.createAccount("e", "abc", 1));
    EXPECT_TRUE(lib.login("e", "abc"));
    EXPECT_FALSE(lib.changePassword("zzz", "def"));
}

TEST(LibraryTest, changePassword_FAIL_notLoggedIn) {
    Library lib;
    EXPECT_FALSE(lib.changePassword("zzz", "def"));
}

#endif