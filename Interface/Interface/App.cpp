#include "App.h"
#include "FolderUser.h"
#include <qstackedwidget.h>
#include <QVBoxLayout>
#include <qcombobox.h>
#include <QCombobox>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include "qtreewidget.h"
#include <QListView>
#include <QTreeView>
#include <QtCore>
#include <QtGui>
#include <QScrollBar>
#include<QCompleter>
#include "User.h"
#include <QFileDialog>
#include <fstream>
#include "Client.h"


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

bool checkToSeeIfUserIsUpdated(const User& x)
{
    FolderUser folder(x.GetUsername());
    int ok = 0;
    for (auto& p1 : fs::recursive_directory_iterator(folder.GetPathAsString()))
    {
        ok = 0;
        for (auto& p2 : fs::recursive_directory_iterator(folder.GetServerPath()) )
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
    if (ok == 0)
        return 0;
    return 1;
}


App::App(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::darkCyan);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");
  
    
}

App::App(const User& x, QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::white);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");

    FolderUser user(x.GetUsername());
    model = new QFileSystemModel(this);
    username = x.GetUsername();
    model->setReadOnly(false);
    QString qstr = QString::fromStdString(user.GetPathAsString());
    model->setRootPath(qstr);
    ui.treeView->setModel(model);
    ui.treeView->verticalScrollBar()->setEnabled(true);
    ui.treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui.treeView->setRootIndex(model->index(qstr));
   
    QModelIndex index = ui.treeView->currentIndex();
   

    model2 = new QFileSystemModel(this);
    username = x.GetUsername();
    model2->setReadOnly(false);
    QString qstr2 = QString::fromStdString(user.GetServerPath());
    model2->setRootPath(qstr2);
    ui.treeView_2->setModel(model2);
    ui.treeView_2->verticalScrollBar()->setEnabled(true);
    ui.treeView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui.treeView_2->setRootIndex(model2->index(qstr2));

    QModelIndex index2 = ui.treeView_2->currentIndex();
    
}

void App::on_add_clicked()
{
    FolderUser folderuser(username);
    QCompleter* cmpt;
    QFileSystemModel* model;
    model = new QFileSystemModel(this);
    cmpt = new QCompleter(model, this);
    model->setRootPath(QDir::rootPath());
    QString filter = "All File (*.*) ;; Text File(*.txt) ;; XML File (*.xml*)";
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    FolderUser aux(username);
    aux.AddFile(filename.toStdString());
}


void App::on_deleteBtn_clicked()
{
    std::wstring pathOrigin = fs::current_path();

    QModelIndex index = ui.treeView->currentIndex();
    FolderUser aux(username);
    std::string name = model->fileName(index).toStdString();
    std::string pathClient = "../../TcpConnection/Client/UserFolder";
    pathClient += '/';
    pathClient += username;
    pathClient += '/';
    pathClient += name;
    std::uintmax_t n1 = fs::remove(pathClient);
    //aux.DeleteFile(UserName,name);

    fs::current_path(pathOrigin);

   
    
}

void App::on_searchBtn_clicked()
{
 
}

void App::on_ButtonDeleteAccount_clicked()
{
    std::fstream g("conturi.txt", std::ios::app);
    ButtonDeleteAccount = true;
    g.open("conturi.txt");
    g.close();
    bool verifUser = false;
    QMessageBox msgBox;
    DeleteAccount(g, User(username));
    msgBox.setText("This account will be deleted");
    msgBox.exec();

}

void App::on_downloadButton_clicked()
{
    User user(username);
    FolderUser folderuser(username);
    Client client(username);
    QModelIndex index = ui.treeView->currentIndex();
    std::string name = model->fileName(index).toStdString();
    std::string pathServer = "../../TcpConnection/Server/UserFolder";
    pathServer += '/';
    pathServer += username;
    pathServer += '/';
    pathServer += name;
    client.downloadFromServer(pathServer, folderuser.GetPathAsString());
}

void App::on_treeView_doubleClicked(const QModelIndex & index)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(model->filePath(index)));
}
