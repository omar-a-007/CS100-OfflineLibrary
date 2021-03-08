#include <string>
#include <iostream>
#include <cstdlib>
#include <vector> 

#include "../headers/DBwrapper.h"
//#include "../headers/user.h"

DBwrapper::DBwrapper()
{
    DBversion = "0.94";
    if (checkDBversion() != DBversion) remove(DBfile.c_str());
    initDB();
}

/************************************************************************************************************
 * 
 *  Media and Category Related SQL Queries
 * 
 * **********************************************************************************************************/

int DBwrapper::addCategory(const int ParentID, const std::string& Title)
{
    try {   // Open DB file for read/write
        SQLite::Database     db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "INSERT INTO category VALUES (NULL, " + ((ParentID == 0) ? "NULL" : std::to_string(ParentID)) + ", :title)");
        query.bind(":title", Title);

        //std::cout  << query.getExpandedSQL() << std::endl;
        db.exec("PRAGMA foreign_keys = ON;");   // Must be run each time a new DB connection is established in order to enforce foreign-key constraints
        query.exec();

        SQLite::Statement query2(db, "SELECT CID FROM category WHERE Title = :title");
        query2.bind(":title", Title);
        query2.executeStep();
        return query2.getColumn(0);

    }
    catch (std::exception& e) {
        std::cout << "ERROR! Unable to add category to the DB. Please make sure the category doesn't already exist." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
        return false;
    }
}

int DBwrapper::addMedia(const int CID, const std::string& mediaType, const std::string& Title, const std::string& Author, const double Cost, const int Quantity, const int Length, const std::string& ISBN)
{
    try {   // Open DB file for read/write
        SQLite::Database     db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
        SQLite::Statement query(db, "INSERT INTO media VALUES (NULL, " + ((CID == 0) ? "NULL" : std::to_string(CID)) + ", :mediaType, :title, :author, :cost, :qty, :length, :isbn)");        

        query.bind(":mediaType", mediaType);
        query.bind(":title", Title);       
        query.bind(":author", Author);
        query.bind(":cost", Cost);
        query.bind(":qty", Quantity);
        query.bind(":length", Length);
        query.bind(":isbn", ISBN);

        //std::cout  << query.getExpandedSQL() << std::endl;
        db.exec("PRAGMA foreign_keys = ON;");   // Must be run each time a new DB connection is established in order to enforce foreign-key constraints
        query.exec();

        SQLite::Statement query2(db, "SELECT MID FROM media WHERE Title = :title");
        query2.bind(":title", Title);
        query2.executeStep();
        return query2.getColumn(0);
    }
    catch (std::exception& e) {
        std::cout << "ERROR! Unable to add item to the DB. Please make sure the item doesn't already exist and the selected category is accurate." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
        return false;
    }
}

void DBwrapper::getCategories(std::vector<Category*>& v)
{
    try {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile); // SQLite::OPEN_READONLY
	    SQLite::Statement query(db, "SELECT * FROM category ORDER BY CID;");
		while (query.executeStep())
        {
            v.push_back( new Category(query.getColumn("Title"), query.getColumn("CID"), query.getColumn("ParentID")) );
        }
	}
    catch (std::exception& e) {
        std::cout << "ERROR! There was an issue reading the categories from the DB." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
    }
}


void DBwrapper::getMedia(std::vector<Media*>& v)
{
    try {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile); // SQLite::OPEN_READONLY
	    SQLite::Statement query(db, "SELECT * FROM media ORDER BY MID;");
		while (query.executeStep())
        {
            std::string mediaType = query.getColumn("MediaType");
            int MID = query.getColumn("MID"), CID = query.getColumn("CID");
            int qty = query.getColumn("Quantity"), contentsCount = query.getColumn("contentsCount");
            double cost =  query.getColumn("Cost");


            if (mediaType == "Book") {
                v.push_back(new Book (query.getColumn("Title"), query.getColumn("Author"), query.getColumn("ISBN"), contentsCount, cost, MID, CID, qty));
            }
            else if (mediaType == "AudioBook") {
                v.push_back(new AudioBook (query.getColumn("Title"), query.getColumn("Author"), contentsCount, cost, MID, CID, qty));
            }
            else if (mediaType == "DVD") {
                v.push_back(new DVD (query.getColumn("Title"), query.getColumn("Author"), contentsCount, cost, MID, CID, qty));
            }            
        }
	}
    catch (std::exception& e) {
        std::cout << "ERROR! There was an issue reading the categories from the DB." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
    }
}

