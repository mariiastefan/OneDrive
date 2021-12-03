#include "file.h"

std::string File::GetFilename()
{
	return m_filename;
}

std::string File::GetFile_date()
{
	return m_file_date;
}

std::string File::GetUpdate_data()
{
	return m_updated_date;
}

void File::SetUpdate_date(std::string update_data)
{
	m_updated_date = update_data;
}

int File::GetFile_size()
{
	return m_file_size;
}

void File::SetFile_size(int size)
{
	m_file_size = size;
}

File::File(const std::string& name, const std::string& date) :
	m_filename{ name }, m_file_date{ date }, m_updated_date{ date }
{};

void File::ActualizareData(std::string new_name, std::string date)
{
	if (m_filename == new_name)
		m_updated_date = date;
}

int File::GetSize()
{
	return m_file_size;
}
