#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

//#include <iostream>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

SOCKET Socket;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(Addr);

int main()
{
    WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

    if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
    {
        WSACleanup();
        return 0;
    }

    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    ZeroMemory(&Addr, sizeof(Addr));    // clear the struct
    Addr.sin_family = AF_INET;    // set the address family
    Addr.sin_addr.s_addr = inet_addr("192.168.221.94");
    Addr.sin_port = htons(54000);    // set the port

    if (connect(Socket, (sockaddr*)&Addr, sizeof(Addr)) < 0)
    {
        printf("Connection failed !\n");
        getchar();
        return 0;
    }

    printf("Connection successful !\n");

    printf("Receiving file .. \n");



    int Size;
    char* Filesize = new char[1024];

    if (recv(Socket, Filesize, 1024, 0)) // File size
    {
        Size = atoi((const char*)Filesize);
        printf("File size: %d\n", Size);
    }

    char* Buffer = new char[Size];

    int len = Size;
    char *data = Buffer;
    int Offset = 0;
    while (Size > Offset)
    {
        int Amount = send(Socket, Buffer + Offset, Size - Offset, 0);

        if (Amount <= 0)
        {

            break;
        }
        else
        {
            Offset += Amount;
            printf("2\n");
        }
    }

    FILE* File;
    File = fopen("C:/Users/andre/Desktop/salut.txt", "wb");
    fwrite(Buffer, 1, Size, File);
    fclose(File);

    getchar();
    closesocket(Socket);
    WSACleanup();
    return 0;
}