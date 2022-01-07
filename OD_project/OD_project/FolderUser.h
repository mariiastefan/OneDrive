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
	fs::file_time_type m_date;
	std::string m_FolderName;
	int m_nrItems;
public:
	FolderUser();
	FolderUser(std::string userName);

	void DeleteFolder(std::string userName);
	void DeleteUsernameFolder();
	void DeleteFile(std::string username,std::string file);

	void SetFolderName(const std::string& foldername);
	void SetNrItems();
	void SetItemUser();
	fs::path SetPath(fs::path& path);
	std::string GetFolderName()const;
	int GetNrItems()const;

	void AddFile(std::string userName);
	void AddFile();
	bool VerifyFolderName(FolderUser folder, std::string name);
	bool CheckIfTheUsernameExists(std::string filename);
	bool FindInFolder(std::string file);
	std::string SplitFilename(const std::string str);
	void DisplayUserFiles();
	void itemsList(std::string name);
	uintmax_t GetFolderSize();
	uint32_t GetLastTimeWrite();
	fs::path GetPath();

};