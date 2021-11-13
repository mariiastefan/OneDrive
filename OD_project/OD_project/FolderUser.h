#pragma once
#include <string>
#include <filesystem>
#include"User.h"

class FolderUser {
private:
	std::string m_FolderName;
	int m_nrItems;
public:
	FolderUser();
	FolderUser(std::string userName);
	void DeleteFolder(std::string userName);
	std::string GetFolderName()const;
	int GetNrItems()const;
	void SetFolderName(const std::string& foldername2);
	
};