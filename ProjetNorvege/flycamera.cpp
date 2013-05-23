#include "flycamera.h"
#include <QDebug>
#include <QPainter>
#include <QRgb>


FlyCamera::FlyCamera() : AbstractCamera()
{
    cam = new Camera();
    cam->StartCapture();
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
		prop.valueA = (int) p->getValue();
		prop.valueB = (int) p->getValue();
		
		cam->SetProperty(&prop);
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
    Image img;
    getCamera()->RetrieveBuffer(&img);
    unsigned char* picData = img.GetData();
    unsigned int x = img.GetCols();
    unsigned int y = img.GetRows();
    QImage image(x, y, QImage::Format_RGB32);
    for(unsigned int i = 0; i <y; i++){
        for(unsigned int j = 0; j <x; j++) {
            unsigned char data = picData[i*x+j];
            image.setPixel(j, i, qRgb(data, data, data));
		}
	}
	return image;
}


bool FlyCamera::equalsTo(AbstractCamera *c){
    return guid == *((FlyCamera *)c)->getGuid();
}





std::string FlyCamera::getString(){
	string name = FlyCamera::getCameraInfo()->modelName;
	ostringstream refTmp;
	refTmp << FlyCamera::getCameraInfo()->serialNumber;
	string ref = refTmp.str();

	return name + " - " + ref;
}

FlyCamera::~FlyCamera()
{
    //dtor
}


