#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define Port 54000

SOCKET Socket, Sub;
WSADATA Winsock;
sockaddr_in Addr;
sockaddr_in IncomingAddress;
int AddressLen = sizeof(IncomingAddress);

int main()
{
	WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
	{
		std::cerr << "[ERROR] Bad version !";
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(Port);
	bind(Socket, (sockaddr*)&Addr, sizeof(Addr));

	if (listen(Socket, 1) == SOCKET_ERROR)
	{
		std::cerr<<"[ERROR] Listening error\n";
	}
	else
	{
		std::cout<<"[INFO] Listening ok\n";
	}

	if (Sub = accept(Socket, (sockaddr*)&IncomingAddress, &AddressLen))
	{
		char* ClientIP = inet_ntoa(IncomingAddress.sin_addr);
		int ClientPort = ntohs(IncomingAddress.sin_port);
		std::cout << "[INFO] Client conncted!\n";
		std::cout<<"IP: "<< ClientIP<< ClientPort<<"\n";

		std::cout<<"[INFO] Sending file ... \n";

		FILE* File;
		char* Buffer;
		unsigned long Size;

		File = fopen("C:/Users/andre/Desktop/salut.txt", "rb");
		if (!File)
		{
			std::cerr<<"[ERROR] Error while readaing the file\n";
			getchar();
			return 0;
		}

		fseek(File, 0, SEEK_END);
		Size = ftell(File);
		fseek(File, 0, SEEK_SET);

		Buffer = new char[Size];

		fread(Buffer, Size, 1, File);
		char cSize[MAX_PATH];
		sprintf(cSize, "%i", Size);

		fclose(File);
		send(Sub, cSize, MAX_PATH, 0); // File size

		int len = Size;
		char* data = Buffer;


		int Offset = 0;
		while (Size > Offset)
		{
			int Amount = recv(Socket, Buffer + Offset, Size - Offset, 0);

			if (Amount <= 0)
			{
				break;
			}
			else
			{
				Offset += Amount;
				std::cout<<"2\n";
			}
		}


		free(Buffer);
		closesocket(Sub);
		closesocket(Socket);
		WSACleanup();
	}

	getchar();
	return 0;
}