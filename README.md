# Efficient Library System
Authors: \<[Omar Al-kurd](https://github.com/omar-a-007)\>, \<[Sevak Ohanian](https://github.com/SevakOhanian7)\>, \<[Xirong Xie](https://github.com/xxie043)\>

## Project Description
The Effecient Library System is a tool that enables members to catalog a variety of media, spanning across any number of categories and genres. The tool is designed to support effecient storage and retrieval as well as intuitive catalog displays. By logining in the system, users can check their accounts' status, including account grade,    borrow and return history, debt. There are more functions for users, such as borrow, return, and searching. The system will also store books' information for users to search. Books will be organized under different genres/sub-genres. The system will also provide recommendations to users based on their previous reading history. For system manage, administrative accounts will be able to edit both members' and books' information. The administrator can access the member's status; for example, to see if they returned books on time. The administrator can also access books' information; the admin can change the borrow/return status of media and modify the category/genre information.

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

 > ## Phase II
 > In addition to completing the "Class Diagram" section below, you will need to 
 > * Set up your GitHub project board as a Kanban board for the project. It should have columns that map roughly to 
 >   * Backlog, TODO, In progress, In testing, Done
 >   * You can change these or add more if you'd like, but we should be able to identify at least these.
 > * There is no requirement for automation in the project board but feel free to explore those options.
 > * Create an "Epic" (note) for each feature and each design pattern and assign them to the appropriate team member. Place these in the `Backlog` column
 > * Complete your first *sprint planning* meeting to plan out the next 7 days of work.
 >   * Create smaller development tasks as issues and assign them to team members. Place these in the `Backlog` column.
 >   * These cards should represent roughly 7 days worth of development time for your team, taking you until your first meeting with the TA
## Class Diagram
 > Include a class diagram(s) for each design pattern and a description of the diagram(s). Your class diagram(s) should include all the main classes you plan for the project. This should be in sufficient detail that another group could pick up the project this point and successfully complete it. Use proper OMT notation (as discussed in the course slides). You may combine multiple design patterns into one diagram if you'd like, but it needs to be clear which portion of the diagram represents which design pattern (either in the diagram or in the description). 
 
 > ## Phase III
 > You will need to schedule a check-in with the TA (during lab hours or office hours). Your entire team must be present. 
 > * Before the meeting you should perform a sprint plan like you did in Phase II
 > * In the meeting with your TA you will discuss: 
 >   - How effective your last sprint was (each member should talk about what they did)
 >   - Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 >   - Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 >   - What tasks you are planning for this next sprint.

 > ## Final deliverable
 > All group members will give a demo to the TA during lab time. The TA will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Kanban board. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
