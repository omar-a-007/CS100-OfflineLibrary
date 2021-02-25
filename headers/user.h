#ifndef __USER_H__
#define __USER_H__

#include <string>

class User{
	private:
		int privelageLevel;
		std::string email;
		std::string encrypt(std::string password);
	public:
		User()
			{privelageLevel = 0;};
		User(std::string email, std::string password);
		bool login(std::string email, std::string password);
		int setPrivelageLevel();
		int getPrivelageLevel()		{return this->privelageLevel;};
		std::string getUsername()   {return this->email;};
		bool createAccount(std::string email, std::string password, int privelageLevel);
		bool deleteAccount(std::string password);
		bool changePassword(std::string oldPassword, std::string newPassword);
};

#endif
