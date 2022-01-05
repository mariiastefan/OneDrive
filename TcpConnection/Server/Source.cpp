#include <iostream>
#include <array>
#include <sstream>

#include "../Network/TcpSocket.h"

int main()
{
	std::cout << "Starting server" << std::endl;

	TcpSocket listener;
	listener.Listen(54000);
	
	std::cout << "Waiting for client to connect" << std::endl;
	TcpSocket client = listener.Accept();

	// receive
	std::array<char, 512> receiveBuffer;
	int revieved;
	client.Receive(receiveBuffer.data(), receiveBuffer.size(), revieved);
	
	std::cout << "Received: ";
	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + revieved, std::ostream_iterator<char>(std::cout, ""));
	std::cout << std::endl;

	// send
	std::stringstream stream;
	stream << "Thank you, I received " << revieved << " bytes from you";
	std::string message = stream.str();
	client.Send(message.c_str(), message.size());

	std::cout << "Sending: " << message.size() << " bytes" << std::endl;
	std::cout << "Closing server. Bye! :)" << std::endl;

	return 0;
}