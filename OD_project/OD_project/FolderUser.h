#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "User.h"
#include "file.h"

namespace fs = std::filesystem;

class FolderUser {
private:
	std::vector<File>m_itemUser;
	std::vector<std::string>m_fileName;
	fs::path m_path;
	std::string m_FolderName;
	int m_nrItems;
public:
	FolderUser();
	FolderUser(std::string userName);
	void DeleteFolder(std::string userName);
	void DeleteFile(std::string username,std::string file);
	std::string GetFolderName()const;
	int GetNrItems()const;
	void SetFolderName(const std::string& foldername2);
	void SetNrItems();
	void AddFile(std::string userName);
	bool verify_FolderName(FolderUser folder, std::string name);
	bool verify_existItem(std::string filename);
	bool FindInFolder(std::string file);
	std::string SplitFilename(const std::string str);
	void DisplayUserFiles();
	void SetItemUser();
	uintmax_t GetFolderSize();
	uint32_t GetLastTimeWrite();
	fs::path GetPath();
	//void GetLastWriteTime();
};