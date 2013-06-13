#include "iscamera.h"
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QRgb>


IsCamera::IsCamera(Grabber *grb, VideoCaptureDeviceItem deviceItem)
	: AbstractCamera(), grabber(grb), device(deviceItem), capturing(false)
{
	device.getSerialNumber(serialNum);
}

void IsCamera::setProperty(CameraManager::CameraProperty*)
{
    
}
void IsCamera::updateProperty(CameraManager::CameraProperty*)
{
	
}


void IsCamera::startAutoCapture(){
    
}

void IsCamera::stopAutoCapture(){
    
}

QImage IsCamera::retrieveImage()
{
    return QImage();
}


bool IsCamera::equalsTo(AbstractCamera *c){
	return this->serialNum == ((IsCamera*)c)->serialNum;
}





std::string IsCamera::getString(){
	return QString("Imaging Source Camera - %1").arg(serialNum).toLocal8Bit().constData();
}

IsCamera::~IsCamera()
{
    //dtor
}
