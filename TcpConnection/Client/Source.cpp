#include <iostream>
#include <array>
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
	socket.Connect("192.168.2.99", 54000);

	fs::path file_to_download = "C:\\Users\\Andrei\\Desktop\\salut\\salut2343.txt";

	std::cout << "I want to download the file with the path: " << file_to_download << std::endl;
	bool result = socket.Send(file_to_download.filename().c_str(), fs::file_size(file_to_download));
	if (result)
	{
		std::array<char, 512> receiveBuffer;
		int received;
		socket.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
		std::cout << "Received: ";
		std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
		std::cout << std::endl;
	}

	return 0;
}