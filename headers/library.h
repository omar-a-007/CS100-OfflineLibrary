#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <list>
#include <string>

#include "user.h"
#include "transaction.h"
#include "libraryManagement.h"
#include "DBwrapper.h"

class Library
{
	private:
		Category* recreateCompositeFromDB();	// Returns a "Root" category node with the composite structure re-created based on whats in the DB

	protected:
		User user;
		std::list<Transaction *> borrowLog;
		LibraryManagement manager;

	public:
		DBwrapper DB;
		
		Library();
		~Library();
		//void initDB(std::string filename = DBfile);


		// User-related Functions
		bool login(const std::string& username, const std::string& password)									{return user.login(username, password);}
		bool createAccount(const std::string& username, const std::string& password, int privelageLevel = 1)	{return User::createAccount(username, password, privelageLevel);}
		bool deleteAccount(const std::string& password)															{return user.deleteAccount(password);}
		bool changePassword(const std::string& current_password, const std::string& new_password)				{return user.changePassword(current_password, new_password);}
		bool changePrivelageLevel(const std::string& username, int priv)				{return user.changePrivelageLevel(username, priv);}	
		
		std::string getUsername()	{return user.getUsername();};
		int getPrivelageLevel()		{return user.getPrivelageLevel();};
		
		// Transaction Related Functions (borrowing, late payments, etc)
		void makePayment(int);
		void borrow(Media*);

		// Library Related Functions
		void displayMedia()				{manager.display();}
		void displaySimpleMedia()			{manager.simpleDisplay();}
		void displayCategories()		{manager.listCategories();}

		void addCategory(Category* cat, Category* parent = nullptr);
		void removeCategory(Category* cat);

		void removeMedia(Media*);
		void findMedia(Media*);

		// Export
		void exportData(const std::string& filename, Exporter*);
};

#endif
