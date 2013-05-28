#include "testcamera.h"
#include <QPainter>
#include <QDebug>
#include <QThread>
#include <stdlib.h>

TestCamera::TestCamera(std::string n)
    : AbstractCamera(), n(n), capturing(false), framerate(5) {
    srand(42);
}

void TestCamera::setProperty(CameraManager::CameraProperty* p){
    //Nothing here
    qDebug() << "setProperty";
    if(p->getType() == CameraManager::FRAMERATE) framerate = p->getValue();
}
void TestCamera::updateProperty(CameraManager::CameraProperty* p){
    //Nothing here
    if(p->getType() == CameraManager::FRAMERATE) p->setValue(framerate);
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

void TestCamera::startAutoCapture(){
    capturing = true;
    qDebug() << "Starting autoCapture";
    while(capturing){
        QThread::msleep(1000/framerate);

        QImage img(400,400, QImage::Format_RGB32);
        img.fill(Qt::green);
        QPainter p;
        p.begin(&img);
        p.drawRect(1,1,397,397);
        p.drawRect(rand()%100, rand()%100,rand()%300, rand()%300);
        p.end();

        sendFrame(img);
    }
    qDebug() << "Stoped autoCapture !";
}

void TestCamera::stopAutoCapture(){
    qDebug() << "Stoping autoCapture";
    capturing = false;
}
