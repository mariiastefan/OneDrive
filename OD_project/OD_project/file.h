#pragma once

#include <string>
#include <filesystem>

class File {
private:
	std::string m_nume_fisier;
	std::string m_data_fisier;
	std::string m_data_actualizare;
public:
	File(const std::string& nume, const std::string& data);
	void ActualizareData(std::string nume_nou, std::string data);
};