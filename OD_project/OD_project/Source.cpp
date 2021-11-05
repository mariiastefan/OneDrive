#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "user.h";
namespace fs = std::filesystem;
int main()
{
	std::ifstream g("conturi.txt");
	/*for (int index = 0; index < 2; index++)
	{
		User a;
		std::cin >> a;
		g << a;
	}*/
	/*fs::path path_obj(fs::temp_directory_path());
	fs::create_directory("test_filesystem");
	fs::permissions("test_filesystem", fs::perms::others_all, fs::perm_options::remove);*/
	User a("anda2321", "KKl123");
	if(verify_if_user_exists(g, a)) // nu returneaza bine trebuie modificat

		delete_account(g, a);
	return 0;
}