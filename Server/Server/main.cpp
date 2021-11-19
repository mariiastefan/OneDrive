#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

void main()
{
	std::string ipAddress = "127.0.0.1"; // adresa ip
	int port = 54000; // port

	//Initialize winsock
	WSADATA wsData; // wsadata este o structura care contine informatii despre implementarea socket-urilor
	WORD ver = MAKEWORD(2, 2); // aici se creeaza o variabila de tip WORD care se refera la versiunea winsock

	int wsOk = WSAStartup(ver, &wsData); //wsastartup initializeaza folosirea winsock dll cu un porces si returneaza un pointer catre structura de date wsadata care primeste detalii despre implementarea socket-urilor
	if (wsOk != 0)
	{
		std::cerr << "Cant initialize winsock ! Quitting" << std::endl;
		return;
	}

	//create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // functia socket creeaza un socket care este "legat de catre un serviciu de transport", AF_INET = address family (in headerul winsock2.h sunt 2 valori suportate iar AF_INET este una dintre ele). SOCK_STREAM = tipul de socket. A socket type that provides sequenced, reliable, two-way, connection-based byte streams with an OOB data transmission mechanism. This socket type uses the Transmission Control Protocol (TCP) for the Internet address family (AF_INET or AF_INET6). 0 = protocol to be used adica nu se foloseste niciun protocol
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup(); // inchide procesul de folosire a winsock 2 dll
		return;
	}

	//bind socket to an ip address and port to a socket
	sockaddr_in hint; // sockaddr_in este o structura care specifica adresa de transport si portul pentru AF_INET
	hint.sin_family = AF_INET; // adresa familie pentru adresa de transport
	hint.sin_port = htons(port); //functia htons transforma u_short in TCP/IP network byte order
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //sin_addr este o struct de tip IN_ADDR = A union that contains the following different representations of the IPv4 transport address:

	bind(sock, (sockaddr*)&hint, sizeof(hint)); // asociaza o adresa locala cu un socket , sizeof(hint) =lungimea in biti a valorii care e pointata de hint

	//tell winsock the socket is for listening 
	listen(sock, SOMAXCONN); //indica o pregatire a socketului pentru a accepta conectari ale clientilor somaxconn= valoarea maxima de conexiuni in asteptare pentru orice listening socket

	//wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(sock, (sockaddr*)&client, &clientSize); // accepta o noua conexiune pe un socket  adica accepata sock pe adresa lui client
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "INVALID SOCKET ! Quitting !";
		return;
	}

	char host[NI_MAXHOST]; //clients remote name ni_maxhost = valoarea maxima a unui domain
	char service[NI_MAXSERV]; // service (i.e. port) the client is connect on, ni_maxserv = valoarea maxima a numelui de serv

	ZeroMemory(host, NI_MAXHOST); // umple un block de memorie cu 0 , primul param = pointer catre adresa de start a primului block de memorie, al doilea param = dimensiunea pe care o umple cu 0
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) // transforma de la o adresa la un ansi host name si de la un port number la ansi service name
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST); // converteste o adresa ipv4(toate adresele de mai sus sunt IPv4) sau ipv6 intr un string in internet standard formnt
		std::cout<<host<<" connected on port "<<ntohs(client.sin_port)<<std::endl;//convert ushort from tcp/ip in host byte order
	}
	// close listening socket
	closesocket(sock); // inchide socketul sock

	//while loop : accept and echo message back to client
	char buf[4096];

	while (true) {
		ZeroMemory(buf, 4096);

		//Wait for client to send data
		int bytesRecieved = recv(clientSocket, buf, 4096, 0); // recv primeste informatii de la un socket conectat
		if (bytesRecieved == SOCKET_ERROR)
		{
			std::cerr << "Error in recv() !  Quitting !";
			break;
		}

		if (bytesRecieved == 0)
		{
			std::cout << "Client Disconnected !";
			break;
		}
		//echo message back to client
		send(clientSocket, buf, bytesRecieved + 1, 0); // trimite info catre un socket conectat

	}
	//close socket
	closesocket(clientSocket);

	//CleanUp winsock
	WSACleanup();// inchide procesul de folosire a winsock 2 dll

}
