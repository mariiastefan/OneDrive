#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "user.h";
#include "FolderUser.h";
#include "server.h";
#include "client.h";
//#include "../TcpConnection/server.h"
//#include "../TcpConnection/client.h"

namespace fs = std::filesystem;

int main()
{
	/*Server s("192.168.2.99");
	Client c("192.168.2.99", 54000);
	s.Start();
	c.Start();*/
	std::fstream g("conturi.txt");
	/*for (int index = 0; index < 2; index++)
	{
		User a;
		std::cin >> a;
		g << a;
	}*/
	/*fs::path path_obj(fs::temp_directory_path());
	fs::create_directory("test_filesystem");
	fs::permissions("test_filesystem", fs::perms::others_all, fs::perm_options::remove);*/
	//User a;
	//std::cin >> a;
	//g << a;
	/*FolderUser b("ana");
	b.SetNrItems();*/
	//b.AddFile("Ela");
	//b.DeleteFile("ana", "poza_bd.jpeg");
	//std::cout<<b.GetNrItems();
	std::cout << "s";
	FolderUser b("ana");
	b.AddFile("ana");
	b.SetNrItems();
	//std::cout << b.GetPath() << '\n';
	std::cout << b.GetFolderSize();
	std::cout << '\n';


	//std::cout<<b.GetNrItems();
	return 0;
}