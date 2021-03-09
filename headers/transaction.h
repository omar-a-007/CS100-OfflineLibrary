#ifndef __TRANSACTION_H_
#define __TRANSACTION_H_

#include <iostream>
#include <vector>

#include "user.h"

class Transaction{
    private:
        int fee;
        int due_date;
    public:
        Transaction();
        void makepayment(int);
        void removeTransaction(std::vector <std::string>, std::string);
        void editTransaction(std::vector <std::string>, std::string);
        void viewTransactions(std::string);
        void set_fee(int);
        void set_due_date(int);
};

#endif