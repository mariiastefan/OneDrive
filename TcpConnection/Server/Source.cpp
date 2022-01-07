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
	listener.Listen(8080);
	
	std::cout << "Waiting for client to connect..." << std::endl;
	TcpSocket client = listener.Accept();

	// receive
	std::array<char, 512> receiveBuffer;
	int received;
	client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	std::cout << "Received: ";
	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	std::cout << std::endl;
	std::string filename;
	

	for (int index = 0; index< received; index++)
	{
		filename += receiveBuffer[index];
	}

	fs::path fileToDownload = filename;
	if (ShowFiles(fileToDownload) == 0)
	{
		std::cerr << "Couldn't find the file !" << std::endl;
		std::string message = "Couldn't find the file !";
		client.Send(message.c_str(), message.size());
		return 1;
	}

	// send
	std::stringstream stream;
	stream << "Thank you, I received " << received << " bytes from you and the size of the file you sent is : "<< fs::file_size(fileToDownload) << " bytes \n";
	std::string message = stream.str();
	client.Send(message.c_str(), message.size());

	std::cout << "Sending: " << message.size() << " bytes" << std::endl;
	return 0;
}