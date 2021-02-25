#include "../headers/library.h"
#include "../headers/user.h"
#include "../headers/constants.h"

Library::Library()
{
	// Initilaize the Library

	// Setup/Create DB if its not setup yet
	initDB(DBfile);
}


void Library::borrow(Media* media)
{
}


void Library::initDB(std::string file) /* file = DBfile */
{
    //std::cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;
    //std::cout << "SQliteC++ version " << SQLITECPP_VERSION << std::endl;

    try
    {
        // Connect to Library DB

        // Open Database File for Read/Write access
        // Currently uses SQLite due to restrictions of Hammer server
        SQLite::Database    db(file, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
        //std::cout << "Library database opened successfully\n";

        db.exec("PRAGMA foreign_keys = ON;");
        //std::cout << db.execAndGet("PRAGMA foreign_keys").getInt() << std::endl;

        // Initialize tables if they dont exist
        bool addAdminAcct = !(db.tableExists("users"));

        db.exec("CREATE TABLE IF NOT EXISTS users ("
					"UID INTEGER PRIMARY KEY, "
                    "email TEXT, "
                    "password TEXT, "
                    "privelageLevel INTEGER"
                ");");
        if (addAdminAcct) user.createAccount("admin", "pass", 2);

        
        db.exec("CREATE TABLE IF NOT EXISTS transactions ("
                    "TID INTEGER PRIMARY KEY, "
                    "UID INTEGER, MID INTEGER, "
                    "DueDate INTEGER, "
                    "FOREIGN KEY(UID) REFERENCES users(UID), "
                    "FOREIGN KEY(MID) REFERENCES media(MID)"
                ");");
        db.exec("CREATE TABLE IF NOT EXISTS media ("
                    "MID INTEGER PRIMARY KEY, CID INTEGER, "
                    "Title TEXT, "
                    "Author TEXT, "
                    "Cost INTEGER, "
                    "Quantity INTEGER, "
                    "contentsCount INTEGER, "
                    "ISBN TEXT, "
                    "FOREIGN KEY(CID) REFERENCES category(CID)"
                ");");
		db.exec("CREATE TABLE IF NOT EXISTS category ("
                    "CID INTEGER PRIMARY KEY, "
                    "ParentID INTEGER, "
                    "Title TEXT"
                ");");

    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE); // unexpected error : exit the library app
    }
}