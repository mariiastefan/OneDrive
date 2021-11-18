#include "FolderUser.h"
#include <filesystem>
#include <cstdio>
#include<iostream>


FolderUser::FolderUser()
{
    m_nrItems = 0;
}

FolderUser::FolderUser(std::string userName)
{
    m_FolderName = userName;
    m_nrItems = 0;
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


void FolderUser::SetNrItems()
{
    namespace fs1 = std::filesystem;
    std::string path1 = "../../UserFolder";
    std::wstring pathOrigin = fs1::current_path();
    path1 += "/";
    path1 += m_FolderName;
    fs1::current_path(path1);
    for (auto const& dir_entry : std::filesystem::directory_iterator{ fs1::current_path() })
        m_nrItems++;
    fs1::current_path(pathOrigin);
}

void FolderUser::AddFile(std::string userName)
{
    std::string old_place;
    std::cout << "introduceti calea catre fisier: ";
    std::cin >> old_place;

    std::string ItemName;
    do {
    std::cout << "cititi numele fisierului";
    std::cin >> ItemName;
    } while (verify_existItem(ItemName) == true);
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
    fs1::copy((old_place), fs1::current_path());
    fs1::current_path(pathOrigin);
     m_nrItems++;
     File aux(ItemName, "data");
     itemUser.push_back(aux);
}

bool FolderUser::verify_FolderName(FolderUser folder, std::string name)
{
    if (folder.GetFolderName() == name)
        return 1;
    return 0;
}

bool FolderUser::verify_existItem(std::string filename)
{
    for (int i = 0; i < itemUser.size(); i++)
    {
        if (filename == itemUser[i].GetFilename()) return true;
    }
    return false;
}