#include <iostream>
#include <array>
#include <sstream>
#include <experimental/filesystem>
#include "../Network/TcpSocket.h"

namespace fs = std::experimental::filesystem;

bool ShowFiles(fs::path path)
{
	for (auto& p : fs::recursive_directory_iterator(path.parent_path()))
	{
		/*std::cout << p.path().filename() << '\n';
		std::cout << path.parent_path() << "\n";
		std::cout << p.path().parent_path() << "\n";*/
		if (p.path() == path)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	std::cout << "Starting server..." << std::endl;

	TcpSocket listener;
	listener.Listen(54000);
	
	std::cout << "Waiting for client to connect..." << std::endl;
	TcpSocket client = listener.Accept();

	// receive
	std::array<char, 512> receiveBuffer;
	int received;
	client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	std::cout << "Received: ";
	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	std::cout << std::endl;

	fs::path file_to_download = receiveBuffer.data();
	if (ShowFiles(file_to_download) == 0)
	{
		std::cerr << "Couldn't find the file !" << std::endl;
		return 1;
	}

	// send
	std::stringstream stream;
	stream << "Thank you, I received " << received << " bytes from you";
	std::string message = stream.str();
	client.Send(message.c_str(), message.size());

	std::cout << "Sending: " << message.size() << " bytes" << std::endl;
	std::cout << "Closing server. Bye! :)" << std::endl;

	return 0;
}