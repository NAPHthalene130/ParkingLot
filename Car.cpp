#include "Car.h"
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>
#include <iostream>
#include <QMovie>
#include <QVBoxLayout>
#include <QSequentialAnimationGroup>
#include <ctime>
#include <QTransform>
Car::Car(QString num){
    using std::cout;
    using std::endl;
    movie = new QMovie(":/images/carGif.gif");
    carnum = num;
    if (movie->isValid()) {
        this->carGifLabel = new QLabel;
        this->carNumLabel = new QLabel;
        this->carGifLabel->setMovie(movie);
        this->carGifLabel->setScaledContents(true);
        this->setStyleSheet("border: none;");
        this->carNumLabel->setText(num);
        this->carNumLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->carNumLabel->setStyleSheet("border: 1px solid green;");
        QVBoxLayout *carLay = new QVBoxLayout;
        carLay->addWidget(this->carNumLabel);
        carLay->addWidget(this->carGifLabel);
        this->carGifLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        this->carNumLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        this->carGifLabel->setFocusPolicy(Qt::NoFocus);
        this->carNumLabel->setFocusPolicy(Qt::NoFocus);

        this->setLayout(carLay);
        movie->start();
    } else {
        cout << "WARN: set gif failed" << endl;
    }
    this->setFixedSize(120,150);
    this->setAutoFillBackground(false);
}

Car::~Car()
{
    std::cout << "DELETE CAR" << std::endl;
    if (carGifLabel != nullptr) {
        delete carGifLabel;
    }
    if (carNumLabel != nullptr) {
        delete carNumLabel;
    }
}

void Car::leaveParking(QWidget* widget)
{

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(widget);
    QPropertyAnimation *animAB = new QPropertyAnimation(this, "pos");
    animAB->setDuration(300);
    animAB->setStartValue(this->pos());
    QPoint p = this->pos();
    p.setY(200);
    animAB->setEndValue(p);
    group->addAnimation(animAB);
    QPropertyAnimation *animBC = new QPropertyAnimation(this, "pos");
    animBC->setDuration(p.x());
    animBC->setStartValue(p);
    animBC->setEndValue(QPoint(0, 200));
    group->addAnimation(animBC);
    QObject::connect(animBC, &QPropertyAnimation::finished,
                     this, &QWidget::deleteLater);
    group->start();
}

