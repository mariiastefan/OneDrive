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
	File(const std::string& nume, const std::string& data);
	void ActualizareData(std::string new_name, std::string date);
	int GetSize();
};