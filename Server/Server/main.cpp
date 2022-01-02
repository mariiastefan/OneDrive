#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

SOCKET Socket;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(Addr);

int main()
{
    std::cout << "salut\n";
    WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock
    std::cout << "am pornit\n";
    if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
    {
        std::cerr << "[ERROR] Bad version !";
        WSACleanup();
        return 0;
    }
    std::cout << "am verif versiunea\n";

    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::cout << "am creeat socket\n";
    ZeroMemory(&Addr, sizeof(Addr));    // clear the struct
    Addr.sin_family = AF_INET;    // set the address family
    Addr.sin_addr.s_addr = inet_addr("192.168.221.94");
    Addr.sin_port = htons(54000);    // set the port
    std::cout << "am setat porturile\n";
    if (connect(Socket, (sockaddr*)&Addr, sizeof(Addr)) < 0)
    {
        std::cerr<<"[ERROR] Connection failed !\n";
        getchar();
        return 0;
    }

    std::cout<<"[INFO] Connection successful !\n";

    std::cout << "[INFO] Receiving file .. \n";



    int Size;
    char* Filesize = new char[1024];

    if (recv(Socket, Filesize, 1024, 0)) // File size
    {
        Size = atoi((const char*)Filesize);
        std::cout<<"[INFO] File size: \n"<< Size;
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