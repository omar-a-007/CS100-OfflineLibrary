#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <vector>
#include <string>

#include "user.h"
#include "transaction.h"
#include "libraryManagement.h"
#include "constants.h"

class Library
{
	protected:
		User user;
		std::vector<Transaction *> borrowLog;
		LibraryManagement manager;
		Exporter* exporter;

	public:
		Library();
		void initDB(std::string filename = DBfile);


		// User-related Functions
		bool login(std::string username, std::string password)									{return user.login(username, password);}
		bool createAccount(std::string username, std::string password, int privelageLevel = 1)	{return user.createAccount(username, password, privelageLevel);}
		bool deleteAccount(std::string password)												{return user.deleteAccount(password);}
		bool changePassword(std::string oldPass, std::string newPass)							{return user.changePassword(oldPass,newPass);}

		std::string getUsername()	{return user.getUsername();};
		int getPrivelageLevel()		{return user.getPrivelageLevel();};
		
		// Transaction Related Functions (borrowing, late payments, etc)
		void makePayment(int);
		void borrow(Media*);

		// Library Related Functions
		void displayMedia();
		void displayCategories();

		void addCategory(Category* cat, Category* parent = nullptr);
		void removeCategory(Category* cat);

		void removeMedia(Media*);
		void findMedia(Media*);

		// Export
		void exportData(std::string filename, Exporter*);
};

#endif
