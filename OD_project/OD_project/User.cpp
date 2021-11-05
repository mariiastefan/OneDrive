#include"user.h"
std::istream& operator>>(std::istream& in, User& obj)
{
	std::cout << "Introduceti username: ";
	in >> obj.m_username;
	while (!obj.verify_username())
	{
		std::cout << "Intoruceti un alt username care sa contina caractere doar mici, mari si cifre !";
		in >> obj.m_username;
	}
	std::cout << "Introduceti password: ";
	in >> obj.m_password;
	while (!obj.verify_password())
	{
		std::cout << "Intoruceti o alta parola care sa aiba lungimea mai mare ca 6 si sa contina doar litere mici, mari si cifre !";
		in >> obj.m_password;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const User& obj)
{
	out << obj.m_username;
	out << " ";
	out << obj.m_password;
	out << '\n';
	return out;
}
User::User() {
	m_username = "";
	m_password = "";
}

User::User(const std::string& other_username, const std::string& other_password) :
	m_username{ other_username }, m_password{ other_password }
{}

User::User(const User& obj)
{
	m_username = obj.m_username;
	m_password = obj.m_password;
}
std::string User::GetUsername() const
{
	return m_username;
}
std::string User::GetPassword() const
{
	return m_password;
}
void User::SetUsername(const std::string& username2) {
	m_username = username2;
}
void User::SetPassword(const std::string& password2) {
	m_password = password2;
}
bool User::verify_password()
{
	std::regex reg(R"([a-zA-Z0-9]+$)");
	if (m_password.size() >= 6)
	{
		if (std::regex_match(m_password, reg))
			return true;
		else {
			throw std::overflow_error{ "Nu contine toate caracterele !" };
			return false;
		}
	}
	else {
		throw std::overflow_error{ "Nu e buna lungimea !" };
		return false;
	}
}