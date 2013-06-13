#include "iscamera.h"
#include <QDebug>
#include <QPainter>
#include <QRgb>


IsCamera::IsCamera()
	: AbstractCamera(), capturing(false)
{
    
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


bool IsCamera::equalsTo(AbstractCamera *){
    return true; // TODO
}





std::string IsCamera::getString(){
	return "Imaging Source Camera";
}

IsCamera::~IsCamera()
{
    //dtor
}
