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
   //std::string DBwrapper::DBfile = "library.db3";
   

   std::vector<Book*> books1, books2;
   // Fiction
   books1.push_back(new Book("Pride and Prejudice", "Jane Austen", "9780141439518", 480, 9.99));
   books1.push_back(new Book("To Kill a Mockingbird", "Harper Lee", "0060935464", 336, 9.99));
   books1.push_back(new Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", 180, 9.99));
   books1.push_back(new Book("One Hundred Years of Solitude", "Gabriel Garcia Marquez", "0060883286", 417, 13.99));
   books1.push_back(new Book("Brave New World", "Aldous Huxley", "9780451524935", 328, 7.99)); 
   books1.push_back(new Book("Moby Dick: or, the White Whale", "Herman Melville", "1503280780", 379, 12.13)); 
   books1.push_back(new Book("The Lion, the Witch and the Wardrobe", "C.S. Lewis", "9780064404990", 282, 7.64));
   books1.push_back(new Book("One Flew Over the Cuckoo's Nest", "Ken Kesey", "067002323X", 238, 20.80));

   // Non-Fiction
   books2.push_back(new Book("Untamed", "Glennon Doyle", "1984801252", 352, 15.60));
   books2.push_back(new Book("Midnight in Chernobyl: The Untold Story of the World's Greatest Nuclear Disaster", "Adam Higginbotham", "1501134639", 560, 12.79));
   books2.push_back(new Book("A Great and Terrible King: Edward I and the Forging of Britain", "Marc Morris", "1681771330", 480, 17.95));
   books2.push_back(new Book("The Accidental President: Harry S. Truman and the Four Months That Changed the World", "A. J. Baime", "1328505685", 464, 15.60));
   books2.push_back(new Book("The Lost City of the Monkey God: A True Story", "Douglas Preston", "1455540005", 326, 19.56));


   Category* cat1 = new Category("Ficton");
   for (auto& b : books1) cat1->add(b);

   Category* cat2 = new Category("Non-Ficton");
   for (auto& b : books2) cat2->add(b);


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
      //userAction = GetAction(PROMPT[lib.getPrivelageLevel()]);
      //std::cout << userAction << std::endl;
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
