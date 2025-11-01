#ifndef CAR_H
#define CAR_H
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>

class Car : public QWidget
{
public:
    QString carnum;
    Car(QString);
    ~Car();
    QMovie *movie;
    void leaveParking(QWidget* widget);
private:
    QLabel *carNumLabel;
    QLabel *carGifLabel;
};

#endif // CAR_H
