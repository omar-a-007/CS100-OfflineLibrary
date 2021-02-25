#include <iostream>
#include "../headers/library.h"
//#include "../headers/constants.h"

void displayMenu();
void menuSelection(int);

int main ()
{
    Library lib; 

    (lib.createAccount("b", "b") == true) ?
        std::cout << "Account created successfully!\n" :
        std::cout << "An account with that username already exists, please try again.\n";
    (lib.createAccount("a", "abc") == true) ? 
        std::cout << "Account created successfully!\n" : 
        std::cout << "ERROR! An account with that username already exists. Please try again.\n";

    (lib.login("a", "a") == true)  ?
        std::cout << "Successfully logged in, welcome " + lib.getUsername() + "\n" : 
        std::cout << "ERROR! Username or Password provided is incorrect\n";

    (lib.login("a", "abc") == true)  ?
        std::cout << "Successfully logged in, welcome " + lib.getUsername() + "\n" : 
        std::cout << "ERROR! Username or Password provided is incorrect\n";

    (lib.changePassword("ab", "a") == true ) ? 
        std::cout << "Password has been successfully changed.\n" : 
        std::cout << "ERROR! Unable to change password. Incorrect password provided. Please try again.\n";

    (lib.changePassword("abc", "a") == true ) ? 
        std::cout << "Password has been successfully changed.\n" : 
        std::cout << "ERROR! Unable to change password. Incorrect password provided. Please try again.\n";

    (lib.changePassword("a", "abc") == true ) ? 
        std::cout << "Password has been successfully changed.\n" : 
        std::cout << "ERROR! Incorrect password provided. Please try again.\n";

    (lib.deleteAccount("abc") == true ) ? 
        std::cout << "Account deleted. We're sorry to see you go.\n" : 
        std::cout << "ERROR! Unable to delete account. Incorrect password provided. Please try again.\n";
}

void displayMenu()
{

}

void menuSelection(int selection)
{

}