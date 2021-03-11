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
git clone https://github.com/cs100/final-project-oalk001-smaht003-xxie043.git
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

<details><summary>Googletest and Valgrind results</summary>
<p>
 
