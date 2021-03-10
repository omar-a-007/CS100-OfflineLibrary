#ifndef __TRANSACTION_TEST_HPP__
#define __TRANSACTION_TEST_HPP__

#include "gtest/gtest.h"

#include <string>
#include <sstream>
#include <iostream>

#include "../headers/library.h"
#include "../headers/transaction.h"

using namespace std;

TEST(TransactionTest, fullConstructor) {
    Library lib;
    // Popuolate a test object with all variables. Good use-case is when retrieving transactions from DB.
    Transaction test (1, 1, 1, 0);  
    EXPECT_EQ(test.MID, 1);
    EXPECT_EQ(test.TID, 1);
    EXPECT_EQ(test.UID, 1);
    EXPECT_EQ(test.DueDate, 0);
}

TEST(TransactionTest, partialConstructor) {
    // Partial variables, good for creating new transactions where a helper function will determine the DueDate and the DB will return the TID
    Transaction test (1, 1, false);
    EXPECT_EQ(test.TID, 0);
    EXPECT_EQ(test.DueDate, 0);
}

TEST(TransactionTest, partialConstructor_create_success) {
    Transaction test (1, 1, true);
    EXPECT_EQ(test.TID, 1);
}

TEST(TransactionTest, partialConstructor_create_FAIL_badMID) {
    Transaction test (1, 0, true);
    EXPECT_EQ(test.TID, -1);
}

TEST(TransactionTest, partialConstructor_create_FAIL_badUID) {
    Transaction test (0, 1, true);
    EXPECT_EQ(test.TID, -1);
}

TEST(TransactionTest, createTransaction_success) {
    Transaction test (2, 1, 1, 0);
    EXPECT_TRUE(test.createTransaction());
}

TEST(TransactionTest, createTransaction_FAIL_badUID) {
    Transaction test (3, 0, 1, 0);
    EXPECT_FALSE(test.createTransaction());
}

TEST(TransactionTest, createTransaction_FAIL_badMID) {
    Transaction test (3, 1, 0, 0);
    EXPECT_FALSE(test.createTransaction());
}

TEST(TransactionTest, modifyTransaction) {
    Transaction test (1, 1, true);
    EXPECT_TRUE(test.modifyDueDate(+1));    
    EXPECT_TRUE(test.DueDate > 0);
}

TEST(TransactionTest, satisfyTransaction) {
    Transaction test (1, 1, true);
    EXPECT_TRUE(test.modifyDueDate(+1));
    EXPECT_TRUE(test.satisfyTransaction());
    EXPECT_EQ(test.DueDate, Transaction::RETURNED);
}

TEST(TransactionTest, removeTransaction) {
    Transaction test (1, 1, true);
    EXPECT_TRUE(test.modifyDueDate(+1));
    EXPECT_TRUE(test.removeTransaction());
    EXPECT_EQ(test.DueDate, Transaction::REMOVED);
}

TEST(TransactionTest, checkIfOverdue_true) {
    Transaction test (1, 1, 1, Transaction::REMOVED);
    EXPECT_TRUE(test.modifyDueDate(+3));
    test.checkIfOverdue();
    EXPECT_EQ(test.DueDate, Transaction::PASTDUE);
}

TEST(TransactionTest, checkIfOverdue_false) {
    Transaction test (1, 1, 1, Transaction::PASTDUE);
    EXPECT_TRUE(test.satisfyTransaction());
    test.checkIfOverdue();
    EXPECT_EQ(test.DueDate, Transaction::RETURNED);
}

TEST(TransactionTest, display) {
    Library lib;
    Transaction test (1, 3, true);

    stringstream testSS;
    test.display(lib.root, false, testSS);
    EXPECT_EQ(testSS.str(), "[ID: 6] The Last Samurai\n     ---Due in: 60 days\n");
}

TEST(TransactionTest, display_returned_Historical_ONandOFF) {
    Library lib;
    Transaction test (1, 3, true);
    EXPECT_TRUE(test.satisfyTransaction());

    stringstream testSS;
    test.display(lib.root, false, testSS);
    EXPECT_EQ(testSS.str(), "");

    test.display(lib.root, true, testSS);
    EXPECT_EQ(testSS.str(), "[ID: 7 | Returned]     The Last Samurai\n");
}




#endif