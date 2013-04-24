#include "testcamera.h"
#include <QPainter>

TestCamera::TestCamera()
    : AbstractCamera() {

}

void TestCamera::setProperty(CameraProperty* p){
    //Nothing here
}
void TestCamera::updateProperty(CameraProperty* p){
    //Nothing here
}

QImage TestCamera::retrieveImage(){
    QImage img(400,400, QImage::Format_RGB32);
    img.fill(Qt::green);
    QPainter p;
    p.begin(&img);
    p.drawRect(50, 50, 300, 300);
    p.end();
    return img;
}
