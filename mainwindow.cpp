#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "Parkingplacelabel.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
    this->setFixedSize(1200,800);
    this->leftWidget = new QWidget;
    QWidget *rightWidget = new QWidget;
    leftWidget->setStyleSheet("background-color: #E0FFFF; border: 2px solid black;");
    rightWidget->setStyleSheet("background-color: #F0FFF0; border: 1px solid green;");

    QHBoxLayout *mainHLay = new QHBoxLayout;
    mainHLay->addWidget(leftWidget,5);
    mainHLay->addWidget(rightWidget,1);
    mainWidget->setLayout(mainHLay);

    /*
     * 初始化右边组件
    */
    QVBoxLayout *rightLay = new QVBoxLayout;
    //剩余车位数
    QLabel *spaceLeftLabel = new QLabel("剩余车位:0");

    //设置车位数
    QWidget *spaceNumWidget = new QWidget;
    QGridLayout *spaceNumGridlay = new QGridLayout;
    QLabel *spaceNumLabel = new QLabel("每行车位数:");
    spaceNumSpin = new QSpinBox;
    QPushButton *spaceNumOkButton = new QPushButton("确认设置");
    spaceNumSpin->setValue(1);
    spaceNumSpin->setMaximum(4);
    spaceNumSpin->setMinimum(1);
    spaceNumSpin->setStyleSheet(R"(
        QSpinBox {
            padding-right: 20px;
            max-width: 80px;
        }
        QSpinBox::up-button {
            subcontrol-origin: border;
            subcontrol-position: top right;
            width: 20px;
        }
        QSpinBox::down-button {
            subcontrol-origin: border;
            subcontrol-position: bottom right;
            width: 20px;
        }
    )");
    spaceNumGridlay->addWidget(spaceNumLabel,0,0);
    spaceNumGridlay->addWidget(spaceNumSpin,0,1);
    spaceNumGridlay->addWidget(spaceNumOkButton,1,0,1,2);
    spaceNumWidget->setLayout(spaceNumGridlay);

    //车辆入队及入库
    QWidget *carPushWidget = new QWidget;
    QGridLayout *carPushGridLay = new QGridLayout;
    QLabel *nowLisence = new QLabel("当前车牌:00000");
    QPushButton *randLisenceButton = new QPushButton("随机车牌号");
    QPushButton *pushCarButton = new QPushButton("车辆入队");
    QPushButton *queueTopButton = new QPushButton("队首入库");

    carPushGridLay->addWidget(nowLisence,0,0);
    carPushGridLay->addWidget(randLisenceButton,0,1);
    carPushGridLay->addWidget(pushCarButton,1,0,1,2);
    carPushGridLay->addWidget(queueTopButton,2,0,1,2);
    carPushWidget->setLayout(carPushGridLay);

    //车辆出库
    QWidget *carPopWidget = new QWidget;
    QVBoxLayout *carPopLay = new QVBoxLayout;
    QLabel *carPopLabel = new QLabel("请输入出库车牌号：");
    QLineEdit *carPopLineEdit = new QLineEdit;
    QPushButton * carPopButton = new QPushButton("确认出库");


    carPopLay->addWidget(carPopLabel);
    carPopLay->addWidget(carPopLineEdit);
    carPopLay->addWidget(carPopButton);

    carPopWidget->setLayout(carPopLay);

    //信息展示栏
    QTextEdit *infoTextEdit = new QTextEdit;

    rightLay->addWidget(spaceLeftLabel,1);
    rightLay->addWidget(spaceNumWidget,2);
    rightLay->addWidget(carPushWidget,2);
    rightLay->addWidget(carPopWidget,2);
    rightLay->addWidget(infoTextEdit,6);
    rightWidget->setLayout(rightLay);

    /*
     * 左侧栏
     */
    this->leftGridLay = new QGridLayout;
    //设置等大
    for (int i = 0; i < 18; ++i) {
        leftGridLay->setColumnStretch(i, 1);
    }
    for (int i = 0; i < 4; ++i) {
        leftGridLay->setRowStretch(i,1);
    }

    initLeft();

    /*
     * 动作设置区
     */
    connect(spaceNumOkButton, &QPushButton::clicked,
            this, &MainWindow::spaceNumOkButton_clicked);

}

void MainWindow::initLeft()
{
    QWidget *entrySeparatorWidget = new QWidget;
    entrySeparatorWidget->setStyleSheet("background-color: black;");
    entrySeparatorWidget->setStyleSheet("background-color: #F0FFF0; border: 1px solid green;");
    leftGridLay->addWidget(entrySeparatorWidget, 3, 0, 1, 18);
    leftWidget->setLayout(leftGridLay);
    int numPerLine = spaceNumSpin->value();
    int spaceWidth = 12/numPerLine;
    int index = 3;
    for (int i = 0; i < numPerLine; i++) {
        ParkingPlaceLabel *uPLabel = new ParkingPlaceLabel;
        ParkingPlaceLabel *dPLabel = new ParkingPlaceLabel;
        leftGridLay->addWidget(uPLabel,0,index,1,spaceWidth);
        leftGridLay->addWidget(dPLabel,2,index,1,spaceWidth);
        this->parkingIconPoints.push_back(uPLabel);
        this->parkingIconPoints.push_back(dPLabel);
        index += spaceWidth;
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::spaceNumOkButton_clicked()
{
    for (auto p: parkingIconPoints) {
        delete p;
    }
    parkingIconPoints.clear();
    initLeft();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint relativePos = event->pos();
    int x = relativePos.x();
    int y = relativePos.y();
    qDebug() <<"Local Position"
             << "X =" << x
             << "Y =" << y;
}
