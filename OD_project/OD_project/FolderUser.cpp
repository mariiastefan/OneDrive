#include "FolderUser.h"
#include <filesystem>
#include<iostream>
namespace fs = std::filesystem;

FolderUser::FolderUser(std::string userName)
{
    std::string path = "../../UserFolder";
    fs::current_path(path);
    fs::create_directory(userName);
}
