#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <list>
#include <string>
#include <iostream>

#include "user.h"
#include "libraryManagement.h"
#include "DBwrapper.h"
#include "transaction.h"

class Library : public LibraryManagement
{
	private:
		Category* recreateCompositeFromDB();	// Returns a "Root" category node with the composite structure re-created based on whats in the DB
		void clearBorrowLog() {for (auto i : borrowLog) delete i;}

	protected:
		User user;
		std::list<Transaction *> borrowLog;

	public:
		DBwrapper DB;
		
		Library();
		~Library() {clearBorrowLog();};

		// User-related Functions
		bool login(const std::string& username, const std::string& password)									{return user.login(username, password);}
		bool createAccount(const std::string& username, const std::string& password, int privelageLevel = 1)	{return User::createAccount(username, password, privelageLevel);}
		bool deleteAccount(const std::string& password)															{return user.deleteAccount(password);}
		bool changePassword(const std::string& current_password, const std::string& new_password)				{return user.changePassword(current_password, new_password);}
		bool changePrivelageLevel(const std::string& username, int priv)										{return user.changePrivelageLevel(username, priv);}	
		
		std::string getUsername()	{return user.getUsername();}
		int getPrivelageLevel()		{return user.getPrivelageLevel();}
		int getUID()				{return user.getUID();}
		
		// Transaction Related Functions (borrowing, late payments, etc)
		void showTransactions(int UID, bool showHistory, std::ostream& stream = std::cout);
		void makePayment(int);
		bool borrow(Media*);

		// Export
		void exportData(const std::string& filename, Exporter*);
};

#endif
