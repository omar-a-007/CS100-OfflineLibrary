#ifndef __USER_H__
#define __USER_H__

#include <string>

class User{
	private:
		int privelageLevel;
		std::string email;
	public:
		User()
			: privelageLevel(0) {};
		User(const std::string& email, const std::string& password);

		int setPrivelageLevel();
		int getPrivelageLevel()		{return this->privelageLevel;};
		std::string getUsername()   {return this->email;};

		void logout()  				{email = ""; privelageLevel = 0;}
		bool login(const std::string& email, const std::string& password);
		bool deleteAccount(const std::string& password);
		bool changePassword(const std::string& current_password, const std::string& new_password);
		bool changePrivelageLevel(const std::string& username, int priv);

		static const std::string encrypt_RSA(const std::string& password);
		static bool createAccount(const std::string& email, const std::string& password, int privelageLevel);
};

#endif
