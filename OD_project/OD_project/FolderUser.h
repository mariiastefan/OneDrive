#pragma once
#include <string>
#include <filesystem>
#include"User.h"

class FolderUser {
private:
	std::string m_FolderName;
	int m_nrItems;
public:
	FolderUser(std::string userName);
};