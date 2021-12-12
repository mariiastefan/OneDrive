#include "FolderUser.h"
#include <filesystem>
#include <cstdio>
#include<iostream>


FolderUser::FolderUser()
{
	m_nrItems = 0;
}

FolderUser::FolderUser(std::string userName)
{
	m_FolderName = userName;
	m_nrItems = 0;
	namespace fs1 = std::filesystem;
	std::wstring pathOrigin = fs1::current_path();
	std::string path1 = "../../Client/UserFolder";
	fs1::current_path(path1);
	fs1::create_directory(userName);
	fs1::current_path(pathOrigin);
	std::string path2 = "../../Server/UserFolder";
	fs1::current_path(path2);
	fs1::create_directory(userName);
	fs1::current_path(pathOrigin);
}

void FolderUser::DeleteFolder(std::string userName)
{
	namespace fs1 = std::filesystem;
	std::string pathClient = "../../Client/UserFolder";
	std::string pathServer = "../../Server/UserFolder";
	std::wstring pathOrigin = fs1::current_path();
	fs1::current_path(pathClient);
	std::uintmax_t n1 = fs1::remove_all(userName);
	fs1::current_path(pathOrigin);
	fs1::current_path(pathServer);
	std::uintmax_t n2 = fs1::remove_all(userName);
	fs1::current_path(pathOrigin);
}
void FolderUser::DeleteFile(std::string username, std::string file)
{
	namespace fs1 = std::filesystem;
	std::string pathClient = "../../Client/UserFolder";
	std::string pathServer = "../../Server/UserFolder";
	std::string path = "../../UserFolder";
	path += '/';
	path += username;
	path += '/';
	path += file;
	std::uintmax_t n = fs1::remove(path);
	pathClient += '/';
	pathClient += username;
	pathClient += '/';
	pathClient += file;
	std::uintmax_t n1 = fs1::remove(pathClient);
	pathServer += '/';
	pathServer += username;
	pathServer += '/';
	pathServer += file;
	std::uintmax_t n2= fs1::remove(pathServer);

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
	namespace fs1 = std::filesystem;
	std::string pathClient = "../../Client/UserFolder";
	std::string pathServer = "../../Server/UserFolder";
	std::wstring pathOrigin = fs1::current_path();

	pathClient += "/";
	pathClient += m_FolderName;
	fs1::current_path(pathClient);

	int m_nrItems_local = 0;
	for (auto const& dir_entry : std::filesystem::directory_iterator{ fs1::current_path() })
		m_nrItems_local++;
	fs1::current_path(pathOrigin);

	pathServer += "/";
	pathServer += m_FolderName;
	fs1::current_path(pathServer);

	int m_nrItems_server = 0;
	for (auto const& dir_entry : std::filesystem::directory_iterator{ fs1::current_path() })
		m_nrItems_server++;
	fs1::current_path(pathOrigin);

	m_nrItems = m_nrItems_server;

	if (m_nrItems_server == m_nrItems_local) std::cout << std::endl << "Fisiere sincronizate" << std::endl;
	else std::cout << std::endl << "Fisierele nu sunt sincronizate cu serverul"<<std::endl;
}

void FolderUser::AddFile(std::string userName)
{
	std::string old_place;
	std::cout << "introduceti calea catre fisier: ";
	std::cin >> old_place;

	std::string ItemName;
	do {
		std::cout << "cititi numele fisierului: ";
		std::cin >> ItemName;
	} while (verify_existItem(ItemName) == true);
	old_place += "/";
	old_place += ItemName;
	std::string old_place2= old_place;

	namespace fs1 = std::filesystem;
	std::string pathClient = "../../Client/UserFolder";
	std::string pathServer = "../../Server/UserFolder";
	std::wstring pathOrigin = fs1::current_path();

	pathClient += "/";
	pathClient += userName;
	fs1::current_path(pathClient);
	pathClient += "/";
	pathClient += ItemName;
	fs1::copy((old_place), fs1::current_path());
	fs1::current_path(pathOrigin);

	pathServer += "/";
	pathServer += userName;
	fs1::current_path(pathServer);
	pathServer += "/";
	pathServer += ItemName;
	fs1::copy((old_place2), fs1::current_path());

	fs1::current_path(pathOrigin);
	m_nrItems++;
	File aux(ItemName, "data");
	m_itemUser.push_back(aux);
}

bool FolderUser::verify_FolderName(FolderUser folder, std::string name)
{
	if (folder.GetFolderName() == name)
		return true;
	return false;
}

bool FolderUser::verify_existItem(std::string filename)
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
	namespace fs1 = std::filesystem;
	std::string path1 = "../../UserFolder";
	std::wstring pathOrigin = fs1::current_path();
	path1 += "/";
	path1 += m_FolderName;
	fs1::current_path(path1);

	for (auto const& dir_entry : fs1::directory_iterator{ fs1::current_path() })
	{
		std::string aux = fs1::absolute(dir_entry.path()).string();
		aux = SplitFilename(aux);
		m_fileName.push_back(aux);
	}

	fs1::current_path(pathOrigin);

	DisplayUserFiles();

}
std::uintmax_t FolderUser::GetSizeOfASpecificFolder()
{
	std::string name;
	std::cout << "Scrieti numele username ului pt care doriti sa aflati dimensiunea fisierului: ";
	std::cin >> name;
	namespace fs1 = std::filesystem;
	std::wstring pathOrigin = fs1::current_path();
	std::string path = "../../UserFolder";
	path += "/";
	path += name;
	uintmax_t size = 0;
	for (auto const& dir_entry : fs1::directory_iterator{ path })
	{
		size += file_size(dir_entry);
	}
	return size;

}