#ifndef __DBwrapper_TEST_HPP__
#define __DBwrapper_TEST_HPP__

#include "gtest/gtest.h"

#include <string>
#include <list>
#include <iterator>
#include <sstream>

#include "../headers/library.h"
#include "../headers/DBwrapper.h"

using namespace std;

// DBwrapper();

// static int login( username, password);
// static bool createAccount( username, password, int privelageLevel);
// static bool deleteAccount( username, password);
// static bool changePassword( username, cur_pass, new_pass);

// int addCategory(const int ParentID, const std::string& Title);
// int addMedia(const int CID, const std::string& mediaType, const std::string& Title, const std::string& Author, const double Cost, const int Quantity, const int Length, const std::string& ISBN);

// void getCategories(std::list<Category*>& v);
// void getMedia(std::list<Media*>& v);


/*
 *   /================\
 *   *** Usage Note ***
 *   \================/
 *   The DBwrapper class is primarily a helper class, meant to be called by other classes, not used in a standalone fashion.
 *   Some functions, such as createAccount and changePassword *must* be used through other classes (User) in order to function as expected.
 */

TEST(DBwrapperTest, db_Initialization) {
    DBwrapper db;   // Checks the current DB version, deletes the DB if theres an update.
                    // Then creates a DB with a slew of default data if no DB is found.
    User u;
    EXPECT_TRUE(u.login("admin", "pass"));  // A new DB should have an admin account created
}

TEST(DBwrapperTest, db_addCategory_success) {
    EXPECT_TRUE(DBwrapper::addCategory(0, "New Category") > 0); // Returns CID
}

TEST(DBwrapperTest, db_addCategory_FAIL_AlreadyExists) {
    EXPECT_EQ(DBwrapper::addCategory(0, "New Category"), -1);
}

TEST(DBwrapperTest, db_addMedia_success) {    
    EXPECT_TRUE(DBwrapper::addMedia(0, "Book", "New Book", "Somebody", 5.99, 0, 120, "123789X") > 0); // Returns CID
}

TEST(DBwrapperTest, db_addMedia_FAIL_AlreadyExists) {    
    EXPECT_EQ(DBwrapper::addMedia(0, "Book", "New Book", "Somebody", 5.99, 0, 120, "123789X"), -1); // Returns CID
}

TEST(DBwrapperTest, db_createAccount_success) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::createAccount should NEVER be accessed directly.
     * Instead, you should call User.createAccount() as it encrypts the password
     */
    EXPECT_TRUE(DBwrapper::createAccount("ABC", "A", 2));
}

TEST(DBwrapperTest, db_createAccount_FAIL_AlreadyExists) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::createAccount should NEVER be accessed directly.
     * Instead, you should call User.createAccount() as it encrypts the password
     */
    EXPECT_FALSE(DBwrapper::createAccount("ABC", "A", 2));
}

TEST(DBwrapperTest, db_changePassword_success) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::changePassword should NEVER be accessed directly.
     * Instead, you should call User.changePassword() as it encrypts the passwords
     */
    EXPECT_TRUE(DBwrapper::changePassword("ABC", "A", "B"));
}

TEST(DBwrapperTest, db_changePassword_FAIL_BadUser) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::changePassword should NEVER be accessed directly.
     * Instead, you should call User.changePassword() as it encrypts the passwords
     */
    EXPECT_FALSE(DBwrapper::changePassword("ABD", "B", "B"));
}

TEST(DBwrapperTest, db_changePassword_FAIL_BadPass) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::changePassword should NEVER be accessed directly.
     * Instead, you should call User.changePassword() as it encrypts the passwords
     */
    EXPECT_FALSE(DBwrapper::changePassword("ABC", "A", "B"));
}

TEST(DBwrapperTest, db_deleteAccount_success) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::deleteAccount should NEVER be accessed directly.
     * Instead, you should call User.deleteAccount() as it encrypts the checked password properly
     */
    EXPECT_TRUE(DBwrapper::deleteAccount("ABC", "B"));
}

TEST(DBwrapperTest, db_deleteAccount_FAIL_BadUser) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::deleteAccount should NEVER be accessed directly.
     * Instead, you should call User.deleteAccount() as it encrypts the checked password properly
     */
    EXPECT_FALSE(DBwrapper::deleteAccount("ABC", "B"));
}

TEST(DBwrapperTest, db_deleteAccount_FAIL_BadPass) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::deleteAccount should NEVER be accessed directly.
     * Instead, you should call User.deleteAccount() as it encrypts the checked password properly
     */
    EXPECT_FALSE(DBwrapper::deleteAccount("admin", "invalid"));
}

TEST(DBwrapperTest, db_login_success) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::login should NEVER be accessed directly.
     * Instead, you should call User.login() as it encrypts the checked password properly
     */
    EXPECT_TRUE(DBwrapper::createAccount("Z", "Z", 2));
    EXPECT_EQ(DBwrapper::login("Z", "Z"), 2);
}


TEST(DBwrapperTest, db_login_FAIL_BadUser) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::login should NEVER be accessed directly.
     * Instead, you should call User.login() as it encrypts the checked password properly
     */
    EXPECT_EQ(DBwrapper::login("X", "Z"), 0);
}

TEST(DBwrapperTest, db_login_FAIL_BadPass) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::login should NEVER be accessed directly.
     * Instead, you should call User.login() as it encrypts the checked password properly
     */
    EXPECT_EQ(DBwrapper::login("Z", "X"), 0);
}

TEST(DBwrapperTest, db_getMedia) {
    std::list<Media*> test;
    DBwrapper::getMedia(test);
    EXPECT_EQ(test.size(), 22);
    EXPECT_EQ(test.front()->getTitle(), "Untamed");
}

TEST(DBwrapperTest, db_getCategories) {
    std::list<Category*> test;
    DBwrapper::getCategories(test);
    EXPECT_EQ(test.size(), 4);
    EXPECT_EQ(test.front()->getTitle(), "Non-Fiction");
    EXPECT_EQ(test.front()->getPID(), 0);

    auto iter = test.begin(); ++iter; ++iter;
    EXPECT_EQ((*iter)->getTitle(), "Educational");
    EXPECT_EQ((*iter)->getPID(), 1);
}




TEST(DBwrapperTest, cleanup)
{
    remove("test.db3");
}

#endif