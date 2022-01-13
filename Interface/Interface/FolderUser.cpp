#include "FolderUser.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <cstdio>
using namespace std::chrono_literals;


FolderUser::FolderUser()
{
	m_nrItems = 0;
}

FolderUser::FolderUser(std::string userName)
{
	m_FolderName = userName;
	m_nrItems = 0;

	std::wstring pathOrigin = fs::current_path();
	std::string path1 = "../../TcpConnection/Client/UserFolder";
	fs::create_directory(path1);
	fs::current_path(path1);
	fs::create_directory(userName);
	path1 += "/";
	m_path = path1 + m_FolderName;
	m_path2 = path1 + m_FolderName;
	fs::current_path(pathOrigin);
	std::string path2 = "../../TcpConnection/Server/UserFolder";
	fs::create_directory(path2);
	fs::current_path(path2);
	fs::create_directory(userName);
	fs::current_path(pathOrigin);

	m_date = fs::last_write_time(m_path);
}
FolderUser::FolderUser(std::string foldername, fs::path path, fs::file_time_type date, std::vector<std::string> filename) : m_FolderName{ foldername }, m_path{ path }, m_date{ date }, m_fileName{ filename }
{
	std::wstring pathOrigin = fs::current_path();
	std::string path1 = "../../Client/UserFolder";
	fs::current_path(path1);
	fs::create_directory(foldername);
	path1 += "/";
	m_path = path1 + m_FolderName;

	fs::current_path(pathOrigin);
	std::string path2 = "../../Server/UserFolder";
	fs::current_path(path2);
	fs::create_directory(foldername);
	fs::current_path(pathOrigin);
}

void FolderUser::DeleteFolder(std::string userName)
{
	std::string pathClient = "../../Client/UserFolder";
	std::string pathServer = "../../Server/UserFolder";
	std::wstring pathOrigin = fs::current_path();
	fs::current_path(pathClient);
	std::uintmax_t n1 = fs::remove_all(userName);
	fs::current_path(pathOrigin);
	fs::current_path(pathServer);
	std::uintmax_t n2 = fs::remove_all(userName);
	fs::current_path(pathOrigin);
}
void FolderUser::DeleteUsernameFolder()
{
	fs::remove_all(m_path);
}
void FolderUser::DeleteFile(std::string username, std::string file)
{
	namespace fs = std::filesystem;
	std::string pathClient = "../../TcpConnection/Client/UserFolder";
	std::string pathServer = "../../TcpConnection/Server/UserFolder";
	pathClient += '/';
	pathClient += username;
	pathClient += '/';
	pathClient += file;
	std::uintmax_t n1 = fs::remove(pathClient);
	pathServer += '/';
	pathServer += username;
	pathServer += '/';
	pathServer += file;
	std::uintmax_t n2 = fs::remove(pathServer);

}
void FolderUser::DeleteFile()
{
	fs::path path;
	std::cout << "Introduceti calea fisierului pe care doriti sa il stergeti: ";
	std::cin >> path;
	std::uintmax_t deleted = fs::remove(path);
}
std::string FolderUser::GetFolderName() const
{
	return m_FolderName;
}
int FolderUser::GetNrItems()const
{
	return m_nrItems;
}
void FolderUser::SetFolderName(const std::string& foldername2)
{
	m_FolderName = foldername2;
}


void FolderUser::SetNrItems()
{
	std::string pathClient = "../../Client/UserFolder";
	std::string pathServer = "../../Server/UserFolder";
	std::wstring pathOrigin = fs::current_path();

	pathClient += "/";
	pathClient += m_FolderName;
	fs::current_path(pathClient);

	int m_nrItems_local = 0;
	for (auto const& dir_entry : std::filesystem::directory_iterator{ fs::current_path() })
		m_nrItems_local++;
	fs::current_path(pathOrigin);

	pathServer += "/";
	pathServer += m_FolderName;
	fs::current_path(pathServer);

	int m_nrItems_server = 0;
	for (auto const& dir_entry : std::filesystem::directory_iterator{ fs::current_path() })
		m_nrItems_server++;
	fs::current_path(pathOrigin);

	m_nrItems = m_nrItems_server;

	if (m_nrItems_server == m_nrItems_local) std::cout << std::endl << "Fisiere sincronizate" << std::endl;
	else std::cout << std::endl << "Fisierele nu sunt sincronizate cu serverul" << std::endl;
}

void FolderUser::AddFile()
{
	fs::path path, helpPath;
	std::cout << "Introduceti calea fisierului pe care doriti sa il adaugati: ";
	std::cin >> path;
	std::cout << path.filename().string();
	fs::current_path(m_path);
	helpPath = m_path;
	helpPath += "/";
	helpPath += path.filename().string();
	fs::copy(path, fs::current_path());
}

bool FolderUser::VerifyFolderName(FolderUser folder, std::string name)
{
	if (folder.GetFolderName() == name)
		return true;
	return false;
}

bool FolderUser::CheckIfTheUsernameExists(std::string filename)
{
	for (auto& index : m_itemUser)
	{
		if (index.GetFilename() == filename)
			return true;
	}
	return false;
}
bool FolderUser::FindInFolder(std::string file)
{
	for (auto& fil : m_fileName)
	{
		if (fil == file)
			return true;
	}
	return false;
}

std::string FolderUser::SplitFilename(const std::string str)
{
	std::size_t found = str.find_last_of("/\\");
	return str.substr(found + 1);
}

void FolderUser::DisplayUserFiles()
{
	for (auto index : m_fileName)
		std::cout << index << std::endl;
}

void FolderUser::SetItemUser()
{
	std::string path1 = "../../Client/UserFolder";
	std::wstring pathOrigin = fs::current_path();
	path1 += "/";
	path1 += m_FolderName;
	fs::current_path(path1);

	for (auto const& dir_entry : fs::directory_iterator{ fs::current_path() })
	{
		std::string aux = fs::absolute(dir_entry.path()).string();
		aux = SplitFilename(aux);
		m_fileName.push_back(aux);
	}

	fs::current_path(pathOrigin);

	DisplayUserFiles();

}
void FolderUser::itemsList(std::string name)
{
	std::string path1 = "../../Client/UserFolder";
	std::wstring pathOrigin = fs::current_path();
	path1 += "/";
	path1 += m_FolderName;
	fs::current_path(path1);
	std::ofstream out("ItemsList.txt");
	time_t now = time(0);
	char* dt = ctime(&now);
	out << name << " " << dt << std::endl;
	fs::current_path(pathOrigin);
}
std::uintmax_t FolderUser::GetFolderSize()
{
	uintmax_t size = 0;
	for (auto const& dir_entry : fs::directory_iterator{ m_path })
	{
		size += file_size(dir_entry);
	}
	return size;

}
fs::path FolderUser::GetPath()
{
	return m_path;
}

std::string FolderUser::GetPath2()
{
	return m_path2;
}

void FolderUser::SetPath(fs::path& path)
{
	m_path = path;
}



//uint32_t FolderUser::GetLastTimeWrite()
//{
//
//	using namespace std::chrono_literals;
//	auto print_last_write_time = [](std::filesystem::file_time_type const& ftime) {
//		std::time_t cftime = std::chrono::system_clock::to_time_t(ftime);
//		std::cout << "File write time is " << std::asctime(std::localtime(&cftime));
//	};
//
//	auto ftime = std::filesystem::last_write_time(p);
//	print_last_write_time(ftime);
//
//}
