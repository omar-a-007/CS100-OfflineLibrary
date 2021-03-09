#include <iostream>
#include <string>
#include <vector>
#include "../headers/library.h"
#include "../headers/DBwrapper.h"
//#include "../headers/constants.h"

void displayMenu(Library& lib);
char GetAction(std::string prompt);

const std::string DBwrapper::DBfile{"library.db3"};
int main ()
{
   Library lib;

   displayMenu(lib);
}

void displayMenu(Library& lib)
{
   const char EXIT_CODE = 'Q';
std::vector<std::string> PROMPT;

// PROMPT index corresponds to user's privelage level 
// 0 = Guest/not logged in, 1 = Normal User, 2 = Admin

// [0] -- Guest

PROMPT.push_back(R"(----------------------
Welcome to the Library
----------------------
  L - [L]ogin
  C - [C]reate Account
  
  Q - [Q]uit

Choose an option:)");

// [1] -- Normal User
PROMPT.push_back(R"(----------------------
Library Menu
----------------------
  B - [B]orrow from the Library
  
  S - [S]how All Categories
  V - [V]iew All Items with details

  E - [E]xport Database
  
  P - Change [P]assword
  D - [D]elete Account

  Q - [Q]uit

Choose an option:)");

// [2] -- Admin
PROMPT.push_back(R"(----------------------
Library Admin Menu
----------------------
  B - [B]orrow from the Library
  
  S - [S]how All Categories
  V - [V]iew All Items with details

  E - [E]xport Database

  P - Change [P]assword
  C - [C]reate Account
  D - [D]elete Account
  
  Q - [Q]uit

Choose an option:)");

   // Loop until the user enters the exit code.
   char userAction = ' ';
   //userAction = GetAction(PROMPT[lib.getPrivelageLevel()]);

   //while (userAction != EXIT_CODE) {
   while ( (userAction = GetAction(PROMPT[lib.getPrivelageLevel()])) != EXIT_CODE) {
      // Login
      if (userAction == 'L' && lib.getPrivelageLevel() == 0) {
            std::string U, P;
            std::cout << "Please enter your username/email: ";
            std::getline(std::cin, U);
            std::cout << "Please enter your password: ";
            std::getline(std::cin, P);
            (lib.login(U, P) == true)  ?
               std::cout << "Successfully logged in, welcome " + U + "\n" : std::cout << "ERROR! Username or Password provided is incorrect\n";
      }
      // Create Account
      else if (userAction == 'C' && lib.getPrivelageLevel() != 1) {
            std::string U, P, L = "1";
            std::cout << "Please enter a username/email: ";
            std::getline(std::cin, U);
            std::cout << "Please enter a password: ";
            std::getline(std::cin, P);
            if (lib.getPrivelageLevel() == 2) {
               std::cout << "Normal User (1) or Admin User (2)?: ";
               std::getline(std::cin, L);
               if (L != "1" && L != "2") L = "1";
            }
            (lib.createAccount(U, P, std::stoi(L)) == true) ?
               std::cout << "Account created successfully!\n" : std::cout << "ERROR! An account with that username already exists. Please try again.\n";
            if (lib.getPrivelageLevel() != 2) lib.login(U,P);
      }
      // Change Password
      else if (userAction == 'P' && lib.getPrivelageLevel() != 0) {
            std::string P, N;
            std::cout << "Please enter current password: ";
            std::getline(std::cin, P);
            std::cout << "Please enter a new password: ";
            std::getline(std::cin, N);
            (lib.changePassword(P, N) == true ) ? 
               std::cout << "Password has been successfully changed.\n" : std::cout << "ERROR! Incorrect password provided. Please try again.\n";
      }
      
      // Delete Account
      else if (userAction == 'D' && lib.getPrivelageLevel() != 0) {
            std::string Confirm, P;
            std::cout << "Are you sure you want to delete your account? (y/yes to continue): ";
            std::getline(std::cin, Confirm);
            if (toupper(Confirm[0]) != 'Y') continue;

            std::cout << "Please confirm your password: ";
            std::getline(std::cin, P);

            (lib.deleteAccount(P) == true ) ? 
               std::cout << "Account deleted. We're sorry to see you go.\n" : 
               std::cout << "ERROR! Unable to delete account. Incorrect password provided. Please try again.\n";
      }

      // [V]iew All Items
      else if (userAction == 'V' && lib.getPrivelageLevel() != 0) {
            lib.displayMedia();
      }

      // [S]how All Categories
      else if (userAction == 'S' && lib.getPrivelageLevel() != 0) {
            std::cout << "\nList of Categories\n";
            std::cout << "------------------\n";
            lib.displayCategories();
      }
   } 
}

// Get the action the user wants to perform
char GetAction(std::string prompt) {
   std::string answer;
   char firstChar;

   firstChar = '?';

   std::cout << std::endl << prompt << std::endl;
   std::getline(std::cin, answer);
   while(answer.size() == 0) {
      std::getline(std::cin, answer);
   }
   firstChar = toupper(answer[0]);

   return firstChar;
}
