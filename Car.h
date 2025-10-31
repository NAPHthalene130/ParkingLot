#ifndef CAR_H
#define CAR_H
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>

class Car : public QLabel
{
public:
    QString carnum;
    Car();
    QMovie *movie;
};

#endif // CAR_H
