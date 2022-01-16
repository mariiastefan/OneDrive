#include <iostream>
#include <array>
#include <sstream>
#include <fstream>
#include <experimental/filesystem>
#include <chrono>
#include "../Network/TcpSocket.h"
#include "Logger.h"
#include <mutex>
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


bool compare_files(const fs::path& filename1, const fs::path& filename2)
{
	std::ifstream file1(filename1, std::ifstream::ate | std::ifstream::binary); //open file at the end
	std::ifstream file2(filename2, std::ifstream::ate | std::ifstream::binary); //open file at the end
	const std::ifstream::pos_type fileSize = file1.tellg();

	if (fileSize != file2.tellg()) {
		return false; //different file size
	}

	file1.seekg(0); //rewind
	file2.seekg(0); //rewind

	std::istreambuf_iterator<char> begin1(file1);
	std::istreambuf_iterator<char> begin2(file2);

	return std::equal(begin1, std::istreambuf_iterator<char>(), begin2); //Second argument is end-of-range iterator
}

bool checkToSeeIfUserIsUpdated(const fs::path a, const fs::path b)
{
	for (auto& p1 : fs::recursive_directory_iterator(a))
	{
		int ok = 0;
		for (auto& p2 : fs::recursive_directory_iterator(b))
		{
			if (ok == 0)
			{
				if (compare_files(p1, p2) == 1)
					ok = 1;
			}
		}
		if (ok == 0)
			return 0;
	}
	return 1;
}

fs::path whichFileIsNotSynced(const fs::path a, const fs::path b)
{
	for (auto& p1 : fs::directory_iterator(a))
	{
		int ok = 0;
		for (auto& p2 : fs::directory_iterator(b))
		{
			if (ok == 0)
			{
				if (compare_files(p1, p2) == 1)
					ok = 1;
			}
		}
		if (ok == 0)
			return p1;
	}
}

