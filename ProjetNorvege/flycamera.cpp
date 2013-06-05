#include "flycamera.h"
#include <QDebug>
#include <QPainter>
#include <QRgb>


FlyCamera::FlyCamera()
	: AbstractCamera(), capturing(false)
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
    case CameraManager::PAN:
        return PAN;
        break;
    case CameraManager::FRAMERATE:
        return FRAME_RATE;
        break;
	}

	return BRIGHTNESS;
}


void FlyCamera::startAutoCapture(){
    capturing = true;
    qDebug() << "Starting autoCapture";
	getCamera()->StartCapture();

	Image img;

    while(capturing){
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

		AbstractCamera::sendFrame(image);
    }
    qDebug() << "Stoped autoCapture !";
}

void FlyCamera::stopAutoCapture(){
    qDebug() << "Stoping autoCapture";
    capturing = false;
	getCamera()->StopCapture();
}

QImage FlyCamera::retrieveImage()
{
    Image img;
	getCamera()->StartCapture();
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
	getCamera()->StopCapture();
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


