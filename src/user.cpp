#include "../headers/user.h"
#include "../headers/constants.h"

User::User(std::string username, std::string password)
{
	login(username, password);
}


bool User::login(std::string username, std::string password)
{
    try
    {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile); // SQLite::OPEN_READONLY
	    SQLite::Statement query(db, "SELECT privelageLevel FROM users WHERE email='" + username + "' and password='" + password +"'");
		if (!query.executeStep()) return false;	 // provided oldPassword doesn't match stored password
		
		this->email = username;
		this->privelageLevel = query.getColumn(0);

		return true;
	}
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        throw(EXIT_FAILURE); // unexpected error : exit the library app
    }
}


bool User::createAccount(std::string username, std::string password, int privelageLevel)
{
    try
	{   // Open DB file for read/write
        SQLite::Database     db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    SQLite::Statement query(db, "SELECT * FROM users WHERE email='" + username + "'");
		if (query.executeStep()) return false;	 // User already exists

		db.exec("INSERT INTO users VALUES (NULL, '" + username + "', '" + password + "', " + std::to_string(privelageLevel) + ")");
		return true;
	}
    catch (std::exception& e)
    {
        std::cout << "SQLite exception A: " << e.what() << std::endl;
        exit(EXIT_FAILURE); // unexpected error : exit the library app
    }
}

bool User::deleteAccount(std::string password)
{
	if (privelageLevel = 0) return false; // Not logged in, no account to delete.
    try
    {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    SQLite::Statement query(db, "SELECT * FROM users WHERE email='" + email + "' and password='" + password +"'");
		if (!query.executeStep()) return false;	 // provided password doesn't match stored password

		db.exec("DELETE FROM users WHERE email='" + email + "'");
		return true;
	}
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        throw(EXIT_FAILURE); // unexpected error : exit the library app
    }
}

bool User::changePassword(std::string oldPassword, std::string newPassword)
{
	if (privelageLevel = 0) return false; // Not logged in, cant change password.
    try
    {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    SQLite::Statement query(db, "SELECT * FROM users WHERE email='" + email + "' and password='" + oldPassword +"'");
		if (!query.executeStep()) return false;	 // provided oldPassword doesn't match stored password

		db.exec("UPDATE users SET password='" + newPassword + "' WHERE email='" + email + "'");
		return true;
	}
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        throw(EXIT_FAILURE); // unexpected error : exit the library app
    }
}
