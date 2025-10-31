#include "Car.h"
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>
#include <iostream>
#include <QMovie>
#include <QVBoxLayout>

Car::Car(QString num){
    using std::cout;
    using std::endl;
    movie = new QMovie(":/images/carGif.gif");
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
    if (carGifLabel != nullptr) {
        delete carGifLabel;
    }
    if (carNumLabel != nullptr) {
        delete carNumLabel;
    }
}
