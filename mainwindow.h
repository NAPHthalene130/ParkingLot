#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <vector>
#include "Parkingplacelabel.h"
#include "Queue.h"
#include "Car.h"
#include <set>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *leftWidget;
    QGridLayout *leftGridLay;
    QSpinBox *spaceNumSpin = new QSpinBox;
    void initLeft();
    std::vector<ParkingPlaceLabel*> parkingIconPoints;
    Queue<Car*> carQueue;
    std::set<QString> carnumQueueHave;
    std::set<QString> carnumParkingHave;
    QString nowCarnum;
    QLabel *nowLisence;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void spaceNumOkButton_clicked();
    void pushCarButton_clicked();
    void randLisenceButton_clicked();
protected:
    //测试鼠标位置
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
