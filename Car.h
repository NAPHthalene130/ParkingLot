#ifndef CAR_H
#define CAR_H
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>
#include <QDateTime>
#include <QPushButton>
#include <QTransform>
class Car : public QPushButton
{
public:
    QString carnum;
    Car(QString);
    ~Car();
    QMovie *movie;
    void leaveParking(QWidget* widget);
    QDateTime entryTime;
    int index = 0;
    int spaceIndex;
    bool isStop = false;
    void applyTransform(const QTransform &transform);
    QLabel *carNumLabel;
    QLabel *carGifLabel;
};

#endif // CAR_H
