#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
    this->setFixedSize(1200,800);
    QWidget *leftQWidget = new QWidget;
    QWidget *rightWidget = new QWidget;
    leftQWidget->setStyleSheet("background-color: #E0FFFF; border: 2px solid black;");
    rightWidget->setStyleSheet("background-color: #F0FFF0; border: 1px solid red;");

    QHBoxLayout *mainHLay = new QHBoxLayout;
    mainHLay->addWidget(leftQWidget,5);
    mainHLay->addWidget(rightWidget,1);
    mainWidget->setLayout(mainHLay);

    //初始化右边组件
    QVBoxLayout *rightLay = new QVBoxLayout;
    QLabel *spaceLeftLabel = new QLabel("剩余车位:0");

    rightLay->addWidget(spaceLeftLabel);
    rightWidget->setLayout(rightLay);
}

MainWindow::~MainWindow()
{
}
