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

App::App(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::white);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");
    ui.new_folder->setHidden(true);
    ui.lineEditaddnew->setHidden(true);
    ui.folderName->setHidden(true);
    

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(QDir::currentPath());
    //ui.treeWidget->setModel(dirModel);

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fileModel->setRootPath(QDir::currentPath());
    //ui.listWidget->setModel(fileModel);

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
    ui.folderName->setHidden(Search);
    ui.lineEditaddnew->setHidden(Search);
    if (Search == true) Search = false;
    else Search = true;
}
