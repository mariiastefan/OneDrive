#include "Logger.h"

LOGGER_API std::ostream& log(std::ostream& out, int number)
{
	out << number;
	return out;
}