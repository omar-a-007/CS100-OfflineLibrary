#ifndef __USER_H__
#define __USER_H__

#include <string>

class User{
	private:
		int privelageLevel;
		std::string email;
	pubic:
		User(std::string email, std::string password);
		bool login(std::string email, std::string password);
		int setPrivelageLevel();
		int getPrivelageLevel();
		bool createAccount(std::string email, std::string password);
		bool deleteAccount(std::string email, std::string password);
		bool changePassword(std::string oldPassword, std::string newPassword);
};

#endif
