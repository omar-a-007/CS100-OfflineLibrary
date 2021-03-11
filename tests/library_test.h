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
    EXPECT_EQ(lib.getUID(), 0);
    EXPECT_EQ(lib.getUsername(), "");
    EXPECT_EQ(lib.getPrivelageLevel(), 0);    
    EXPECT_TRUE(lib.login("admin", "pass"));   
    EXPECT_EQ(lib.getUID(), 1);
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

TEST(LibraryTest, findMedia_ByTitle_success) {
    Library lib;
    Media* m  = lib.findMedia("Ghandi");
    EXPECT_TRUE(m != nullptr);

    EXPECT_EQ(m->getTitle(), "Ghandi");
}

TEST(LibraryTest, findMedia_ByMID_success) {
    Library lib;
    Media* m  = lib.findMedia(1);
    EXPECT_TRUE(m != nullptr);

    EXPECT_EQ(m->getTitle(), "Ghandi");
}

TEST(LibraryTest, findMedia_ByTitle_FAIL_doesntExist) {
    Library lib;
    Media* m  = lib.findMedia("ASDGF");
    EXPECT_TRUE(m == nullptr);
}

TEST(LibraryTest, findMedia_ByMID_FAIL_doesntExist) {
    Library lib;
    Media* m  = lib.findMedia(999);
    EXPECT_TRUE(m == nullptr);
}

TEST(LibraryTest, findCategory_ByTitle_success) {
    Library lib;
    Category* c = lib.findCategory("Fiction");
    EXPECT_TRUE(c != nullptr);

    EXPECT_EQ(c->getTitle(), "Fiction");
}

TEST(LibraryTest, findCategory_ByMID_success) {
    Library lib;
    Category* c = lib.findCategory(2);
    EXPECT_TRUE(c != nullptr);

    EXPECT_EQ(c->getTitle(), "Fiction");
}

TEST(LibraryTest, findCategory_ByTitle_FAIL_doesntExist) {
    Library lib;
    Category* c = lib.findCategory("ASDGF");
    EXPECT_TRUE(c == nullptr);
}

TEST(LibraryTest, findCategory_ByMID_FAIL_doesntExist) {
    Library lib;
    Category* c = lib.findCategory(999);
    EXPECT_TRUE(c == nullptr);
}

TEST(LibraryTest, listUserAccounts) {
    Library lib;

    stringstream testSS;
    lib.listUserAccounts(testSS);
    EXPECT_EQ(testSS.str(), "[1] admin");
}


TEST(LibraryTest, borrowMedia) {
    Library lib;
    EXPECT_TRUE(lib.login("admin", "pass"));
    
    Media* m  = lib.findMedia("Ghandi");
    EXPECT_EQ(m->getQuantityAvailable(), 2);

    EXPECT_TRUE(lib.borrow(m));
    EXPECT_EQ(m->getQuantityAvailable(), 1);
}



#endif