/************************************************************************************************************
 * 
 *  Account Related SQL Queries
 * 
 *  + int login(username, password)                          -- Validate login credentials, returns privelageLevel
 *  + bool createAccount(username, password, privelageLevel) -- Insert a new user account
 *  + bool deleteAccount(username, password)                 -- Delete a user's account
 *  + bool changePassword(username, old_pass, new_pass)      -- Change a user's password
 * 
 * **********************************************************************************************************/

int DBwrapper::login(const std::string& username, const std::string& password)
{
    try {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile); // SQLite::OPEN_READONLY
	    SQLite::Statement query(db, "SELECT privelageLevel FROM users WHERE email= :user and password= :pass;");
        query.bind(":user", username);
        query.bind(":pass", password);
		if (!query.executeStep()) return 0;	 // No records returned, user pass combo is invalid
		
		return query.getColumn(0);
	}
    catch (std::exception& e) {
        std::cout << "ERROR! There was an issue logging in." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DBwrapper::createAccount(const std::string& username, const std::string& password, int privelageLevel)
{
    try {   // Open DB file for read/write
        SQLite::Database     db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    SQLite::Statement query(db, "SELECT * FROM users WHERE email='" + username + "'");
		if (query.executeStep()) return false;	 // User already exists

        SQLite::Statement query2(db, "INSERT INTO users VALUES (NULL, :user, :pass, :level);");
        query2.bind(":user", username);
        query2.bind(":pass", password);
        query2.bind(":level", privelageLevel);
        return query2.exec();
	}
    catch (std::exception& e) {
        std::cout << "ERROR! Unable to create account! Please make sure the email address isn't already registered." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
        return false;
    }
}

bool DBwrapper::deleteAccount( const std::string& username, const std::string& password)
{		
    try {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    /*
        SQLite::Statement query(db, "SELECT * FROM users WHERE email = :email and password = :pass");
        query.bind(":email", username);
        query.bind(":pass", password);
		if (!query.executeStep()) return false;	 // provided password doesn't match stored password
        */
	    SQLite::Statement query2(db, "DELETE FROM users WHERE email = :email AND password = :pass;");
        query2.bind(":email", username);
        query2.bind(":pass", password);
		return query2.exec();
	}
    catch (std::exception& e) {
        std::cout << "ERROR! Unable to delete account!" << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;
        return false;
    }
}

bool DBwrapper::changePassword(const std::string& username, const std::string& current_password, const std::string& new_password)
{
    try {	// Open DB file in read-only mode
        SQLite::Database    db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
	    SQLite::Statement query(db, "UPDATE users SET password = :new_pass WHERE email = :email AND password = :cur_pass;");
        query.bind(":email", username);
        query.bind(":cur_pass", current_password);
        query.bind(":new_pass", new_password);

        return query.exec();
	}
    catch (std::exception& e) {
        std::cout << "ERROR! Unable to change password! Please make sure you entered your current password correctly." << std::endl;
        std::cout << "\t Error Details... SQLite exception: " << e.what() << std::endl;

        return false;
    }
}

/************************************************************************************************************
 * 
 *  DB Initialization Relation Functions
 * 
 *  + initDB() -- Create Tables (+Admin Account) to establish the framework of the DB 
 *  + initPopulateDB() -- Populate the DB with some initial data
 *  - checkDBversion()
 *  - const string setDBversion() const
 * 
 * **********************************************************************************************************/

void DBwrapper::initDB()
{
    //std::cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;
    //std::cout << "SQliteC++ version " << SQLITECPP_VERSION << std::endl;
    try
    {    // Connect to Library DB

        // Open Database File for Read/Write access
        // Currently uses SQLite due to restrictions of Hammer server
        SQLite::Database    db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
        //std::cout << "Library database opened successfully\n";
        //std::cout << db.execAndGet("PRAGMA foreign_keys").getInt() << std::endl;

        bool newDB = !(db.tableExists("users"));

        // Initialize tables if they dont exist
        db.exec("PRAGMA foreign_keys = ON;");
        db.exec("CREATE TABLE IF NOT EXISTS users ("
					"UID INTEGER PRIMARY KEY, "
                    "email TEXT, "
                    "password TEXT, "
                    "privelageLevel INTEGER"
                ");");
        db.exec("CREATE TABLE IF NOT EXISTS transactions ("
                    "TID INTEGER PRIMARY KEY, "
                    "UID INTEGER, MID INTEGER, "
                    "DueDate INTEGER, "
                    "FOREIGN KEY(UID) REFERENCES users(UID), "
                    "FOREIGN KEY(MID) REFERENCES media(MID)"
                ");");
        db.exec("CREATE TABLE IF NOT EXISTS media ("
                    "MID INTEGER PRIMARY KEY, "
                    "CID INTEGER, "
                    "MediaType TEXT, "
                    "Title TEXT UNIQUE, "
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
                    "Title TEXT UNIQUE, "
                    "FOREIGN KEY (ParentID) REFERENCES category(CID)"
                ");");
		db.exec("CREATE TABLE IF NOT EXISTS DBversion ("
                    "version INTEGER "
                ");");

        if (newDB) initPopulateDB();
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE); // unexpected error : exit the library app
    }
}

