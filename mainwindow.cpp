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
#include <QPropertyAnimation>
#include "Car.h"
#include <iostream>
#include <QMovie>
#include <QRandomGenerator>
#include <QDateTime>
#include <cstdlib>
#include <ctime>
#include <QtGlobal>
#include <vector>
#include <QPoint>
#include <QSequentialAnimationGroup>
#include <chrono>
#include <ctime>
#include <QDateTime>

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
    this->spaceLeftLabel = new QLabel("剩余车位:0");

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
    this->nowLisence = new QLabel("当前车牌:00000");
    nowCarnum = "00000";
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
    this->carPopLineEdit = new QLineEdit;
    QPushButton* carPopButton = new QPushButton("确认出库");


    carPopLay->addWidget(carPopLabel);
    carPopLay->addWidget(carPopLineEdit);
    carPopLay->addWidget(carPopButton);

    carPopWidget->setLayout(carPopLay);

    //信息展示栏
    this->infoTextEdit = new QTextEdit;
    infoTextEdit->setReadOnly(true);

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
    QWidget *entrySeparatorWidget = new QWidget;
    entrySeparatorWidget->setStyleSheet("background-color: black;");
    entrySeparatorWidget->setStyleSheet("background-color: #F0FFF0; border: 1px solid green;");
    leftGridLay->addWidget(entrySeparatorWidget, 3, 0, 1, 18);
    QLabel *outLabel = new QLabel("出\n口");
    outLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QFont outFont = outLabel->font();
    outFont.setBold(true);
    outFont.setPointSize(48);
    outLabel->setFont(outFont);
    leftGridLay->addWidget(outLabel,0,0,3,3);
    spaceState.assign(8,nullptr);
    initLeft();

    // Car *myCar = new Car;
    // myCar->move(50,50);
    // myCar->setParent(leftWidget);

    /*
     * 动作设置区
     */
    connect(spaceNumOkButton, &QPushButton::clicked,
            this, &MainWindow::spaceNumOkButton_clicked);
    connect(pushCarButton, &QPushButton::clicked,
            this, &MainWindow::pushCarButton_clicked);
    connect(randLisenceButton, &QPushButton::clicked,
            this, &MainWindow::randLisenceButton_clicked);
    connect(queueTopButton, &QPushButton::clicked,
            this, &MainWindow::queueTopButton_clicked);
    connect(carPopButton, &QPushButton::clicked,
            this, &MainWindow::carPopButton_clicked);

}

//车位排布设置
void MainWindow::initLeft()
{
    leftWidget->setLayout(leftGridLay);
    int numPerLine = spaceNumSpin->value();
    parkingSpareSpace = 2 * numPerLine;
    parkingAllSpace = 2 * numPerLine;
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
    for (int i = 0 ; i < 8; i++) {
        if (spaceState[i] != nullptr) {
            delete spaceState[i];
            spaceState[i] = nullptr;
        }
    }
    spaceState.assign(8,nullptr);
    spaceLeftLabel->setText("剩余车位:"+ QString::number(parkingSpareSpace));
    infoTextEdit->setText("车位设置成功！\n当前共"+ QString::number(numPerLine*2) + "个车位");
}

MainWindow::~MainWindow()
{
}

//设置车位数
void MainWindow::spaceNumOkButton_clicked()
{
    for (auto p: parkingIconPoints) {
        delete p;
    }
    parkingIconPoints.clear();
    carnumParkingHave.clear();
    carnumQueueHave.clear();
    carQueue.clear();
    initLeft();

}

//新车辆入队
void MainWindow::pushCarButton_clicked()
{
    using std::cout;
    using std::endl;
    cout << "pushCarButton_Clicked" << endl;
    if ((carnumQueueHave.find(nowCarnum) == carnumQueueHave.end()) && (carnumParkingHave.find(nowCarnum) == carnumParkingHave.end())) { //车牌不在库内及队内
        if (this->carQueue.size() >= 4) { //队满
            infoTextEdit->setText("等待位数已满！");
        } else {
            cout << 1 << endl;
            Car *newCar = new Car(nowCarnum);
            newCar->setParent(leftWidget);
            newCar->carnum = nowCarnum;
            carnumQueueHave.insert(nowCarnum);
            carQueue.push(newCar);
            newCar->move(20,600);
            newCar->show();
            QPropertyAnimation *animation = new QPropertyAnimation(newCar, "pos");
            animation->setDuration(1000);
            animation->setStartValue(QPoint(20, 600));
            animation->setEndValue(QPoint(850 - 150*carQueue.size(), 600));
            animation->start();
        }
    } else { //车牌在库内或队内
        infoTextEdit->setText("车辆已存在！");
    }
}

//生成随机车牌
void MainWindow::randLisenceButton_clicked()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    QString str = "";
    bool flag = true;
    while (flag) {
        str = "";
        for (int i = 0 ; i < 5; i++) {
            int num = std::rand()%10;
            str += QString::number(num);
        }
        if ((carnumParkingHave.find(str) == carnumParkingHave.end()) && (carnumQueueHave.find(str) == carnumQueueHave.end())) {
            flag = false;
        }
    }
    nowCarnum = str;
    nowLisence->setText("当前车牌:"+str);
}

