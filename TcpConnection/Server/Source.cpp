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

	// receive path for the download
	std::array<char, 512> receiveBuffer;
	int received;
	client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	std::cout << "Received: ";
	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	std::cout <<" the path for the download file " << std::endl;
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
	stream << "The download will begin shortly !\n";
	std::string message = stream.str();
	client.Send(message.c_str(), message.size());
	
	//path for where to be save
	std::array<char, 512> receiveBuffer2;
	int received2;
	client.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
	std::cout << "Received: ";
	std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
	std::cout <<" the path where the file will be saved " << std::endl;
	std::string filenameToSave;

	for (int index = 0; index < received2; index++)
	{
		filenameToSave += receiveBuffer2[index];
	}

	fs::path whereToBeSaved = filenameToSave;
	const auto copyOptions = fs::copy_options::update_existing
		| fs::copy_options::recursive
		;
	fs::copy(fileToDownload, whereToBeSaved, copyOptions);
	std::stringstream stream2;
	stream2 << "Download complete !" ;
	std::string message2 = stream2.str();
	client.Send(message2.c_str(), message2.size());

	return 0;
}