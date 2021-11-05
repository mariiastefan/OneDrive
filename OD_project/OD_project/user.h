#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
class User {
private:
	std::string m_username;
	std::string m_password;
	friend std::istream& operator >> (std::istream& in, User& obj);
	friend std::ostream& operator <<(std::ostream& out, const User& obj);
public:
	User();
	User(const std::string& other_username, const std::string& other_password);
	User(const User& other);
	bool verify_username();
	bool verify_password();
	std::string GetUsername() const;
	std::string GetPassword() const;
	void SetUsername(const std::string & username2) ;
	void SetPassword(const std::string & password2) ;
	friend void delete_account(std::ifstream &file, const User & obj);
	friend bool verify_if_user_exists(std::ifstream& file, const User& obj);
};
