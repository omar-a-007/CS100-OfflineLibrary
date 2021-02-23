#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <vector>

#include "user.h"
#include "trasaction.h"
#include "librarymanagement.h"

class Library
{
	protected:
		User user;
		std::vector<Trasaction *> borrowLog;
		LibraryManagement manager
	private:
		void displayMenu();
		void menuSelection(int selection);
		void borrow();
};

#endif
