#ifdef SERVER_EXPORTS
#define SERVER_API __declspec(dllexport)
#else 
#define SERVER_API __declspec(dllimport)

#endif //CLIENT_EXPORTS 


#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

class SERVER_API Server {
private:
	std::string ipAddress;
public:
	Server(std::string ipAddress)
	{
		this->ipAddress = ipAddress;
	}
	void Start() {
		// Initialze winsock
		WSADATA wsData;
		WORD ver = MAKEWORD(2, 2);

		int wsOk = WSAStartup(ver, &wsData);
		if (wsOk != 0)
		{
			std::cerr << "Can't Initialize winsock! Quitting" << std::endl;
			return;
		}

		// Create a socket
		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			std::cerr << "Can't create a socket! Quitting" << std::endl;
			return;
		}

		// Bind the ip address and port to a socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(54000);
		hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

		bind(listening, (sockaddr*)&hint, sizeof(hint));

		// Tell Winsock the socket is for listening 
		listen(listening, SOMAXCONN);

		// Create the master file descriptor set and zero it
		fd_set master;
		FD_ZERO(&master);

		// Add our first socket that we're interested in interacting with; the listening socket!
		// It's important that this socket is added for our server or else we won't 'hear' incoming
		// connections 
		FD_SET(listening, &master);

		// this will be changed by the \quit command (see below, bonus not in video!)
		bool running = true;

		while (running)
		{
			fd_set copy = master;

			// See who's talking to us
			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

			// Loop through all the current connections / potential connect
			for (int i = 0; i < socketCount; i++)
			{
				// Makes things easy for us doing this assignment
				SOCKET sock = copy.fd_array[i];

				// Is it an inbound communication?
				if (sock == listening)
				{
					// Accept a new connection
					SOCKET client = accept(listening, nullptr, nullptr);

					// Add the new connection to the list of connected clients
					FD_SET(client, &master);

					// Send a welcome message to the connected client
					std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
					send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

				}
				else // It's an inbound message
				{
					char buf[4096];
					ZeroMemory(buf, 4096);

					// Receive message
					int bytesIn = recv(sock, buf, 4096, 0);
					if (bytesIn <= 0)
					{
						// Drop the client
						std::cout << "Client disconnected because no message was sent !";
						closesocket(sock);
						FD_CLR(sock, &master);
					}
					else
					{

						// Send message to other clients, and definiately NOT the listening socket

						for (int i = 0; i < master.fd_count; i++)
						{
							SOCKET outSock = master.fd_array[i];
							/*if (outSock != listening && outSock != sock)
							{*/
							std::ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							std::string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							//}
						}
						//while (true)
						//{
						//	ZeroMemory(buf, 4096);

						//	// Wait for client to send data
						//	int bytesReceived = recv(sock, buf, 4096, 0);
						//	if (bytesReceived == SOCKET_ERROR)
						//	{
						//		cerr << "Error in recv(). Quitting" << endl;
						//		break;
						//	}

						//	if (bytesReceived == 0)
						//	{
						//		cout << "Client disconnected " << endl;
						//		break;
						//	}

						//	cout << string(buf, 0, bytesReceived) << endl;

						//	// Echo message back to client
						//	send(sock, buf, bytesReceived + 1, 0);

						//}
					}
				}
			}
			//else {
			//	while (true)
			//		{
			//			ZeroMemory(buf, 4096);

			//		Wait for client to send data
			//		int bytesReceived = recv(sock, buf, 4096, 0);
			//		//	if (bytesReceived == SOCKET_ERROR)
			//		//	{
			//		//		cerr << "Error in recv(). Quitting" << endl;
			//		//		break;
			//		//	}

			//		//	if (bytesReceived == 0)
			//		//	{
			//		//		cout << "Client disconnected " << endl;
			//		//		break;
			//		//	}

			//		//	cout << string(buf, 0, bytesReceived) << endl;

			//		//	// Echo message back to client
			//		//	send(sock, buf, bytesReceived + 1, 0);

			//		//}
		}

		// Remove the listening socket from the master file descriptor set and close it
		// to prevent anyone else trying to connect.
		FD_CLR(listening, &master);
		closesocket(listening);

		// Message to let users know what's happening.
		std::string msg = "Server is shutting down. Goodbye\r\n";

		while (master.fd_count > 0)
		{
			// Get the socket number
			SOCKET sock = master.fd_array[0];

			// Send the goodbye message
			send(sock, msg.c_str(), msg.size() + 1, 0);

			// Remove it from the master file list and close the socket
			FD_CLR(sock, &master);
			closesocket(sock);
		}

		// Cleanup winsock
		WSACleanup();

		system("pause");
	}

};