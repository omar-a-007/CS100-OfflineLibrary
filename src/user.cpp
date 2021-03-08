#include <string>

#include "../headers/user.h"
#include "../headers/DBwrapper.h"

User::User(const std::string& username, const std::string& password)
{
	login(username, password);
}

bool User::login(const std::string& username, const std::string& password)
{
	privelageLevel = DBwrapper::login(username, encrypt_RSA(password));
	if (privelageLevel > 0) {
		email = username;
		return true;
	}
	return false;
}

bool User::createAccount(const std::string& username, const std::string& password, int privelageLevel)
{
	return DBwrapper::createAccount(username, encrypt_RSA(password), privelageLevel);
}


bool User::deleteAccount(const std::string& password)
{
	if (privelageLevel == 0) return false; // Not logged in, no account to delete.

	std::string encrypted_password = encrypt_RSA(password);
	bool result = DBwrapper::deleteAccount(email, encrypted_password);
	logout();
	return result;
}

bool User::changePassword(const std::string& current_password, const std::string& new_password)
{
	if (privelageLevel == 0) return false; // Not logged in, cant change password.

	return DBwrapper::changePassword(email, encrypt_RSA(current_password), encrypt_RSA(new_password));
}

const std::string User::encrypt_RSA(const std::string& password)
{
	int p = 7;
	int q = 19;
	int n = p * q;
	int e = 29;
	int d = 41;
	int temp = 0;

	int* passwordArray = new int[password.length()];


	for (int i = 0; i < password.length(); i++) {
		passwordArray[i] = (int)password.at(i);
	}
	
	for (int i = 0; i < password.length(); i++) {
		temp = passwordArray[i];
		for (int j = 0; j < e - 1; j++) {
			passwordArray[i] = passwordArray[i] * temp;
			passwordArray[i] = passwordArray[i] % n;
		}
	}


	std::string encryptedString = "";

	for (int i = 0; i < password.length(); i++) {
		encryptedString = encryptedString + (char)passwordArray[i];
	}

	delete[] passwordArray;
	return encryptedString;
}
