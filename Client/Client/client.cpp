#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "Client.h"
#pragma comment(lib, "ws2_32.lib")


int main()
{
	std::string ipAddress = "192.168.230.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	Client client(ipAddress, port);
	client.Start();
}
