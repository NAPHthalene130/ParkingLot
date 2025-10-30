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

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *leftWidget;
    QGridLayout *leftGridLay;
    QSpinBox *spaceNumSpin = new QSpinBox;
    void initLeft();
    std::vector<ParkingPlaceLabel*> parkingIconPoints;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void spaceNumOkButton_clicked();

protected:
    //测试鼠标位置
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
