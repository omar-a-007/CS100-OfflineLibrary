CMAKE_MINIMUM_REQUIRED(VERSION 3.1) 

PROJECT(EffecientLibrarySystem)

SET(CMAKE_CXX_STANDARD 11)

#Add GoogleTest
ADD_SUBDIRECTORY(googletest)


# Add SQLite3 C++ wrapper around sqlite3 library (sqlite3 itself provided within SQLiteCpp for ease of use)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(SQLiteCpp)

ADD_EXECUTABLE(library
	src/main.cpp
	src/library.cpp
	src/user.cpp
	src/iComponent.cpp
	src/DBwrapper.cpp
	src/transaction.cpp
)

ADD_EXECUTABLE(temp
	src/temp.cpp
	src/library.cpp
	src/user.cpp
	src/iComponent.cpp
	src/DBwrapper.cpp
	src/transaction.cpp
)

ADD_EXECUTABLE(test
	tests/unit_test.cpp
	src/library.cpp
	src/user.cpp
	src/iComponent.cpp
	src/DBwrapper.cpp
	src/transaction.cpp
)

# Link library and temp executable with SQLiteCpp
TARGET_LINK_LIBRARIES(library SQLiteCpp)
TARGET_LINK_LIBRARIES(temp SQLiteCpp)

 # Link test executable with googleTest and SQLiteCpp
TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(test SQLiteCpp)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
