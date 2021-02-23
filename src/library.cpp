#include "../headers/library.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <SQLiteCpp/SQLiteCpp.h>

Library::Library()
{
	// Initilaize the Library

	// Connect to Library DB
	connectToLibrary();
}



void Library::displayMenu()
{
}

void Library::menuSelection(int selection)
{
}


// Connect to Library DB
// Currently uses SQLite due to restrictions of Hammer server
void Library::connectToLibrary()
{
	// Open Database File for Read/Write access
		SQLite::Database    db("library.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	db.exec("CREATE TABLE IF NOT EXIST users (
			UID INTEGER PRIMARY KEY,
			email TEXT,
			password TEXT)");

}


void Library::borrow()
{
}
