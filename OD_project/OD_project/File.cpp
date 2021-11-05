#include "file.h"
File::File(const std::string& nume, const std::string& data) :
	m_nume_fisier{ nume }, m_data_fisier{ data }, m_data_actualizare{ data }
{};

void File::ActualizareData(std::string nume_nou, std::string data)
{
	if (m_nume_fisier == nume_nou)
		m_data_actualizare = data;
}