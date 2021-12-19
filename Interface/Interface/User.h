#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
//#include "FolderUser.h"
class User {
private:
	std::string m_username;
	std::string m_password;
	std::vector<std::string>m_user;
	friend std::istream& operator >> (std::istream& in, User& obj);
	friend std::ostream& operator <<(std::ostream& out, const User& obj);
public:
	User();
	User(const std::string& other_username);
	User(const User& other);
	bool verify_username();
	std::string GetUsername() const;
	std::string GetPassword() const;
	void SetUsername(const std::string& username2);
	void SetPassword(const std::string& password2);
	friend bool verify_if_user_exists(std::ifstream& file, const User& obj);
	friend void delete_account(std::fstream& file, const User& obj);
	bool findUser(std::string name);
};
