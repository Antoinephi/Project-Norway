#include "flycamera.h"
#include <QDebug>
#include <QPainter>
#include <QRgb>

FlyCamera::FlyCamera() : AbstractCamera()
{
    cam = new Camera();
}

Camera* FlyCamera::getCamera()
{
    return cam;
}

PGRGuid* FlyCamera::getGuid()
{
    return &guid;
}

CameraInfo* FlyCamera::getCameraInfo()
{
    return &camInfo;
}

void FlyCamera::setProperty(CameraManager::CameraProperty* p)
{
    Error error;
	Property prop;
	prop.type = getPropertyType(p);
	
    error = cam->GetProperty(&prop);
    if (error == PGRERROR_OK)
    {
		prop.autoManualMode = p->getAuto();

		if(p->getDecimals() > 0)
			prop.absValue = p->getValue();
		else
			prop.valueA = (int) p->getValue();
		
		cam->SetProperty(&prop);
		qDebug() << "set " << p->getName().c_str() << " : " << (p->getDecimals() > 0 ? prop.absValue : prop.valueA);;
    }
}
void FlyCamera::updateProperty(CameraManager::CameraProperty* p)
{
	Error error;
	Property prop;
	prop.type = getPropertyType(p);

    error = cam->GetProperty(&prop);
    if (error == PGRERROR_OK)
    {
		p->setAuto(prop.autoManualMode);
		p->setValue(p->getDecimals() > 0 ? prop.absValue : prop.valueA);
		qDebug() << "get " << p->getName().c_str() << " : " << (p->getDecimals() > 0 ? prop.absValue : prop.valueA);
    }
}
FlyCapture2::PropertyType FlyCamera::getPropertyType(CameraManager::CameraProperty* p)
{
	switch(p->getType()){
	case CameraManager::BRIGHTNESS:
		return BRIGHTNESS;
		break;
	case CameraManager::EXPOSURE:
		return AUTO_EXPOSURE;
		break;
	case CameraManager::GAIN:
		return GAIN;
		break;
	case CameraManager::GAMMA:
		return GAMMA;
		break;
	case CameraManager::SHUTTER:
		return SHUTTER;
		break;
	}
}

QImage FlyCamera::retrieveImage(){


    getCamera()->StartCapture();
    Image img;
    getCamera()->RetrieveBuffer(&img);
    int size = img.GetDataSize();

    unsigned char* picData = img.GetData();
    QImage image(img.GetCols(), img.GetRows(), QImage::Format_RGB32);
	for(unsigned int i = 0; i <img.GetCols(); i++){
		for(unsigned int j = 0; j <img.GetRows(); j++) {
			image.setPixel(i, j, picData[i*img.GetRows()+j]);
		}
	}
	
	return image;
}


bool FlyCamera::equalsTo(AbstractCamera *c){
    return guid == *((FlyCamera *)c)->getGuid();
}

FlyCamera::~FlyCamera()
{
    //dtor
}


