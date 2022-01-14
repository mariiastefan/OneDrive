//#include <iostream>
//#include <filesystem>
//#include <cstdlib>
//#include "User.h";
//#include "FolderUser.h";
//#include "server.h";
//#include "client.h";
////#include "../TcpConnection/server.h"
////#include "../TcpConnection/client.h"
//
//namespace fs = std::filesystem;
//
//int main()
//{
//	/*Server s("192.168.2.99");
//	Client c("192.168.2.99", 54000);
//	s.Start();
//	c.Start();*/
//	std::fstream g("conturi.txt");
//	/*for (int index = 0; index < 2; index++)
//	{
//		User a;
//		std::cin >> a;
//		g << a;
//	}*/
//	/*fs::path path_obj(fs::temp_directory_path());
//	fs::create_directory("test_filesystem");
//	fs::permissions("test_filesystem", fs::perms::others_all, fs::perm_options::remove);*/
//	//User a;
//	//std::cin >> a;
//	//g << a;
//	/*FolderUser b("ana");
//	b.SetNrItems();*/
//	//b.AddFile("Ela");
//	//b.DeleteFile("ana", "poza_bd.jpeg");
//	//std::cout<<b.GetNrItems();
//	FolderUser b("ana");
//	//b.AddFile("ana");
//	b.DeleteFile2();
//	//b.SetNrItems();
//	//std::cout << b.GetPath() << '\n';
//	//::cout << b.GetFolderSize();
//	std::cout << '\n';
//
//
//	//std::cout<<b.GetNrItems();
//	return 0;
//}
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <experimental/filesystem>

using namespace std::chrono_literals;
int main()
{
    auto p = std::filesystem::temp_directory_path() / "example.bin";
    std::ofstream(p.c_str()).put('a'); // create file

    auto print_last_write_time = [](std::filesystem::file_time_type const& ftime) {
        std::time_t cftime = std::chrono::system_clock::to_time_t(fs::last_write_time(p));
        std::cout << "File write time is " << std::asctime(std::localtime(&cftime));
    };

    auto ftime = std::filesystem::last_write_time(p);
    print_last_write_time(ftime);

    std::filesystem::last_write_time(p, ftime + 1h); // move file write time 1 hour to the future
    ftime = std::filesystem::last_write_time(p); // read back from the filesystem
    print_last_write_time(ftime);

    std::filesystem::remove(p);
}