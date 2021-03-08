#include <iostream>
#include <string>
#include <vector>
#include <regex> 
#include "../headers/library.h"

#include <SQLiteCpp/SQLiteCpp.h>
//#include "../headers/constants.h"

void test1();
void test2();
bool addCategoryToDB(const int ParentID, const std::string& Title);
bool addMediaToDB(const int CID, const std::string& mediaType, const std::string& Title, const std::string& Author, const double Cost, const int Quantity, const int Length, const std::string& ISBN);

// CleanString
// -- Only use with unbound paramaters
// -- A bound paramater's special characters are escaped by default, no need to clean them up.
const std::string cleanString(const std::string& riskyString)
{
    return std::regex_replace(riskyString, std::regex( "\'" ), "\\'" );
}

const std::string DBwrapper::DBfile{"library.db3"};
int main ()
{
    Library lib;
    std::vector<Category*> cats;
    std::vector<Media*> media;


    lib.DB.getCategories(cats);
    for (auto& c : cats)
    {
        c->display();
    }


    lib.DB.getMedia(media);
    for (auto& m : media)
    {
        m->display();
    }

    return 0;
}

/*
    try {
        SQLite::Database    db("testme.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); 
        db.exec("CREATE TABLE IF NOT EXISTS media (MID INTEGER PRIMARY KEY, CID INTEGER, FOREIGN KEY(CID) REFERENCES category(CID));");
		db.exec("CREATE TABLE IF NOT EXISTS category (CID INTEGER PRIMARY KEY, Title TEXT UNIQUE);");
        db.exec("PRAGMA foreign_keys = ON;"); 

        SQLite::Statement query(db, "INSERT INTO media VALUES (NULL, :CategoryID)");
        //query.bind(":CategoryID", 0);         // Generates FOREIGN KEY constraint failed
        //query.bind(":CategoryID", NULL);      // Unable to build: passing NULL to non-pointer argument
        query.bind(":CategoryID", "NULL");      // Generates FOREIGN KEY constraint failed


        std::cout << query.getExpandedSQL() << std::endl;       // Produces: INSERT INTO media VALUES (NULL, 'NULL')
        std::cout << query.exec() << std::endl;
        remove("testme.db3");
    }
    catch (std::exception& e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        remove("testme.db3");
        exit(EXIT_FAILURE);
    }
*/
/*
bool addMediaToDB(const int CID, const std::string& mediaType, const std::string& Title, const std::string& Author, const double Cost, const int Quantity, const int Length, const std::string& ISBN)
{
    try
    {
        // Open DB file for read/write
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
        return query.exec()  ;  // query.exec will return the number of rows affected by an Insert/Update/Delete
                                // therefore, if the Insert is successful, exec returns 1, otherwise 0
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR! Unable to add item to the DB. Please make sure the item doesn't already exist and the selected category is accurate." << std::endl;
        std::cout << "Error Details... SQLite exception: " << e.what() << std::endl;
        return false;
    }
}
*/
/*
bool addCategoryToDB(const int ParentID, const std::string& Title)
{
    try
    {
        // Open DB file for read/write
        SQLite::Database     db(DBfile, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "INSERT INTO category VALUES (NULL, " + ((ParentID == 0) ? "NULL" : std::to_string(ParentID)) + ", :title)");

        query.bind(":title", Title);

        //std::cout  << query.getExpandedSQL() << std::endl;
        
        db.exec("PRAGMA foreign_keys = ON;");   // Must be run each time a new DB connection is established in order to enforce foreign-key constraints
        return query.exec()  ;  // query.exec will return the number of rows affected by an Insert/Update/Delete
                                // therefore, if the Insert is successful, exec returns 1, otherwise 0
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR! Unable to add category to the DB. Please make sure the category doesn't already exist." << std::endl;
        std::cout << "Error Details... SQLite exception: " << e.what() << std::endl;
        return false;
    }
}
*/


void test_readDB()
{

}

