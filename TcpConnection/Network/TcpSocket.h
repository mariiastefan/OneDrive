#pragma once
#include <cstdint>
#include <string>
#include <mutex>
#include <basetsd.h>
#include <WS2tcpip.h>


class TcpSocket
{
private:
	using SocketHandle = UINT_PTR;
	static const SocketHandle InvalidSocketHandle;

public:
	TcpSocket();
	~TcpSocket();

	bool Listen(uint16_t remotePort);
	TcpSocket Accept();

	bool Connect(const std::string& remoteAddress, uint16_t remotePort);
	bool Send(const void* data, int size);
	bool Receive(void* data, int size, int& recieved);

private:
	TcpSocket(SocketHandle socketHandle);

private:
	SocketHandle m_socket;
};

