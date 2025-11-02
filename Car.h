#ifndef CAR_H
#define CAR_H
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>
#include <QDateTime>

class Car : public QWidget
{
public:
    QString carnum;
    Car(QString);
    ~Car();
    QMovie *movie;
    void leaveParking(QWidget* widget);
    QDateTime entryTime;
private:
    QLabel *carNumLabel;
    QLabel *carGifLabel;
};

#endif // CAR_H