void DBwrapper::initPopulateDB()
{
    setDBversion();
    createAccount("admin", "pass", 2);
    

    addCategory(0, "Non-Fiction");
    addCategory(0, "Fiction");
    addCategory(1, "Educational");

    // Non-Fiction
    addMedia(1, "Book", "Untamed", "Glennon Doyle", 15.60, 7, 352, "1984801252");
    addMedia(1, "DVD", "Ghandi", "Richard Attenborough", 12.99, 2, 122, "");
    addMedia(1, "DVD", "The Last Samurai", "Edward Zwick", 2.19, 12, 154, "");
    addMedia(1, "DVD", "The Day After Tomorrow", "Roland Emmerich", 1.49, 1, 124, "");
    addMedia(1, "DVD", "Wal-Mart: The High Cost of Low Price", "Robert Greenwald", 8.99, 9, 98, "");
    addMedia(1, "DVD", "The Founder", "John Lee Hancock", 3.99, 12, 115, "");
    addMedia(1, "AudioBook", "A Promised Land", "Barrack Obama", 40.00, 6, 1750, "");


    // Fiction
    addMedia(2, "Book", "Moby Dick: or, the White Whale", "Herman Melville", 12.13, 7, 379, "1503280780");
    addMedia(2, "Book", "The Lion, the Witch and the Wardrobe", "C.S. Lewis", 7.64, 5, 282, "9780064404990");
    addMedia(2, "Book", "One Flew Over the Cuckoo's Nest", "Ken Kesey", 20.80, 9, 238, "067002323X");
    addMedia(2, "DVD", "Willy Wonka & The Chocolate Factory", "Mel Stuart", 3.99, 17, 99, "");
    addMedia(2, "DVD", "Black Box", "Emmanuel Osei-Kuffour", 9.99, 9, 100, "");
    addMedia(2, "DVD", "Ready Player One", "Richard Attenborough", 14.99, 3, 139, "");
    addMedia(2, "DVD", "Archive", "Gavin Rothery", 7.99, 1, 109, "");
    addMedia(2, "AudioBook", "Ready Player Two", "Ernest Cline", 25.00, 2, 1426, "");

    // Non-Fiction: Educational
    addMedia(3, "Book", "Cracking the Coding Interview", "Gayle Laakmann McDowell", 26.99, 27, 687, "0984782869");
    addMedia(3, "Book", "Introduction to Algorithms, 3rd Edition (The MIT Press)", "Thomas H. Cormen", 68.36, 1, 1292, "9780262033848");
    addMedia(3, "Book", "Algorithms to Live By: The Computer Science of Human Decisions", "Brian Christian", 20.42, 6, 368, "1627790365");
    addMedia(3, "DVD", "The Tomb of the Scythian Prince", "Marc Jampolsky", 6.99, 3, 52, "");
    addMedia(3, "AudioBook", "The 7 Habits of Highly Effective People", "Stephen R. Covey", 25.00, 12, 907, "");
    addMedia(3, "AudioBook", "MicroShifts: Transforming Your Life One Step at a Time", "Gary Jansen", 10.00, 4, 131, "");
}


void DBwrapper::setDBversion()
{
    try {   // Open DB file for Read/Write access
        SQLite::Database     db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
        SQLite::Statement query(db, "INSERT INTO DBversion VALUES (:version)");
        query.bind(":version", DBversion);
        query.exec();
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE); // unexpected error : exit the library app
    }
}

const std::string DBwrapper::checkDBversion() const
{
    try {   // Open DB file for read-only access
        SQLite::Database     db(DBfile);
        return db.execAndGet("SELECT version FROM DBversion;");
    }
    catch (std::exception& e) {
        return "";
    }

}