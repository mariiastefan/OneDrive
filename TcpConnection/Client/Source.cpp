#include <iostream>
#include <array>
#include <experimental/filesystem>
#include "../Network/TcpSocket.h"
#include <Windows.h>

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

	fs::path fileToDownload = "C:/Users/Andrei/Desktop/salut/salut.txt";	
	fs::path whereToSave = "C:/Users/Andrei/Desktop/save";
	std::cout << "I want to download the file with the path: " << fileToDownload << std::endl;
	std::string pathString{ fileToDownload.u8string() };
	std::string saveString{ whereToSave.u8string() };
	//URLDownloadToFile(NULL, pathString.c_str(), saveString.c_str(), 0, NULL);

	bool result = socket.Send(pathString.c_str(), pathString.size());
	if (result)
	{
		std::array<char, 512> receiveBuffer;
		int received;
		if (fs::file_size(fileToDownload) > receiveBuffer.size())
		{
			std::cerr << "File you are trying to download is to big !";
			return 1;                                                                  
		}
		socket.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
		std::cout << "Received: ";
		std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
		std::cout << std::endl;
	}
	else {
		std::cerr << "Couldn't send the data to the server !";
		return 1;
	}
	return 0;
}