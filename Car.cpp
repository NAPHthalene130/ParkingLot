#include "Car.h"
#include <QPropertyAnimation>
#include <QLabel>
#include <QPoint>
#include <qlabel.h>
#include <iostream>
#include <QMovie>

Car::Car(){
    using std::cout;
    using std::endl;
    QMovie *movie = new QMovie(":/images/carGif.gif");
    if (movie->isValid()) {
        this->setMovie(movie);
        movie->start();
    } else {
        cout << "WARN: set gif failed" << endl;
    }
}
