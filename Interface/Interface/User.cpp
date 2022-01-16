#include"user.h"
#include <sstream>

std::istream& operator>>(std::istream& in, User& obj)
{
	std::cout << "Introduceti username: ";
	in >> obj.m_username;
	return in;
}

std::ostream& operator<<(std::ostream& out, const User& obj)
{
	out << obj.m_username;
	out << '\n';
	return out;
}

User::User() {
	m_username = "";
}

User::User(const std::string& other_username) :
	m_username{ other_username }
{}

User::User(const User& obj)
{
	m_username = obj.m_username;
}
User::User(const std::string& username, const std::vector<std::string> user) : m_username{ username }, m_user{ user }
{
}
std::string User::GetUsername() const
{
	return m_username;
}

void User::SetUsername(const std::string& username) {
	m_username = username;
}

bool User::VerifyUserExistance(std::fstream& file)
{
	file.open("conturi.txt", std::ios::in);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line == m_username)
			{
				file.close();
				return true;
			}
		}
		file.close();
	}
	return false;
}

bool User::VerifyUsername() {
	std::regex verify(R"([a-zA-Z]+\d*$)");
	if (std::regex_match(m_username, verify))
		return true;
	else {
		throw std::overflow_error{ "Username-ul contine caractere nepermise !" };
		return false;
	}
}
void DeleteAccount(std::fstream& file, const User& obj)
{
	std::string filename("conturi.txt");
	std::ofstream out;
	file.open(filename);
	out.open("temp.txt");
	std::string line;
	std::string deleteline = obj.GetUsername();
	while (std::getline(file, line))
	{
		if (line != deleteline)
			out << line << std::endl;
	}
	out.close();
	file.close();
	remove("conturi.txt");
	rename("temp.txt", "conturi.txt");
}
