#include <iostream>
#include <string>
#include <vector>
 #include <stdexcept>
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
  W - [W]hat am I borrowing
  
  S - [S]how All Categories
  T - [T]itles output with limited details
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
  L - [L]ibrary Management
  W - [W]hat's being borrowed by a user
  
  S - [S]how All Categories
  T - [T]itles output with limited details
  V - [V]iew All Items with details

  E - [E]xport Database

  P - Change [P]assword
  C - [C]reate Account
  D - [D]elete Account
  M - [M]odify User's Privelage Level
  U - [U]ser Account List 
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
      
      // Change Privelage Level
      else if (userAction == 'M' && lib.getPrivelageLevel() == 2) {
         std::string U, P;
         int priv;
         bool isCorrect = false;
         std::cout << "Please enter the name of the user you wish to modify: ";
         std::getline(std::cin, U);
         while(!isCorrect){
            std::cout << "Please enter the new privelage level: ";
            std::getline(std::cin, P);
            try{
               priv = stoi(P);
               isCorrect = true;
            }
            catch(std::exception &err) {
               std::cout << "Must enter either 0, 1, or 2.\n";
            }
         
            if(priv < 0 || priv > 2) {
               std::cout << "Must enter either 0, 1, or 2.\n";
               isCorrect = false;
            }
         } 
         (lib.changePrivelageLevel(U, priv) == true) ?
            std::cout << "Privelage Level has been successfully changed.\n" : std::cout << "ERROR! Incorrect username provided. Pleasse try again.\n";
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
      //U - [U]ser Account List
      else if (userAction == 'U' && lib.getPrivelageLevel() == 2) {
            lib.listUserAccounts();
      }
      else if (userAction == 'B' && lib.getPrivelageLevel() != 0) {
         std::string searchMethod, search; int MID; bool result;
         std::cout << "Would you like to enter the Media ID or Title (Type [T]itle for title)? ";
         std::getline(std::cin>>std::ws, searchMethod);

         searchMethod = searchMethod[0] == 't' || searchMethod[0] == 'T' ? "Title" : "Media ID";

         try {
            std::cout << searchMethod << ": ";       
            std::getline(std::cin>>std::ws, search);
            if (searchMethod == "Media ID") result = lib.borrow(lib.findMedia(stoi(search)));
            else result = lib.borrow(lib.findMedia(search));

            (result) ? std::cout << "Borrowing the item was a success! Please return within 60 days.\nAfter 60 days the item will be considered lost and your account will be charged the replacement cost." << std::endl 
                     : std::cout << "ERROR! Please make sure the Title/MID exist." << std::endl;            
         }
         catch(std::exception &err) { std::cout << "ERROR! " << err.what(); }
      }

      // L - [L]ibrary Management
      else if (userAction == 'L' && lib.getPrivelageLevel() == 2) {
         int input = 0; std::string sInput;
         while (input < 1 || input > 5)
         {
            try {
               std::cout << "\nLibrary Management:\n 1. Create a new Category\n 2. Create a new Media Entry\n 3. Modify a Category's Title\n 4. Modify an item's quantity available\n 5. Return to the previous menu" << std::endl;
               std::getline(std::cin>>std::ws, sInput); input = stoi(sInput);
            } catch(std::exception const& err) { std::cout << "ERROR! Must enter a number." << std::endl; }

            if (input == 1) { // Create Category
               std::string cTitle; std::string cParent; int PID;
               std::cout << "New Category Title: ";
               std::getline(std::cin>>std::ws, cTitle);


               std::cout << "Parent Category ('x' for none): ";
               std::getline(std::cin>>std::ws, cParent);
               
               try{
                  Category* parent = (cParent == "x" || cParent == "X") ? lib.findCategory(0) :  lib.findCategory(cParent);
                  if (parent == nullptr ) throw std::runtime_error("Invalid parent category.");

                  PID = parent->getCID();
                  int CID = DBwrapper::addCategory(PID, cTitle);
                  if (CID == -1) throw std::runtime_error("DB call failed.");

                  parent->add(new Category(cTitle, CID, PID));
                  std::cout<< "Successfully added category.\n\n";
               }
               catch(std::exception const& err) { std::cout << "ERROR! " << err.what() << std::endl; }

               input = 0;    
            }
            else if (input == 2) { // Create Media
               std::string Title, mediaType, Author, ISBN = "", sParent, sLength, sQty, sCost; int CID, MID, Length, Qty; double Cost; bool valid = false;
               while (!valid) {
                  std::cout << "Media Type (Book, DVD, AudioBook) : ";
                  std::getline(std::cin>>std::ws, mediaType);
                  
                  switch (char(std::tolower(mediaType[0])))
                  {
                     case 'b': mediaType = "Book";      valid = true; break;
                     case 'd': mediaType = "DVD";       valid = true; break;
                     case 'a': mediaType = "AudioBook"; valid = true; break;
                  }
               }
               std::cout << "New " << mediaType << " Title: ";   std::getline(std::cin>>std::ws, Title);
               std::cout << "Author or Director: ";              std::getline(std::cin>>std::ws, Author);
               std::cout << "Category ('x' for none): ";         std::getline(std::cin>>std::ws, sParent);
               if (mediaType == "Book") {
                  std::cout << "ISBN: ";                         std::getline(std::cin>>std::ws, ISBN);
               }
               
               try{
                  std::cout << "Page count or Duration (in minutes): ";    std::getline(std::cin>>std::ws, sLength); Length = stoi(sLength);
                  std::cout << "Cost: ";                                   std::getline(std::cin>>std::ws, sCost); Cost = stod(sCost);
                  std::cout << "Quantity: ";                               std::getline(std::cin>>std::ws, sQty); Length = stoi(sQty);

                  Category* parent = (sParent == "x" || sParent == "X") ? lib.findCategory(0) :  lib.findCategory(sParent);
                  if (parent == nullptr ) throw std::runtime_error("Invalid Category.");
                  CID = parent->getCID();

                  MID = DBwrapper::addMedia(CID, mediaType, Title, Author, Cost, Qty, Length, ISBN);
                  if (MID == -1) throw std::runtime_error("DB call failed.");

                  Media* m;
                       if (mediaType == "Book")      m = new Book      (Title, Author, ISBN, Length, Cost, MID, CID, Qty);
                  else if (mediaType == "AudioBook") m = new AudioBook (Title, Author, Length, Cost, MID, CID, Qty);
                  else if (mediaType == "DVD")       m = new DVD       (Title, Author, Length, Cost, MID, CID, Qty);
                  parent->add(m);

                  std::cout<< "Successfully added " << mediaType << std::endl << std::endl;
               }
               catch(std::exception const& err) { std::cout << "ERROR! " << err.what() << std::endl; }

               input = 0;
            }
            else if (input == 3) { // Modify Category Title
               std::string cTitle, nTitle, cParent; bool success;
               std::cout << "Category Title: ";                    std::getline(std::cin>>std::ws, cTitle);
               std::cout << "New Category Title: ";                std::getline(std::cin>>std::ws, nTitle);
               
               try{
                  Category* c = lib.findCategory(cTitle);
                  if (c == nullptr ) throw std::runtime_error("Invalid Category Title.");

                  success = DBwrapper::setCategoryTitle(c->getCID(), nTitle);
                  if (!success) throw std::runtime_error("DB call failed.");

                  c->setTitle(nTitle);
                  std::cout<< "Successfully changed category title.\n\n";
               }
               catch(std::exception const& err) { std::cout << "ERROR! " << err.what() << std::endl; }

               input = 0;
            }
            else if (input == 4) {
               std::string mTitle, sQty; int Qty; bool success;
               
               try{
                  std::cout << "Media Title: ";                 std::getline(std::cin>>std::ws, mTitle);
                  Media* m;
                  m = lib.findMedia(mTitle);
                  if (m == nullptr ) throw std::runtime_error("Invalid Media Title.");

                  std::cout << "New Quantity: ";                std::getline(std::cin>>std::ws, sQty); Qty = stoi(sQty);

                  success = DBwrapper::setMediaQty(m->getMID(), Qty);
                  if (!success) throw std::runtime_error("DB call failed.");

                  m->setTitle(mTitle);
                  std::cout<< "Successfully changed" << mTitle << " quantity.\n" << std::endl;
               }
               catch(std::exception const& err) { std::cout << "ERROR! " << err.what() << std::endl; }

               input = 0;
            }
         }
      }

      // [W]hat's being borrowed by a user
      else if (userAction == 'W' && lib.getPrivelageLevel() != 0) {
         int UID = lib.getUID(); std::string sUID;
         std::string historicalView;
         try {
            if (lib.getPrivelageLevel() == 2) {
               std::cout << "UID to show borrow log of: ";               std::getline(std::cin>>std::ws, sUID); UID = stoi(sUID);
            }
            std::cout << "View history as well (Y/yes)? ";               std::getline(std::cin>>std::ws, historicalView);
            std::cout << "\nBorrow List" << std::endl;
            std::cout << "-----------" << std::endl;
            bool showHistory = (historicalView[0] == 'y' || historicalView[0] == 'Y' ? true : false);

            lib.showTransactions(UID, showHistory);
         }
         catch(std::exception const& err) { std::cout << "ERROR! " << err.what() << std::endl; }
      }


      // [V]iew All Items
      else if (userAction == 'V' && lib.getPrivelageLevel() != 0) {
         lib.display();
      }

      // [T]itles output with limited details
      else if (userAction =='T' && lib.getPrivelageLevel() != 0) {
	      lib.simpleDisplay();
      }

      // [S]how All Categories
      else if (userAction == 'S' && lib.getPrivelageLevel() != 0) {
         std::cout << "\nList of Categories\n";
         std::cout << "------------------\n";
         lib.listCategories();
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
