#include "../headers/transaction.h"

// make a payment for what user owes
void Transaction::makepayment(int amount){
    fee -= amount; 
}

// remove a transaction
void Transaction::removeTransaction(std::vector <std::string> userdata, std::string username){
    for(int i = 0; i < userdata.size; ++i){
        if (userdata.at(i) == username){
            userdata.erase(i);
        }
    }
}

// edit a transaction
void Transaction::editTransaction(std::vector <std::string> userdata, std::string username){

}

// view the list of transactions of the user
void Transaction::viewTransactions(std::string username){
    std::cout << "Username: " << username << std::endl 
              << "Paid: " << amount << std::endl
              << "Owe: " << fee << std::endl
              << "Due in: " << due_date << " day(s)." << std::endl;
}

// set the fee user owes
void Transaction::set_fee(int fee){
    this->fee = fee;
}

// set the due date 
void Transaction::set_due_date(int due_date){
    this->due_date = due_date;
}