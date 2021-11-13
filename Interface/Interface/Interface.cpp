#include "Interface.h"
#include <qstackedwidget.h>
#include <QVBoxLayout>
#include <qcombobox.h>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    QPixmap bg("login_bg.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive");
    QWidget* firstPageWidget = new QWidget;
    QWidget* secondPageWidget = new QWidget;
    QWidget* thirdPageWidget = new QWidget;

    QStackedWidget *stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(secondPageWidget);
    stackedWidget->addWidget(thirdPageWidget);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    setLayout(layout);
    QComboBox *pageComboBox = new QComboBox;
    pageComboBox->addItem(tr("Page 1"));
    pageComboBox->addItem(tr("Page 2"));
    pageComboBox->addItem(tr("Page 3"));
    connect(pageComboBox, QOverload<int>::of(&QComboBox::activated),
    stackedWidget, &QStackedWidget::setCurrentIndex);
}


void Interface::on_signIn_clicked()
{
    on_signIn = true;
 QString username = ui.lineEdit_username->text();
 QString password = ui.lineEdit_password->text();

 if (check(username, password) == false)
 {
     QMessageBox msgBox;
     msgBox.setText("Sign In Failed");
     msgBox.setInformativeText("Bad Username/Password Combo!!!!");
     msgBox.setStandardButtons(QMessageBox::Ok);
     msgBox.exec();
    
 }
}

void Interface::on_signUp_clicked()
{
    on_signUp = true;
    QWidget* wdg = new QWidget;
    QPalette palette;
    //palette.setBrush(wdg->backgroundRole(), QBrush(QImage("logo1.jpg")));
    palette.setBrush(wdg->backgroundRole(), QBrush(QColor(65, 105, 225)));
    wdg->setWindowTitle("Create OneDrive Account");
    wdg->setWindowIcon(QIcon("logo1.jpg"));
    wdg->setPalette(palette);
    /*QLabel* label = new QLabel(wdg);
    label->setText("username");
    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label->setGeometry(QRect(10, 10, 30, 80));
    */
   
    wdg->show();
   
    hide();
 
}

bool Interface::check(QString username, QString password)
{
    return false;
}
