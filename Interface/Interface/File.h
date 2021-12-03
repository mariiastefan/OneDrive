#pragma once
#include <string>
#include <filesystem>

class File {
private:
	std::string m_filename;
	std::string m_file_date;
	std::string m_updated_date;
	int m_file_size;
public:
	std::string GetFilename();
	std::string GetFile_date();
	std::string GetUpdate_data();
	int GetFile_size();
	void SetUpdate_date(std::string update_data);
	void SetFile_size(int size);
	File(const std::string& nume, const std::string& data);
	void ActualizareData(std::string new_name, std::string date);
	int GetSize();
};