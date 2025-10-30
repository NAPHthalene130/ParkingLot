#include "Parkingplacelabel.h"
#include <QPixmap>
#include <iostream>
ParkingPlaceLabel::ParkingPlaceLabel() {
    QPixmap icon(":/images/img.png");
    if (icon.isNull()) {
        using std::cout;
        using std::endl;
        cout << "WARN: set icon failed" << endl;
    } else {
        this->setPixmap(icon);
    }
    this->setScaledContents(true);
}
