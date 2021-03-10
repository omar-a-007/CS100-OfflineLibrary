#ifndef __TRANSACTIONS_H_
#define __TRANSACTIONS_H_

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string> 

#include "iComponent.h"

class Transaction{
    public:
        enum LoanStatus {REMOVED = -1, PASTDUE = -2, RETURNED = 0};
        int TID, UID, MID;
        long DueDate;

        Transaction(int UID, int MID, bool createNewTransaction = true)
            : UID(UID), MID(MID), TID(0), DueDate(0)          { if (createNewTransaction) createTransaction();};
        Transaction(int TID, int UID, int MID, long DueDate)
            : TID(TID), UID(UID), MID(MID), DueDate(DueDate)  { checkIfOverdue(); };
        ~Transaction() { }

        bool createTransaction();

        bool modifyDueDate(int days_delta);
        bool removeTransaction();
        bool satisfyTransaction();
        void checkIfOverdue();

        void display (Category* root, bool showHistory = false, std::ostream& stream = std::cout);
};

#endif