//队首入车库
void MainWindow::queueTopButton_clicked()
{
    using std::cout;
    using std::endl;
    if (carQueue.size() > 0 && parkingSpareSpace > 0) {
        cout << "TEST2" << endl;
        Car *queueTop = carQueue.getTop();
        QString num = queueTop->carnum;
        Car *newCar = new Car(num);
        carnumQueueHave.erase(num);
        carnumParkingHave.insert(num);
        newCar->setParent(leftWidget);
        newCar->move(queueTop->pos());
        newCar->show();
        carQueue.pop();
        queueTop = newCar;
        int target = 0;
        for (int i = 0; i < parkingAllSpace; i++) {
            if (spaceState[i] == nullptr) {
                target = i;
                break;
            }
        }
        int yPos = (target%2==0) ? 20:400;
        int spaceWidth = (810-170) / (parkingAllSpace/2);
        int xPos = 810 - spaceWidth * (target/2) - spaceWidth/2 - 60;
        QSequentialAnimationGroup *group = new QSequentialAnimationGroup(leftWidget);
        Node<Car*>* nowNode = carQueue.getFrontIt();
        while (carQueue.size() > 0 && nowNode != nullptr) {
            QPropertyAnimation *ani = new QPropertyAnimation(nowNode->value, "pos");
            ani->setDuration(500);
            QPoint p = nowNode->value->pos();
            ani->setStartValue(p);
            p.setX(p.x()+150);
            ani->setEndValue(p);
            ani->setEasingCurve(QEasingCurve::OutQuad);
            ani->start();
            nowNode = nowNode->nextNode;
        }
        QPropertyAnimation *animAB = new QPropertyAnimation(queueTop, "pos");
        animAB->setDuration(300);
        animAB->setStartValue(queueTop->pos());
        animAB->setEndValue(QPoint(820, 600));
        group->addAnimation(animAB);
        QPropertyAnimation *animBC = new QPropertyAnimation(queueTop, "pos");
        animBC->setDuration(500);
        animBC->setStartValue(QPoint(820,600));
        animBC->setEndValue(QPoint(820, 200));
        group->addAnimation(animBC);
        QPropertyAnimation *animCD = new QPropertyAnimation(queueTop, "pos");
        animCD->setDuration((820-xPos));
        animCD->setStartValue(QPoint(820,200));
        animCD->setEndValue(QPoint(xPos, 200));
        group->addAnimation(animCD);
        QPropertyAnimation *animDE = new QPropertyAnimation(queueTop, "pos");
        animDE->setDuration(500);
        animDE->setStartValue(QPoint(xPos,200));
        animDE->setEndValue(QPoint(xPos, yPos));
        group->addAnimation(animDE);
        group->start();
        spaceState[target] = newCar;
        parkingSpareSpace--;
        newCar->entryTime = QDateTime::currentDateTime();
        spaceLeftLabel->setText("剩余车位:"+ QString::number(parkingSpareSpace));
        infoTextEdit->setText("车牌号:" + newCar->carnum + "入库成功\n" + "入库时间" + newCar->entryTime.toString("yyyy/MM/dd hh:mm:ss"));
    }
}

//车辆出库
void MainWindow::carPopButton_clicked()
{
    using std::cout;
    using std::endl;
    QString num = carPopLineEdit->text();
    cout << "carPopButtonClicked: Num: " << num.toStdString() << endl;
    for (int i = 0; i < parkingAllSpace; i++) {
        if (spaceState[i] != nullptr ) {
            cout << "state[" << i << "] Num: " << spaceState[i]->carnum.toStdString() << endl;
        }
        if (spaceState[i] != nullptr && spaceState[i]->carnum == num) {
            spaceState[i]->leaveParking(leftWidget);
            parkingSpareSpace++;
            spaceLeftLabel->setText("剩余车位:"+ QString::number(parkingSpareSpace));
            carnumParkingHave.erase(num);

            QDateTime exitTime = QDateTime::currentDateTime();
            QString text = "车牌号:" + spaceState[i]->carnum + "\n";
            text += "入库时间:" + spaceState[i]->entryTime.toString("yyyy/MM/dd hh:mm:ss") + '\n';
            text += "出库时间" + exitTime.toString("yyyy/MM/dd hh:mm:ss") + '\n';\
            qint64 totalSeconds = spaceState[i]->entryTime.secsTo(exitTime);
            text += "计费规则：￥1/秒\n";
            text += "停车共计费:￥" + QString::number(totalSeconds) + "\n";
            qint64 hour = totalSeconds / 3600;
            totalSeconds %= 3600;
            qint64 minute = totalSeconds / 60;
            totalSeconds %= 60;
            qint64 second = totalSeconds;
            text += "停车时长:" + QString::number(hour) + "时" + QString::number(minute) + "分" + QString::number(second) + "秒\n";
            infoTextEdit->setText(text);

            spaceState[i] = nullptr;
        }
    }
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
