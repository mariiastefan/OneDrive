#include "file.h"

File::File(const std::string& name, const std::string& date) :
	m_filename{ name }, m_file_date{ date }, m_updated_date{ date }
{};

void File::ActualizareData(std::string new_name, std::string date)
{
	if (m_filename == new_name)
		m_updated_date = date;
}
