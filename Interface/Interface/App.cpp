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
#include<QCompleter>
#include "User.h"
#include <QFileDialog>
#include <fstream>


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
    for (auto& p1 : fs::recursive_directory_iterator(folder.GetPath2()))
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
    //ui.new_folder->setHidden(true);
   // ui.lineEditaddnew->setHidden(true);
    //ui.folderName->setHidden(true);
  //  ui.folderName_2->setHidden(true);
  //  ui.AddLine->setHidden(true);
    ui.BackButton->setHidden(true);
    
}

App::App(const User& x, QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::white);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");

    // ui.new_folder->setHidden(true);
   // ui.lineEditaddnew->setHidden(true);
    //ui.AddItemBtn->setHidden(true);

    //ui.folderName->setHidden(true);
  //  ui.folderName_2->setHidden(true);
  //  ui.AddLine->setHidden(true);

    FolderUser user(x.GetUsername());
    model = new QFileSystemModel(this);
    UserName = x.GetUsername();
    model->setReadOnly(false);
    QString qstr = QString::fromStdString(user.GetPath2());
    model->setRootPath(qstr);
    ui.treeView->setModel(model);
    
    ui.treeView->setRootIndex(model->index(qstr));
    
    QModelIndex index = ui.treeView->currentIndex();
    ui.BackButton->setHidden(false);
    

    
}

void App::on_add_clicked()
{
    QCompleter* cmpt;
    QFileSystemModel* mo;
    mo = new QFileSystemModel(this);
    cmpt = new QCompleter(mo, this);
    mo->setRootPath(QDir::rootPath());
    QString filter = "All File (*.*) ;; Text File(*.txt) ;; XML File (*.xml*)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://");
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    FolderUser aux(UserName);
    aux.AddFile(file_name.toStdString());

    ui.BackButton->setHidden(false);
    
}


void App::on_deleteBtn_clicked()
{
    std::wstring pathOrigin = fs::current_path();

    QModelIndex index = ui.treeView->currentIndex();
    FolderUser aux(UserName);
    std::string name = model->fileName(index).toStdString();
    std::string pathClient = "../../TcpConnection/Client/UserFolder";
    pathClient += '/';
    pathClient += UserName;
    pathClient += '/';
    pathClient += name;
    std::uintmax_t n1 = fs::remove(pathClient);
    //aux.DeleteFile(UserName,name);

    fs::current_path(pathOrigin);

    ui.BackButton->setHidden(false);
    
}

void App::on_searchBtn_clicked()
{
   /* ui.folderName->setHidden(Search);
    ui.lineEditaddnew->setHidden(Search);
    if (Search == true) Search = false;
    else Search = true;*/
}

void App::on_ButtonDeleteAccount_clicked()
{
    std::fstream g("conturi.txt", std::ios::app);
    ButtonDeleteAccount = true;
    g.open("conturi.txt");
    g.close();
    bool verif_user = false;
    QMessageBox msgBox;
    delete_account(g, User(UserName));
    msgBox.setText("This account will be deleted");
    msgBox.exec();

    ui.BackButton->setHidden(false);
}

