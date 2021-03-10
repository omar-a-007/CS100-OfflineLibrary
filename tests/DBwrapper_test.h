#ifndef __DBwrapper_TEST_HPP__
#define __DBwrapper_TEST_HPP__

#include "gtest/gtest.h"

#include <string>
#include <list>

#include "../headers/library.h"
#include "../headers/DBwrapper.h"

/*
 *   /================\
 *   *** Usage Note ***
 *   \================/
 *   The DBwrapper class is primarily a helper class, meant to be called by other classes, not used in a standalone fashion.
 *   Some functions, such as createAccount and changePassword *must* be used through other classes (User) in order to function as expected.
 */



TEST(DBwrapperTest, db_Initialization) {
    EXPECT_EQ(remove("test.db3"), 0);

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
    User u;
    EXPECT_TRUE(DBwrapper::createAccount("Z", "Z", 2));
    EXPECT_TRUE(DBwrapper::login(u, "Z", "Z"));
}


TEST(DBwrapperTest, db_login_FAIL_BadUser) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::login should NEVER be accessed directly.
     * Instead, you should call User.login() as it encrypts the checked password properly
     */
    User u;
    EXPECT_EQ(DBwrapper::login(u, "X", "Z"), 0);
}

TEST(DBwrapperTest, db_login_FAIL_BadPass) {
    /* PLEASE READ!!!! 
     * This is for testing puposes ONLY!! DBwrapper::login should NEVER be accessed directly.
     * Instead, you should call User.login() as it encrypts the checked password properly
     */
    User u;
    EXPECT_EQ(DBwrapper::login(u, "Z", "X"), 0);
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



TEST(DBwrapperTest, db_addTransaction_success) {
    EXPECT_EQ(DBwrapper::addTransaction(1, 1, 0), 1);
    EXPECT_EQ(DBwrapper::addTransaction(1, 2, 0), 2);
    EXPECT_EQ(DBwrapper::addTransaction(1, 3, 0), 3);
}

TEST(DBwrapperTest, db_addTransaction_FAIL_badUID) {
    EXPECT_EQ(DBwrapper::addTransaction(99, 1, 0), -1);
}

TEST(DBwrapperTest, db_addTransaction_FAIL_badMID) {
    EXPECT_EQ(DBwrapper::addTransaction(1, 99, 0), -1);
}

TEST(DBwrapperTest, db_modifyTransaction_success) {
    EXPECT_TRUE(DBwrapper::modifyTransaction(1, 1));
}

TEST(DBwrapperTest, db_modifyTransaction_success_largeNumber) {
    EXPECT_TRUE(DBwrapper::modifyTransaction(1, 987546321548));
}

TEST(DBwrapperTest, db_modifyTransaction_success_zero) {
    EXPECT_TRUE(DBwrapper::modifyTransaction(1, 0));
}
TEST(DBwrapperTest, db_modifyTransaction_success_negativeNumber) {
    EXPECT_TRUE(DBwrapper::modifyTransaction(1, -1));
}

TEST(DBwrapperTest, db_modifyTransaction_FAIL_badTID) {
    EXPECT_FALSE(DBwrapper::modifyTransaction(99, 1));
}

TEST(DBwrapperTest, db_getTransactions) {
    std::list<Transaction*> test;
    DBwrapper::getTransactions(1, test);
    EXPECT_EQ(test.size(), 3);
    EXPECT_EQ(test.front()->UID, 1);
    EXPECT_EQ(test.front()->MID, 1);
}


TEST(DBwrapperTest, cleanup)
{
    EXPECT_EQ(remove("test.db3"), 0);
    EXPECT_TRUE(true);
}

#endif