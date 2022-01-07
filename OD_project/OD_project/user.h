#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "FolderUser.h"
#include "file.h"
class User {
private:
	std::string m_username;
	std::vector<std::string>m_user;
	std::vector<File>m_file;
	friend std::istream& operator >> (std::istream& in, User& obj);
	friend std::ostream& operator <<(std::ostream& out, const User& obj);
public:
	User();
	User(const std::string& other_username);
	User(const User& other);
	bool verify_username();
	bool verify_password();
	std::string GetUsername() const;
	void SetUsername(const std::string& username2);

	friend bool VerifyIsUsernameExists(std::ifstream& file, const User& obj);
	friend void DeleteAccount(std::fstream& file, const User& obj);
	bool findUser(std::string name);
	int GetSizeOfFileUser()const;

	void Update(User user, std::string namedate);
	void safe_date_users(User user);
};

