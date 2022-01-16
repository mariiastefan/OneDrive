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
					if (received > 0)
					{
						std::copy(receiveBuffer.begin(), receiveBuffer.begin() + received, std::ostream_iterator<char>(std::cout, ""));
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
}