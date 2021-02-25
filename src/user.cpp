#include "../headers/user.h"
#include "../headers/constants.h"
#include <string>

User::User(std::string username, std::string password)
{
	login(username, password);
}


bool User::login(std::string username, std::string password)
{
	password = encrypt(password);
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
    password = encrypt(password);	
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
	password = encrypt(password);
	if (privelageLevel == 0) return false; // Not logged in, no account to delete.
    try
    {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    SQLite::Statement query(db, "SELECT * FROM users WHERE email='" + email + "' and password='" + password +"'");
		if (!query.executeStep()) return false;	 // provided password doesn't match stored password

		db.exec("DELETE FROM users WHERE email='" + email + "'");
		this-> email = "";
		this-> privelageLevel = 0;
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
	oldPassword = encrypt(oldPassword);
	newPassword = encrypt(newPassword);
	if (privelageLevel == 0) return false; // Not logged in, cant change password.
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

std::string User::encrypt(std::string password) {

	int p = 7;
	int q = 19;
	int n = p * q;
	int e = 29;
	int d = 41;
	int temp = 0;

	int* passwordArray = new int[password.length()];


	for (int i = 0; i < password.length(); i++) {
		passwordArray[i] = (int)password.at(i);
	}
	
	for (int i = 0; i < password.length(); i++) {
		temp = passwordArray[i];
		for (int j = 0; j < e - 1; j++) {
			passwordArray[i] = passwordArray[i] * temp;
			passwordArray[i] = passwordArray[i] % n;
		}
	}


	std::string encryptedString = "";

	for (int i = 0; i < password.length(); i++) {
		encryptedString = encryptedString + (char)passwordArray[i];
	}

	delete[] passwordArray;
	return encryptedString;
}
