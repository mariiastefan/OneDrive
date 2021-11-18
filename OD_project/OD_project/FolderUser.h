#pragma once
#include <string>
#include<vector>
#include <filesystem>
#include"User.h"
#include "file.h"

class FolderUser {
private:
	std::vector<File>itemUser;
	std::vector<std::string>FilesName;
	std::string m_FolderName;
	int m_nrItems;
public:
	FolderUser();
	FolderUser(std::string userName);
	void DeleteFolder(std::string userName);
	std::string GetFolderName()const;
	int GetNrItems()const;
	void SetFolderName(const std::string& foldername2);
	void SetNrItems();
	void AddFile(std::string userName);
	bool verify_FolderName(FolderUser folder, std::string name);
	bool verify_existItem(std::string filename);
};