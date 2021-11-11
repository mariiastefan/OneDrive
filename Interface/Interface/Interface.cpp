#include "Interface.h"
#include <qstackedwidget.h>
#include <QVBoxLayout>
#include <qcombobox.h>
Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    QPixmap bg("background.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);
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

}

void Interface::on_signUp_clicked()
{

}
