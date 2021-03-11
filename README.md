# Efficient Library System
Authors: \<[Omar Al-kurd](https://github.com/omar-a-007)\>, \<[Sevak Ohanian](https://github.com/SevakOhanian7)\>, \<[Xirong Xie](https://github.com/xxie043)\>

## Project Description
The Effecient Library System is a tool that enables members to catalog a variety of media, spanning across any number of categories and genres. The tool is designed to support effecient storage and retrieval as well as intuitive catalog displays.

By logining in the system, users can check their accounts' status, search, borrow and return history, and debt. Books will be organized under different genres/sub-genres. For system management, administrative accounts will be able to edit both members' and books' information. The administrator can access the member's status; for example, to see if they returned books on time. The administrator can also access books' information; the admin can change the borrow/return status of media and modify the category/genre information.

### Why a library system?
"A library will allow us to explore a variety of design patterns and structures as well as interact with data that is only visible dependent upon the logged in user. With a library system, we can incorporate database technology into our toolset." ~ Omar

"The Library System requires variables independent for each user, which is an important skill for projects in the future. Storing user login-information and creating individualized book recommendations is an instructive portion of the project which I look forward to." ~ Sevak

"Our team picked this program because we are interested in the login system and database. Another primary reason is program is pretty straightforward so we can add more functions to make it a little bit "complex" but works more efficiently." ~ Xirong


 ### Languages/tools/technologies
 The Effecient Library System will be programmed in C++
 * We will be exploring [Firebase](https://firebase.google.com/docs/database/cpp/start) as a database system - Firebase is a Real Time Database developed by Google that utilizes a NoSQL cloud database infrastructure.
 * [Git+Github](https://github.com/) - Version Control and Repsotory systems
 * [GoogleTest](https://github.com/google/googletest) - C++ Unit Testing Framework developed by Google
 * [Valgrind](https://valgrind.org/) - Memory Debugging and Profiling utility to help identify memory leaks and other memory related issues.
 
 ### Inputs and Outputs (IO)
 The inputs and outputs will depend on where in the program the user is.
 * Initially, the user will be promopted to login. The inputs will be the username and password, the output whether login was successful.
 * Following succesful login, users will be presented a menu from which they will be able to access (view) their catalog or modify (add/edit/remove) entries within their catalog.
 * * Inputs for members will include: borrow/return books as well as searching for books. For administrators: edit information of members and books.
 * * The system will also output the information of members and books.
 
 ### Design Patterns
**Composite**: The composite design pattern will be used for system management. For example, after creating an administrator class, it can access catetory or books directly. The administrator class will be able to edit category objects from itself. Basically, the design pattern can help create a class which can be used to build hierarchy of objects in the database of library. After that, it will be more convenient to track the data. 

 **Strategy**: The strategy design pattern will allow us to implement multiple algorithims that are dynamically selected based on criteria such as type of media or display constraints. For instance, when searching or sorting varied media, we will be able to utilize the strategy pattern so that the correct algorithm is used at runtime. 
 
 **Facade**: The Facade design pattern will allow us to encapsulate the more complex or low level operations of the library, keeping the interface offered to the end user simple and intuitive. The more complex subsystems of the program will essentially be hidden away.

## Class Diagram
![OMT](./Efficient%20Library%20System%20-%20OMT.png)
A combination of the Facade, Composition, and Strategy design patterns are used. Overall, the Facade pattern is used to encapsulate the complexity of the various classes and present a simple interface to the Client (user). The Composition class is used to for the catalog of media (books, dvds, audiobooks, etc). By using the composition design pattern, categories of media can have sub categories in an effecient manner. The strategy pattern is used for exporting data, allowing users or admins to export the contents of the library in CSV, JSON, and possibly more classes in the future. 
 
 > ## Final deliverable
 > All group members will give a demo to the TA during lab time. The TA will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Kanban board. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
To install this program, we use `git clone` to get the repository, and `cd` into it.
```
git clone --recursive https://github.com/cs100/final-project-oalk001-smaht003-xxie043.git
cd final-project-oalk001-smaht003-xxie043
```
We will be using `cmake .` and `make` to create executables (use `cmake3 .` on hammer), which will be `test` and `library`.
```
cmake .
make
```
After that, we will run the program by running the `library` executable.
```
./library
```
 ## Testing
For testing, we used `googletest` to conduct unit testing. We have a `unit_test.h` file which includes all unit tests in each class. We create unit tests for each public function with both vaild and invalid input. We run the full battery of tests whenever we introduce a new class or change the way an existing class functions. 

We also tested the program for memory leaks by compiling a debug build and running the program through `valgrind`, simulating typical user and admin operations before quitting, to make sure there's no memory leak. 

<details><summary>Googletest result</summary>


```
[xxie043@hammer final-project-oalk001-smaht003-xxie043]$ ./test
[==========] Running 72 tests from 5 test suites.
[----------] Global test environment set-up.
[----------] 7 tests from iComponentTest
[ RUN      ] iComponentTest.simpleBookLeaf
[       OK ] iComponentTest.simpleBookLeaf (0 ms)
[ RUN      ] iComponentTest.emptyComposite
[       OK ] iComponentTest.emptyComposite (1 ms)
[ RUN      ] iComponentTest.simpleComposite
[       OK ] iComponentTest.simpleComposite (0 ms)
[ RUN      ] iComponentTest.findMedia_DNE
[       OK ] iComponentTest.findMedia_DNE (0 ms)
[ RUN      ] iComponentTest.findCategory_DNE
[       OK ] iComponentTest.findCategory_DNE (0 ms)
[ RUN      ] iComponentTest.nestedComposite_recusriveDisplay
[       OK ] iComponentTest.nestedComposite_recusriveDisplay (0 ms)
[ RUN      ] iComponentTest.nestedCompsosite_recursiveFunctions
[       OK ] iComponentTest.nestedCompsosite_recursiveFunctions (0 ms)
[----------] 7 tests from iComponentTest (1 ms total)

[----------] 11 tests from UserTest
[ RUN      ] UserTest.login_success
[       OK ] UserTest.login_success (50 ms)
[ RUN      ] UserTest.login_FAIL
[       OK ] UserTest.login_FAIL (2 ms)
[ RUN      ] UserTest.createAccount_success
[       OK ] UserTest.createAccount_success (4 ms)
[ RUN      ] UserTest.STATIC_createAccount_success
[       OK ] UserTest.STATIC_createAccount_success (4 ms)
[ RUN      ] UserTest.createAccount_FAIL_AlreadyExists
[       OK ] UserTest.createAccount_FAIL_AlreadyExists (2 ms)
[ RUN      ] UserTest.deleteAccount_success
[       OK ] UserTest.deleteAccount_success (5 ms)
[ RUN      ] UserTest.deleteAccount_FAIL_invalidPass
[       OK ] UserTest.deleteAccount_FAIL_invalidPass (4 ms)
[ RUN      ] UserTest.changePassword_success
[       OK ] UserTest.changePassword_success (5 ms)
[ RUN      ] UserTest.changePassword_FAIL_invalidPassword
[       OK ] UserTest.changePassword_FAIL_invalidPassword (4 ms)
[ RUN      ] UserTest.changePassword_FAIL_notLoggedIn
[       OK ] UserTest.changePassword_FAIL_notLoggedIn (2 ms)
[ RUN      ] UserTest.logout
[       OK ] UserTest.logout (2 ms)
[----------] 11 tests from UserTest (84 ms total)

[----------] 15 tests from TransactionTest
[ RUN      ] TransactionTest.fullConstructor
[       OK ] TransactionTest.fullConstructor (2 ms)
[ RUN      ] TransactionTest.partialConstructor
[       OK ] TransactionTest.partialConstructor (0 ms)
[ RUN      ] TransactionTest.partialConstructor_create_success
[       OK ] TransactionTest.partialConstructor_create_success (1 ms)
[ RUN      ] TransactionTest.partialConstructor_create_FAIL_badMID
ERROR! Unable to add borrow item.
         Error Details... SQLite exception: FOREIGN KEY constraint failed
[       OK ] TransactionTest.partialConstructor_create_FAIL_badMID (1 ms)
[ RUN      ] TransactionTest.partialConstructor_create_FAIL_badUID
ERROR! Unable to add borrow item.
         Error Details... SQLite exception: FOREIGN KEY constraint failed
[       OK ] TransactionTest.partialConstructor_create_FAIL_badUID (0 ms)
[ RUN      ] TransactionTest.createTransaction_success
[       OK ] TransactionTest.createTransaction_success (1 ms)
[ RUN      ] TransactionTest.createTransaction_FAIL_badUID
ERROR! Unable to add borrow item.
         Error Details... SQLite exception: FOREIGN KEY constraint failed
[       OK ] TransactionTest.createTransaction_FAIL_badUID (1 ms)
[ RUN      ] TransactionTest.createTransaction_FAIL_badMID
ERROR! Unable to add borrow item.
         Error Details... SQLite exception: FOREIGN KEY constraint failed
[       OK ] TransactionTest.createTransaction_FAIL_badMID (0 ms)
[ RUN      ] TransactionTest.modifyTransaction
[       OK ] TransactionTest.modifyTransaction (3 ms)
[ RUN      ] TransactionTest.satisfyTransaction
[       OK ] TransactionTest.satisfyTransaction (3 ms)
[ RUN      ] TransactionTest.removeTransaction
[       OK ] TransactionTest.removeTransaction (3 ms)
[ RUN      ] TransactionTest.checkIfOverdue_true
[       OK ] TransactionTest.checkIfOverdue_true (3 ms)
[ RUN      ] TransactionTest.checkIfOverdue_false
[       OK ] TransactionTest.checkIfOverdue_false (1 ms)
[ RUN      ] TransactionTest.display
[       OK ] TransactionTest.display (3 ms)
[ RUN      ] TransactionTest.display_returned_Historical_ONandOFF
[       OK ] TransactionTest.display_returned_Historical_ONandOFF (4 ms)
[----------] 15 tests from TransactionTest (26 ms total)

[----------] 28 tests from DBwrapperTest
[ RUN      ] DBwrapperTest.db_Initialization
[       OK ] DBwrapperTest.db_Initialization (34 ms)
[ RUN      ] DBwrapperTest.db_addCategory_success
[       OK ] DBwrapperTest.db_addCategory_success (1 ms)
[ RUN      ] DBwrapperTest.db_addCategory_FAIL_AlreadyExists
ERROR! Unable to add category to the DB. Please make sure the category doesn't already exist.
         Error Details... SQLite exception: UNIQUE constraint failed: category.Title
[       OK ] DBwrapperTest.db_addCategory_FAIL_AlreadyExists (1 ms)
[ RUN      ] DBwrapperTest.db_addMedia_success
[       OK ] DBwrapperTest.db_addMedia_success (1 ms)
[ RUN      ] DBwrapperTest.db_addMedia_FAIL_AlreadyExists
ERROR! Unable to add item to the DB. Please make sure the item doesn't already exist and the selected category is accurate.
         Error Details... SQLite exception: UNIQUE constraint failed: media.Title
[       OK ] DBwrapperTest.db_addMedia_FAIL_AlreadyExists (0 ms)
[ RUN      ] DBwrapperTest.db_createAccount_success
[       OK ] DBwrapperTest.db_createAccount_success (1 ms)
[ RUN      ] DBwrapperTest.db_createAccount_FAIL_AlreadyExists
[       OK ] DBwrapperTest.db_createAccount_FAIL_AlreadyExists (1 ms)
[ RUN      ] DBwrapperTest.db_changePassword_success
[       OK ] DBwrapperTest.db_changePassword_success (1 ms)
[ RUN      ] DBwrapperTest.db_changePassword_FAIL_BadUser
[       OK ] DBwrapperTest.db_changePassword_FAIL_BadUser (0 ms)
[ RUN      ] DBwrapperTest.db_changePassword_FAIL_BadPass
[       OK ] DBwrapperTest.db_changePassword_FAIL_BadPass (1 ms)
[ RUN      ] DBwrapperTest.db_deleteAccount_success
[       OK ] DBwrapperTest.db_deleteAccount_success (1 ms)
[ RUN      ] DBwrapperTest.db_deleteAccount_FAIL_BadUser
ERROR! Unable to delete the only admin account!
[       OK ] DBwrapperTest.db_deleteAccount_FAIL_BadUser (0 ms)
[ RUN      ] DBwrapperTest.db_deleteAccount_FAIL_BadPass
ERROR! Unable to delete the only admin account!
[       OK ] DBwrapperTest.db_deleteAccount_FAIL_BadPass (0 ms)
[ RUN      ] DBwrapperTest.db_login_success
[       OK ] DBwrapperTest.db_login_success (1 ms)
[ RUN      ] DBwrapperTest.db_login_FAIL_BadUser
[       OK ] DBwrapperTest.db_login_FAIL_BadUser (0 ms)
[ RUN      ] DBwrapperTest.db_login_FAIL_BadPass
[       OK ] DBwrapperTest.db_login_FAIL_BadPass (1 ms)
[ RUN      ] DBwrapperTest.db_getMedia
[       OK ] DBwrapperTest.db_getMedia (0 ms)
[ RUN      ] DBwrapperTest.db_getCategories
[       OK ] DBwrapperTest.db_getCategories (1 ms)
[ RUN      ] DBwrapperTest.db_addTransaction_success
[       OK ] DBwrapperTest.db_addTransaction_success (3 ms)
[ RUN      ] DBwrapperTest.db_addTransaction_FAIL_badUID
ERROR! Unable to add borrow item.
         Error Details... SQLite exception: FOREIGN KEY constraint failed
[       OK ] DBwrapperTest.db_addTransaction_FAIL_badUID (0 ms)
[ RUN      ] DBwrapperTest.db_addTransaction_FAIL_badMID
ERROR! Unable to add borrow item.
         Error Details... SQLite exception: FOREIGN KEY constraint failed
[       OK ] DBwrapperTest.db_addTransaction_FAIL_badMID (1 ms)
[ RUN      ] DBwrapperTest.db_modifyTransaction_success
[       OK ] DBwrapperTest.db_modifyTransaction_success (1 ms)
[ RUN      ] DBwrapperTest.db_modifyTransaction_success_largeNumber
[       OK ] DBwrapperTest.db_modifyTransaction_success_largeNumber (1 ms)
[ RUN      ] DBwrapperTest.db_modifyTransaction_success_zero
[       OK ] DBwrapperTest.db_modifyTransaction_success_zero (1 ms)
[ RUN      ] DBwrapperTest.db_modifyTransaction_success_negativeNumber
[       OK ] DBwrapperTest.db_modifyTransaction_success_negativeNumber (1 ms)
[ RUN      ] DBwrapperTest.db_modifyTransaction_FAIL_badTID
[       OK ] DBwrapperTest.db_modifyTransaction_FAIL_badTID (0 ms)
[ RUN      ] DBwrapperTest.db_getTransactions
[       OK ] DBwrapperTest.db_getTransactions (0 ms)
[ RUN      ] DBwrapperTest.cleanup
[       OK ] DBwrapperTest.cleanup (0 ms)
[----------] 28 tests from DBwrapperTest (55 ms total)

[----------] 11 tests from LibraryTest
[ RUN      ] LibraryTest.login_success
[       OK ] LibraryTest.login_success (34 ms)
[ RUN      ] LibraryTest.login_FAIL
[       OK ] LibraryTest.login_FAIL (2 ms)
[ RUN      ] LibraryTest.createAccount_success
[       OK ] LibraryTest.createAccount_success (3 ms)
[ RUN      ] LibraryTest.STATIC_createAccount_success
[       OK ] LibraryTest.STATIC_createAccount_success (3 ms)
[ RUN      ] LibraryTest.createAccount_FAIL_AlreadyExists
[       OK ] LibraryTest.createAccount_FAIL_AlreadyExists (2 ms)
[ RUN      ] LibraryTest.deleteAccount_success
[       OK ] LibraryTest.deleteAccount_success (3 ms)
[ RUN      ] LibraryTest.deleteAccount_FAIL_invalidPass
[       OK ] LibraryTest.deleteAccount_FAIL_invalidPass (4 ms)
[ RUN      ] LibraryTest.changePassword_success
[       OK ] LibraryTest.changePassword_success (4 ms)
[ RUN      ] LibraryTest.changePassword_FAIL_invalidPassword
[       OK ] LibraryTest.changePassword_FAIL_invalidPassword (3 ms)
[ RUN      ] LibraryTest.changePassword_FAIL_notLoggedIn
[       OK ] LibraryTest.changePassword_FAIL_notLoggedIn (1 ms)
[ RUN      ] LibraryTest.borrowMedia
[       OK ] LibraryTest.borrowMedia (4 ms)
[----------] 11 tests from LibraryTest (63 ms total)

[----------] Global test environment tear-down
[==========] 72 tests from 5 test suites ran. (229 ms total)
[  PASSED  ] 72 tests.
```
</details>

<details><summary>Valgrind result</summary>

```
[xxie043@hammer final-project-oalk001-smaht003-xxie043]$ valgrind --leak-check=full ./library
==10661== Memcheck, a memory error detector
==10661== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==10661== Using Valgrind-3.12.0 and LibVEX; rerun with -h for copyright info
==10661== Command: ./library
==10661== HEAP SUMMARY:
==10661==     in use at exit: 0 bytes in 0 blocks
==10661==   total heap usage: 1,104 allocs, 1,104 frees, 686,418 bytes allocated
==10661==
==10661== All heap blocks were freed -- no leaks are possible
==10661==
==10661== For counts of detected and suppressed errors, rerun with: -v
==10661== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
</details>