void test1()
{
   std::vector<Book*> books1, books2, books2b;
   // Fiction
   books1.push_back(new Book("Pride and Prejudice", "Jane Austen", "9780141439518", 480, 9.99));
   books1.push_back(new Book("To Kill a Mockingbird", "Harper Lee", "0060935464", 336, 9.99));
   books1.push_back(new Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", 180, 9.99));
   books1.push_back(new Book("One Hundred Years of Solitude", "Gabriel Garcia Marquez", "0060883286", 417, 13.99));
   books1.push_back(new Book("Brave New World", "Aldous Huxley", "9780451524935", 328, 7.99)); 
   books1.push_back(new Book("Moby Dick: or, the White Whale", "Herman Melville", "1503280780", 379, 12.13)); 
   books1.push_back(new Book("The Lion, the Witch and the Wardrobe", "C.S. Lewis", "9780064404990", 282, 7.64));
   books1.push_back(new Book("One Flew Over the Cuckoo's Nest", "Ken Kesey", "067002323X", 238, 20.80));

   // Non-Fiction
   books2.push_back(new Book("Untamed", "Glennon Doyle", "1984801252", 352, 15.60));
   books2.push_back(new Book("Midnight in Chernobyl: The Untold Story of the World's Greatest Nuclear Disaster", "Adam Higginbotham", "1501134639", 560, 12.79));
   books2.push_back(new Book("A Great and Terrible King: Edward I and the Forging of Britain", "Marc Morris", "1681771330", 480, 17.95));
   books2.push_back(new Book("The Accidental President: Harry S. Truman and the Four Months That Changed the World", "A. J. Baime", "1328505685", 464, 15.60));
   books2.push_back(new Book("The Lost City of the Monkey God: A True Story", "Douglas Preston", "1455540005", 326, 19.56));

   // Non-Fiction: Educational
   books2b.push_back(new Book("Python Crash Course, 2nd Edition", "Eric Mathhes", "1593279280", 544, 21.24, 0, 0, 3));
   books2b.push_back(new Book("Cracking the Coding Interview", "Gayle Laakmann McDowell", "0984782869", 687, 26.99, 0, 0, 6));
   books2b.push_back(new Book("Introduction to Algorithms, 3rd Edition (The MIT Press)", "Thomas H. Cormen", "9780262033848", 1292, 68.36, 0, 0, 3));
   books2b.push_back(new Book("Algorithms to Live By: The Computer Science of Human Decisions", "Brian Christian", "1627790365", 368, 0, 0, 2));

    //for (auto& b : books1) b->display();
    //for (auto& b : books2) b->display("\t");



    Category* cat1 = new Category("Ficton");        for (auto& b : books1) cat1->add(b);
    Category* cat2 = new Category("Non-Ficton");    for (auto& b : books2) cat2->add(b);
    Category* cat2b = new Category("Educational");  for (auto& b : books2b) cat2b->add(b);
    cat2->add(cat2b);

    cat1->display();
    cat2->display();

    std::cout << std::endl<< std::endl<< std::endl;

    std::cout << "Items: " << cat1->itemCount() << std::endl;
    
    Media* searchResult = cat2->findMedia("Python Crash Course, 2nd Edition");
    std::cout << (searchResult == nullptr ? "nullptr" : searchResult->getTitle()) << std::endl;
    
    cat2->remove(searchResult);
    cat2->display();

    delete cat1;
    delete cat2;
}

void test2()
{    
    Category* catA = new Category("Root");
    Category* catB = new Category("Has A Category");
    Category* catC = new Category("Has Another Category");
    Category* catD = new Category("Has MOAR Categories");
    Category* catE1 = new Category("Sub Category A");
    Category* catE2 = new Category("Sub Category B");
    Category* catE3 = new Category("Sub Category C");
    Book* bookie = new Book("Algorithms to Live By: The Computer Science of Human Decisions", "Brian Christian", "1627790365", 368, 0, 0, 2);
    Book* bookie2 =new Book("Untamed", "Glennon Doyle", "1984801252", 352, 15.60);

    catA->add(catB);
    catB->add(catC);
    catC->add(catD);
    catD->add(catE1);
    catD->add(catE2);
    catD->add(catE3);
    catE3->add(bookie);
    catE3->add(bookie2);

    catA->display();

    
    std::cout << "Items: " << catA->itemCount() << std::endl;

    Media* searchResult = catA->findMedia("Untamed");

    catA->remove(catA->findMedia("Untamed"));
    catA->remove(searchResult);

    delete catA;
}
