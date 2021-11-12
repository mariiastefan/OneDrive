#include "FolderUser.h"
#include <filesystem>
#include<iostream>


FolderUser::FolderUser()
{
}

FolderUser::FolderUser(std::string userName)
{
    namespace fs1 = std::filesystem;
    std::string path = "../../UserFolder";
    std::wstring pathOrigin = fs1::current_path();
    fs1::current_path(path);
    fs1::create_directory(userName);
    fs1::current_path(pathOrigin);
}

void FolderUser::DeleteFolder(std::string userName)
{
    namespace fs1 = std::filesystem;
    std::string path = "../../UserFolder";
    std::wstring pathOrigin = fs1::current_path();
    fs1::current_path(path);
    std::uintmax_t n = fs1::remove_all(userName);
    fs1::current_path(pathOrigin);
}
