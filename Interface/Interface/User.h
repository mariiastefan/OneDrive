#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
//#include "FolderUser.h"
class User {
private:
	std::string m_username;
	std::vector<std::string>m_user;
	friend std::istream& operator >> (std::istream& in, User& obj);
	friend std::ostream& operator <<(std::ostream& out, const User& obj);
	friend void DeleteAccount(std::fstream& file, const User& obj);

public:
	User();
	User(const std::string& other_username);
	User(const User& other);
	User(const std::string& username, const std::vector<std::string>user);

	std::string GetUsername() const;
	void SetUsername(const std::string& username);

	bool VerifyUserExistance(std::fstream& file);
	bool VerifyUsername();
	
};