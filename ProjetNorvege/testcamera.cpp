#include "testcamera.h"
#include <QPainter>
#include <QDebug>
#include <stdlib.h>

TestCamera::TestCamera(std::string n)
    : AbstractCamera(), n(n) {
    srand(42);
}

void TestCamera::setProperty(CameraProperty* p){
    //Nothing here
    qDebug() << "setProperty";
}
void TestCamera::updateProperty(CameraProperty* p){
    //Nothing here
}

QImage TestCamera::retrieveImage(){
    QImage img(400,400, QImage::Format_RGB32);
    img.fill(Qt::green);
    QPainter p;
    p.begin(&img);
    p.drawRect(1,1,397,397);
    p.drawRect(rand()%100, rand()%100,rand()%300, rand()%300);
    p.end();
    return img;
}
