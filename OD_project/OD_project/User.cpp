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