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
		prop.absValue = p->getValue();
		qDebug() << "set " << p->getName().c_str() << " : " << prop.absValue;
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
		p->setValue(prop.absValue);
		qDebug() << "get " << p->getName().c_str() << " : " << prop.absValue;
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

QImage FlyCamera::retrieveImage()
{
    getCamera()->StartCapture();
    Image img;
    getCamera()->RetrieveBuffer(&img);
    unsigned char* picData = img.GetData();
    unsigned int x = img.GetCols();
    unsigned int y = img.GetRows();
    QImage image(x, y, QImage::Format_RGB32);
    for(unsigned int i = 0; i <x; i++){
        for(unsigned int j = 0; j <y; j++) {
            unsigned char data = picData[i*x+j];
            image.setPixel(i, j, qRgb(data, data, data));
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


