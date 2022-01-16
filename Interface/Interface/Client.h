#pragma once
#include <iostream>
#include <array>
#include <filesystem>
#include "Network.h"
#include <Windows.h>
#include "Logger.h"
#pragma comment(lib, "urlmon.lib")

namespace fs = std::filesystem;


class Client {

private:
	std::string m_userName;
	TcpSocket m_socket;
public:

	Client()
	{
		m_userName = "";
	}

	Client(const std::string & username)
	{
		m_userName = username;
	}


	bool verifyIfFileExists(const fs::path& path)
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

	void connectToServer(const std::string & path)
	{
		log("[CLIENT] Starting client ...");
		log("[CLIENT] Connecting to server ... ");
		m_socket.Connect("127.0.0.1", 8080);
		bool result = m_socket.Send(path.c_str(), path.size());
		if (result)
		{
			log("Sent succeded ! Folder path");
		}
		else {
			log("[CLIENT] Couldn't send the data to the server !");
			return;
		}
	}

	int downloadFromServer(const std::string& filename, const std::string& whereToSave)
	{
		// Validate the parameters

		TcpSocket socket;
		socket.Connect("127.0.0.1", 8080);

		std::array<char, 512> receiveBuffer2;
		int received2;
		socket.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
		std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
		std::cout << std::endl;


		std::array<char, 512> receiveBuffer3;
		int received3;
		socket.Receive(receiveBuffer3.data(), receiveBuffer3.size(), received3);
		std::copy(receiveBuffer3.begin(), receiveBuffer3.begin() + received3, std::ostream_iterator<char>(std::cout, ""));
		std::cout << std::endl;


		bool result = socket.Send(filename.c_str(), filename.size());
		if (result)
		{
			std::array<char, 512> receiveBuffer;
			int received;
			socket.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
			std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
			std::cout << std::endl;
		}
		else {
			log("[CLIENT] Couldn't send the data to the server !");
			return 1;
		}

		bool result2 = socket.Send(whereToSave.c_str(), whereToSave.size());
		if (result2)
		{
			std::array<char, 512> receiveBuffer2;
			int received2;
			socket.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
			std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
			std::cout << std::endl;
		}
		else {
			log("[CLIENT]Couldn't send the data to the server !");
			return 1;
		}
		return 0;
	}

	//int uploadToServer(int argc, char* argv[])
	//{
	//	// Validate the parameters
	//	if (argc != 2) {
	//		std::cerr << "usage: " << argv[0] << " server-name" << std::endl;
	//		return 1;
	//	}

	//	log("[CLIENT]	Starting client...");

	//	TcpSocket socket;
	//	log("[CLIENT] Connecting to server at: ");
	//	socket.Connect("127.0.0.1", 8080);

	//	std::array<char, 512> receiveBuffer2;
	//	int received2;
	//	socket.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
	//	std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
	//	std::cout << std::endl;

	//	fs::path filepath;
	//	std::cin >> filepath;


	//	if (verifyIfFileExists(filepath) == 0)
	//	{
	//		log("[CLIENT] Couldn't find file !");
	//		socket.Send("exit", 4);
	//		return 1;
	//	}

	//	std::string filePathString{ filepath.u8string() };
	//	bool result = socket.Send(filePathString.c_str(), filePathString.size());
	//	if (result)
	//	{
	//		std::array<char, 512> receiveBuffer;
	//		int received;
	//		socket.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	//		std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	//		std::cout << std::endl;
	//	}
	//	else {
	//		log("[CLIENT] Couldn't send the data to the server !");
	//		return 1;
	//	}


	
	std::string GetUsername()
	{
		return m_userName;
	}
};