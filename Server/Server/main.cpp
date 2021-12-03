#include "server.h"


int main()
{
	std::string ipAddress = "192.168.2.99";
	Server server(ipAddress);
	server.Start();
}