int main()
{
	log("[SERVER] Starting server...");
	std::this_thread::sleep_for(2000ms);
	TcpSocket listener;
	listener.Listen(8080);
	
	
	std::atomic_bool clientConnected = false;
	std::string fileToBeSynced;
	fs::path serverFile = "../../TcpConnection/Server/UserFolder";
	
	/*std::thread watchingConnections([&listener, &client, &clientConnected, &running, &fileToBeSynced]() {
		while (running)
		{
			log("[SERVER] Waiting for client to connect...");
			client = listener.Accept();
			clientConnected = true;
			log("[SERVER] Client connected !");

			std::this_thread::sleep_for(500ms);
			running = false;

			std::this_thread::sleep_for(2000ms);
			std::array<char, 512> receiveBuffer;
			int received;
			client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);			
			std::cout << received;
			
			std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
			log("Received the path for what folder needs to be synced should sync !");

			for (int index = 0; index < received; index++)
			{
				fileToBeSynced += receiveBuffer[index];
			}
			log(fileToBeSynced);

			

		}
	});*/
	

	log("[SERVER] Waiting for client to connect...");
	TcpSocket client = listener.Accept();
	
	clientConnected = true;
	log("[SERVER] Client connected !");

	std::this_thread::sleep_for(500ms);

	std::this_thread::sleep_for(2000ms);
	std::array<char, 512> receiveBuffer;
	int received;
	client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);

	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	std::cout << "\n";
	log("Received the path for what folder needs to be synced should sync !");

	for (int index = 0; index < received; index++)
	{
		fileToBeSynced += receiveBuffer[index];
	}
	log(fileToBeSynced);

	fs::path a = fileToBeSynced;
	serverFile += "/";
	serverFile += a.filename();
	/*running = true;
	watchingConnections.join();*/
	std::atomic_bool running = true;
	std::thread syncTask([&clientConnected, &running, &fileToBeSynced, &serverFile, &client]() {
		if (clientConnected)
		{
			while (running)
			{
				if (checkToSeeIfUserIsUpdated(fileToBeSynced, serverFile))
				{
					log("Nothing new in clients file !");
					std::array<char, 512> receiveBuffer;
					int received;
					client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
					if(received > 0)
					{
						std::copy(receiveBuffer.begin(),receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
						std::string fileToBeDownloaded;
						for (int index = 0; index < received; index++)
						{
							fileToBeDownloaded += receiveBuffer[index];
						}
						fs::copy_options copyOptions;
						copyOptions = fs::copy_options::skip_existing
							| fs::copy_options::recursive
							;
						fs::path a = fileToBeDownloaded;
						fs::copy(a, "C:/Users/Andrei/Desktop/OneDrive/proiect/TcpConnection/Client/UserFolder/ana", copyOptions);
					}
				}
				else {
					log("Something new in clients file ! Sending message ...");
					fs::path syncNext = whichFileIsNotSynced(fileToBeSynced, serverFile);
					fs::copy_options copyOptions;
					if (syncNext.extension() == "")
					{
						copyOptions = fs::copy_options::skip_existing
							| fs::copy_options::recursive
							;
					}
					else {
						copyOptions = fs::copy_options::update_existing
							| fs::copy_options::recursive
							;
					}
					log(syncNext);
					
					fs::copy(syncNext, serverFile, copyOptions);
				}
				std::this_thread::sleep_for(5000ms);
			}
		}
		});
	syncTask.join();
	/*std::vector<std::thread> tasks;
	std::thread sync(syncTask);
	tasks.push_back(std::move(sync));*/



	
	
	

	//cand s a conectat un client serverul trebuie sa astepte sa primeasca
	// o comanda de la client cum ar fi download
	// as putea face un thread ca la watchingConnections si sa am un while
	// infinit in care serverul verifica daca primeste ceva de la client
	// la fiecare x secunde
	// dupa ce a primit informatia ca vrea sa downloadeze se va apela downloadTask
	// sau fac un switch si se apeleaza acolo
	// dupa iar se ia de la capat
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// if (clientConnected)
	//{
	//	log("[SERVER] Client is connected !");
	//	std::mutex m_mutexSocket;
	//	std::lock_guard<std::mutex> lockSocket(m_mutexSocket);

	//	std::stringstream stream;
	//	stream << "[SERVER] The file you want to download !\n";
	//	std::string message = stream.str();
	//	client.Send(message.c_str(), message.size());


	//	std::this_thread::sleep_for(2000ms);

	//	std::stringstream stream2;
	//	stream2 << "[SERVER] Where do you want to save the file ?\n";
	//	std::string message2 = stream2.str();
	//	client.Send(message2.c_str(), message2.size());

	//	std::this_thread::sleep_for(2000ms);

	//	// receive path for the download
	//	std::array<char, 512> receiveBuffer;
	//	int received;
	//	client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	//	std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	//	std::cout << " the path for the download file " << std::endl;
	//	std::string filename;

	//	std::this_thread::sleep_for(2000ms);

	//	for (int index = 0; index < received; index++)
	//	{
	//		filename += receiveBuffer[index];
	//	}

	//	fs::path fileToDownload = filename;
	//	if (verifyIfFileExists(fileToDownload) == 0)
	//	{
	//		std::cerr << "[SERVER] Couldn't find the file !" << std::endl;
	//		std::string message = "[SERVER] Couldn't find the file !";
	//		client.Send(message.c_str(), message.size());
	//		return 1;
	//	}
	//	else {
	//		ShowFiles(fileToDownload);
	//	}

	//	// send
	//	std::stringstream stream1;
	//	stream1 << "[SERVER] The download will begin shortly !\n";
	//	std::string message1 = stream1.str();
	//	client.Send(message1.c_str(), message1.size());

	//	std::this_thread::sleep_for(2000ms);

	//	//path for where to be save

	//	std::array<char, 512> receiveBuffer2;
	//	int received2;
	//	client.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
	//	std::cout << "Received: ";
	//	std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
	//	std::cout << " the path where the file will be saved " << std::endl;
	//	std::string filenameToSave;

	//	std::this_thread::sleep_for(2000ms);

	//	for (int index = 0; index < received2; index++)
	//	{
	//		filenameToSave += receiveBuffer2[index];
	//	}

	//	fs::path whereToBeSaved = filenameToSave;
	//	const auto copyOptions = fs::copy_options::update_existing
	//		| fs::copy_options::recursive
	//		;
	//	fs::copy(fileToDownload, whereToBeSaved, copyOptions);
	//	std::stringstream stream3;
	//	stream3 << "[SERVER] Download complete !";
	//	std::string message3 = stream3.str();
	//	client.Send(message3.c_str(), message3.size());

	//	std::this_thread::sleep_for(2000ms);
	//}
	//	else {
	//	log("[SERVER] Client isn't connected !");
	//	}
	//int op = 0;
	//do
	//{
	//	switch (op)
	//	{
	//	case 1:
	//	{
	//		std::stringstream stream;
	//		stream << "[SERVER] The file you want to download !\n";
	//		std::string message = stream.str();
	//		client.Send(message.c_str(), message.size());

	//		std::stringstream stream2;
	//		stream2 << "[SERVER] Where do you want to save the file ?\n";
	//		std::string message2 = stream2.str();
	//		client.Send(message2.c_str(), message2.size());

	//		// receive path for the download
	//		std::array<char, 512> receiveBuffer;
	//		int received;
	//		client.Receive(receiveBuffer.data(), receiveBuffer.size(), received);
	//		std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
	//		std::cout << " the path for the download file " << std::endl;
	//		std::string filename;


	//		for (int index = 0; index < received; index++)
	//		{
	//			filename += receiveBuffer[index];
	//		}

	//		fs::path fileToDownload = filename;
	//		if (verifyIfFileExists(fileToDownload) == 0)
	//		{
	//			std::cerr << "[SERVER] Couldn't find the file !" << std::endl;
	//			std::string message = "[SERVER] Couldn't find the file !";
	//			client.Send(message.c_str(), message.size());
	//			return 1;
	//		}
	//		else {
	//			ShowFiles(fileToDownload);
	//		}

	//		// send
	//		std::stringstream stream1;
	//		stream1 << "[SERVER] The download will begin shortly !\n";
	//		std::string message1 = stream1.str();
	//		client.Send(message1.c_str(), message1.size());

	//		//path for where to be save

	//		std::array<char, 512> receiveBuffer2;
	//		int received2;
	//		client.Receive(receiveBuffer2.data(), receiveBuffer2.size(), received2);
	//		std::cout << "Received: ";
	//		std::copy(receiveBuffer2.begin(), receiveBuffer2.begin() + received2, std::ostream_iterator<char>(std::cout, ""));
	//		std::cout << " the path where the file will be saved " << std::endl;
	//		std::string filenameToSave;

	//		for (int index = 0; index < received2; index++)
	//		{
	//			filenameToSave += receiveBuffer2[index];
	//		}

	//		fs::path whereToBeSaved = filenameToSave;
	//		const auto copyOptions = fs::copy_options::update_existing
	//			| fs::copy_options::recursive
	//			;
	//		fs::copy(fileToDownload, whereToBeSaved, copyOptions);
	//		std::stringstream stream3;
	//		stream3 << "[SERVER] Download complete !";
	//		std::string message3 = stream3.str();
	//		client.Send(message3.c_str(), message3.size());
	//		break;
	//	}
	//	}
	//} while (op != 0);
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