#include "FolderUser.h"
#include <filesystem>
#include <cstdio>
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
std::string FolderUser::GetFolderName() const
{
    return m_FolderName;
}
int FolderUser::GetNrItems()const
{
    return m_nrItems;
}
void FolderUser::SetFolderName(const std::string& foldername2)
{
    m_FolderName = foldername2;
}
void FolderUser::SetNrItems(const int& nrItems2)
{
    m_nrItems = nrItems2;
}

void FolderUser::AddFile(std::string userName)
{
    std::string old_place;
    std::cout << "introduceti calea catre fisier: ";
    std::cin >> old_place;

    std::string ItemName;
    std::cout << "cititi numele fisierului";
    std::cin >> ItemName;

    old_place += "/";
    old_place += ItemName;

    namespace fs1 = std::filesystem;
    std::wstring pathOrigin = fs1::current_path();
    std::string path = "../../UserFolder";
    path += "/";
    path += userName;
    fs1::current_path(path);
    path += "/";
    path += ItemName;
    fs1:copy((old_place), fs1::current_path());
    fs1::current_path(pathOrigin);
}
bool FolderUser::verify_FolderName(FolderUser folder, std::string name)
{
    if (folder.GetFolderName() == name)
        return 1;
    return 0;
}
