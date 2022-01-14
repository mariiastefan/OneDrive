#include <iostream>
#include <array>
#include <sstream>
#include <fstream>
#include <experimental/filesystem>
#include <chrono>
#include "../Network/TcpSocket.h"
using namespace std::chrono_literals;

namespace fs = std::experimental::filesystem;

void ShowFiles(const fs::path& path)
{
	auto start = std::chrono::system_clock::now();
	// Some computation here
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::ofstream g("log.txt", std::ios::app);
	auto print_last_write_time = [&g](fs::file_time_type const& ftime) {
		std::time_t cftime = std::chrono::system_clock::to_time_t(ftime);
		g << "was modified last time in " << std::asctime(std::localtime(&cftime));
	};
	g << "[LOG] Started downloading files at " << std::ctime(&end_time);
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		auto ftime = fs::last_write_time(p);
		g << p << " ";
		print_last_write_time(ftime);
		std::cout << "\n";
	}
}

bool verifyIfFileExists(const fs::path &path)
{
	for (auto& p : fs::recursive_directory_iterator(path.parent_path()))
	{
		if (p.path() == path)
		{
			return 1;
		}
	}
	return 0;
}

//download from server
int main()
{
	std::ofstream g;
	std::cout << "[SERVER] Starting server..." << std::endl;

	TcpSocket listener;
	listener.Listen(8080);
	
	std::cout << "[SERVER] Waiting for client to connect..." << std::endl;
	TcpSocket client = listener.Accept();
	std::cout << "[SERVER] Client connected !";
	std::stringstream stream;
	stream << "[SERVER] Connection succesful !\n";
	std::string message = stream.str();
	client.Send(message.c_str(), message.size());
	int op = 0;

	//std::stringstream stream;
	//stream << "[SERVER] The file you want to download !\n";
	//std::string message = stream.str();
	//client.Send(message.c_str(), message.size());

	//std::stringstream stream2;
	//stream2 << "[SERVER] Where do you want to save the file ?\n";
	//std::string message2 = stream2.str();
	//client.Send(message2.c_str(), message2.size());

	//// receive path for the download
	//std::array<char, 512> receiveBuffer;
	//int received;
	//client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	//std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	//std::cout <<" the path for the download file " << std::endl;
	//std::string filename;
	//

	//for (int index = 0; index< received; index++)
	//{
	//	filename += receiveBuffer[index];
	//}

	//fs::path fileToDownload = filename;
	//if (verifyIfFileExists(fileToDownload) == 0)
	//{
	//	std::cerr << "[SERVER] Couldn't find the file !" << std::endl;
	//	std::string message = "[SERVER] Couldn't find the file !";
	//	client.Send(message.c_str(), message.size());
	//	return 1;
	//}
	//else {
	//	ShowFiles(fileToDownload);
	//}

	//// send
	//std::stringstream stream1;
	//stream1 << "[SERVER] The download will begin shortly !\n";
	//std::string message1 = stream1.str();
	//client.Send(message1.c_str(), message1.size());
	//
	////path for where to be save

	//std::array<char, 512> receiveBuffer2;
	//int received2;
	//client.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
	//std::cout << "Received: ";
	//std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
	//std::cout <<" the path where the file will be saved " << std::endl;
	//std::string filenameToSave;

	//for (int index = 0; index < received2; index++)
	//{
	//	filenameToSave += receiveBuffer2[index];
	//}

	//fs::path whereToBeSaved = filenameToSave;
	//const auto copyOptions = fs::copy_options::update_existing
	//	| fs::copy_options::recursive
	//	;
	//fs::copy(fileToDownload, whereToBeSaved, copyOptions);
	//std::stringstream stream3;
	//stream3 << "[SERVER] Download complete !" ;
	//std::string message3 = stream3.str();
	//client.Send(message3.c_str(), message3.size());

	return 0;
}
//upload from client
//int main()
//{
//	std::cout << "[SERVER] Starting server..." << std::endl;
//
//	TcpSocket listener;
//	listener.Listen(8080);
//
//	std::cout << "[SERVER] Waiting for client to connect..." << std::endl;
//	TcpSocket client = listener.Accept();
//
//	fs::path save = "C:/Users/Andrei/Desktop/server_files";
//
//	std::stringstream stream;
//	stream << "[SERVER] Select the file you want to upload !\n";
//	std::string message = stream.str();
//	client.Send(message.c_str(), message.size());
//
//	std::array<char, 512> receiveBuffer;
//	int received;
//	client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
//	std::cout << "[CLIENT] ";
//	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
//	std::cout << " the path for the upload file " << std::endl;
//	std::string filename;
//
//	for (int index = 0; index < received; index++)
//	{
//		filename += receiveBuffer[index];
//	}
//
//	if (filename == "exit")
//	{
//		std::cerr << "[SERVER] Didn't recieve any file !\n";
//		return 1;
//	}
//
//	const auto copyOptions = fs::copy_options::update_existing
//	| fs::copy_options::recursive
//	;
//	fs::copy(filename, save, copyOptions);
//	std::stringstream stream2;
//	stream2 << "[SERVER] Upload complete !" ;
//	std::string message2 = stream2.str();
//	client.Send(message2.c_str(), message2.size());
//}