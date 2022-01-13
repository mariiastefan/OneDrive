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

App::App(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::darkCyan);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");
    ui.new_folder->setHidden(true);
    ui.lineEditaddnew->setHidden(true);
    ui.folderName->setHidden(true);
    ui.folderName_2->setHidden(true);
    ui.AddLine->setHidden(true);


    //dirModel = new QFileSystemModel(this);
    ////dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    //dirModel->setRootPath(sPath);
    //ui.treeView->setModel(dirModel);

    //fileModel = new QFileSystemModel(this);
    //fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    //
    //fileModel->setRootPath(sPath);
    //ui.listView->setModel(fileModel);
}

App::App(const User& x, QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::gray);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");
    ui.new_folder->setHidden(true);
    ui.lineEditaddnew->setHidden(true);
    ui.folderName->setHidden(true);
    ui.folderName_2->setHidden(true);
    ui.AddLine->setHidden(true);
    FolderUser user(x.GetUsername());
    model = new QFileSystemModel(this);
    UserName = x.GetUsername();
    model->setReadOnly(false);
    QString qstr = QString::fromStdString(user.GetPath2());
    model->setRootPath(qstr);
    ui.treeView->setModel(model);
    ui.treeView->setRootIndex(model->index(qstr));

  /*  QString sPath = "../../TcpConnection/Client/UserFolder/adina";

    dirModel = new QFileSystemModel();
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(sPath);
    ui.treeView->setModel(dirModel);

    fileModel = new QFileSystemModel(this); 
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files );
    fileModel->setRootPath(sPath);
    ui.listView->setModel(fileModel);*/
}


//void App::on_treeView_clicked(QModelIndex index)
//{
//    //QString sPath = dirModel->fileInfo(index).absoluteFilePath();
//    QString sPath = "../../TcpConnection/Client/UserFolder/adina";
//    ui.listView->setRootIndex(fileModel->setRootPath(sPath));
//}


void App::on_add_clicked()
{
    ui.folderName_2->setHidden(false);
    ui.AddLine->setHidden(false);
    QCompleter* cmpt;
    QFileSystemModel* mo;
    mo = new QFileSystemModel(this);
    cmpt = new QCompleter(mo, this);
    mo->setRootPath(QDir::rootPath());
    ui.AddLine->setCompleter(cmpt);

}

void App::on_addNew_clicked()
{
    on_addNew = true;
    QPalette palette;
    this->setWindowTitle("ADD");
    palette.setBrush(QPalette::Background, Qt::white);

    ui.add->setHidden(false);
    ui.new_folder->setHidden(false);
    ui.lineEditaddnew->setHidden(false);
   
    ui.upload->setHidden(true);
    ui.rename->setHidden(true);
    ui.lineEdit->setHidden(true);
    ui.searchBtn->setHidden(true);

}

void App::on_deleteBtn_clicked()
{
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
}

void App::on_new_folder_clicked()
{
    QString foldername = ui.lineEditaddnew->text();
    std::string folder_name = foldername.toStdString();
    FolderUser folderuser(folder_name);
    QMessageBox msgBox;
    msgBox.setText("You have added a new folder");
    msgBox.exec();
}

void App::on_searchBtn_clicked()
{
   /* ui.folderName->setHidden(Search);
    ui.lineEditaddnew->setHidden(Search);
    if (Search == true) Search = false;
    else Search = true;*/
}
