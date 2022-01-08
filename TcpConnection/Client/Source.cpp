#include <iostream>
#include <array>
#include <experimental/filesystem>
#include "../Network/TcpSocket.h"
#include <Windows.h>
#pragma comment(lib, "urlmon.lib")

namespace fs = std::experimental::filesystem;

bool ShowFiles(fs::path path)
{
	for (auto& p : fs::recursive_directory_iterator(path.parent_path()))
	{
		/*std::cout << p.path().filename() << '\n';
		std::cout << path.parent_path() << "\n";
		std::cout << p.path().parent_path() << "\n";*/
		if (p.path()== path)
		{
			return 1;
		}
	}
	return 0;
}


int main(int argc, char* argv[]) 
{
	// Validate the parameters
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " server-name" << std::endl;
		return 1;
	}

	std::cout << "Starting client..." << std::endl;

	TcpSocket socket;
	std::cout << "Connecting to server at: " << argv[1] << std::endl;
	socket.Connect("127.0.0.1", 8080);

	fs::path defaultPath = "C:/Users/Andrei/Desktop/salut";

	fs::path filename;
	std::cout << "Enter the name of the folder you want to download : ";
	std::cin >> filename;
	fs::path fileToDownload = defaultPath;
	fileToDownload += "\\";
	fileToDownload += filename;

	fs::path whereToSave;
	std::cout<<"Enter the path where you want to save the file :"<<  std::endl;
	std::cin >> whereToSave;

	std::string pathString{ fileToDownload.u8string() };
	std::string saveString{ whereToSave.u8string() };

	bool result = socket.Send(pathString.c_str(), pathString.size());
	if (result)
	{
		std::array<char, 512> receiveBuffer;
		int received;
		socket.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
		std::cout << "Received: ";
		std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
		std::cout << std::endl;
	}
	else {
		std::cerr << "Couldn't send the data to the server !";
		return 1;
	}

	bool result2 = socket.Send(saveString.c_str(), saveString.size());
	if (result2)
	{
		std::array<char, 512> receiveBuffer2;
		int received2;
		socket.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
		std::cout << "Received: ";
		std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
		std::cout << std::endl;
	}
	else {
		std::cerr << "Couldn't send the data to the server !";
		return 1;
	}
	return 0;
}