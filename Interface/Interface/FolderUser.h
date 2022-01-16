#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "User.h"
#include <QString>
#include "file.h"

namespace fs = std::filesystem;

class FolderUser {
private:
	std::vector<File>m_itemUser;
	std::vector<std::string>m_fileName;
	fs::path m_path;
	std::string m_serverPath;
	std::string m_pathAsString;
	fs::file_time_type m_date;
	std::string m_foldername;
	int m_nrItems;
public:
	FolderUser();
	FolderUser(std::string userName);
	FolderUser(std::string foldername, fs::path path, fs::file_time_type date, std::vector<std::string>filename);

	void DeleteFolder(std::string userName);
	void DeleteUsernameFolder();
	void DeleteFile(std::string username, std::string file);
	void DeleteFile();

	void SetFolderName(const std::string& foldername);
	void SetNrItems();
	void SetItemUser();
	void SetPath(fs::path& path);
	std::string GetFolderName()const;


	void AddFile(const std::string &fileName);
	bool VerifyFolderName(FolderUser folder, std::string name);
	bool CheckIfTheUsernameExists(const std::string &filename);
	bool FindInFolder(const std::string &file);
	std::string SplitFilename(const std::string &str);
	void DisplayUserFiles();
	void ItemsList(const std::string &name);

	uintmax_t GetFolderSize();
	fs::path GetPath();
	std::string GetPathAsString();
	std::string GetServerPath();
	int GetNrItems()const;

};