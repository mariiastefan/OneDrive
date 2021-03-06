#include"User.h"

std::istream& operator>>(std::istream& in, User& obj)
{
	std::cout << "Introduceti username: ";
	in >> obj.m_username;

	while (!obj.verify_username())
	{
		std::cout << "Intoruceti un alt username care sa contina caractere doar mici, mari si cifre !";
		in >> obj.m_username;
	}

	FolderUser newF(obj.m_username);
	return in;
}

std::ostream& operator<<(std::ostream& out, const User& obj)
{
	out << obj.m_username;
	out << " ";
;
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
std::string User::GetUsername() const
{
	return m_username;
}

void User::SetUsername(const std::string& username2) {
	m_username = username2;
}


bool User::verify_username() {
	std::regex verify(R"([a-zA-Z]+\d*$)");
	if (std::regex_match(m_username, verify))
		return true;
	else {
		throw std::overflow_error{ "Username-ul contine caractere nepermise !" };
		return false;
	}
}



bool VerifyIsUsernameExists(std::ifstream& file, const User& obj)
{
	std::string filename("conturi.txt");
	if (!file.is_open()) {
		std::cerr << "Could not open the file - " << filename << "'" << std::endl;
		return EXIT_FAILURE;
	}
	std::ofstream out;
	out.open("temp.txt");
	std::string line;
	std::string deleteline = obj.GetUsername();
	while (std::getline(file, line))
	{
		out << line << std::endl;
		if (line == deleteline)
		{
			out.close();
			file.close();
			return 1;
		}
	}
	
	return 0;
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

	FolderUser aux;
	aux.DeleteFolder(obj.GetUsername());

}
bool User::findUser(std::string name)
{
	for (auto& us : m_user)
	{
		if (us == name)
			return true;
	}
	return false;

}
int User::GetSizeOfFileUser()const
{
	return m_file.size();
}

void User::Update(User user,std::string namedate) 
{
	for (int index = 0; index < user.m_file.size(); index++)
		if (m_file[index].GetFilename() == namedate)
		{
			std::string new_name;
			std::string date;
			std::cin >> new_name >> date;
			m_file[index].ActualizareData(new_name, date);

		}
			
}
void User::safe_date_users(User user)
{
	std::ofstream fil("date_file_users.txt");
	for (auto user : m_user)
	{
		fil << "user:" << user<<'/n';
		for(auto file:m_file)
		{
			fil << "file name:" << file.GetFilename() << '/n';
			fil << "file date:" << file.GetFile_date() << '/n';
			fil << "updated data" << file.GetUpdate_data() << '/n';
			fil << "file size:" << file.GetFile_size() << '/n';
		}
	}
	
}