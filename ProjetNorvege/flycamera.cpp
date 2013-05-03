#include "flycamera.h"
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
    Property prop = getProperty(p);

    error = cam->GetProperty(&prop);
    if (error == PGRERROR_OK)
    {
		prop.autoManualMode = p->getAuto();
		prop.absValue = p->getValue();
    }
}
void FlyCamera::updateProperty(CameraManager::CameraProperty* p)
{
	Error error;
	Property prop = getProperty(p);

    error = cam->GetProperty(&prop);
    if (error == PGRERROR_OK)
    {
		p->setAuto(prop.autoManualMode);
		p->setValue(prop.absValue);
    }
}
Property FlyCamera::getProperty(CameraManager::CameraProperty* p)
{
	Property prop;

	switch(p->getType()){
	case CameraManager::BRIGHTNESS:
		prop.type = BRIGHTNESS;
		break;
	case CameraManager::EXPOSURE:
		prop.type = AUTO_EXPOSURE;
		break;
	case CameraManager::GAIN:
		prop.type = GAIN;
		break;
	case CameraManager::GAMMA:
		prop.type = GAMMA;
		break;
	case CameraManager::SHUTTER:
		prop.type = SHUTTER;
		break;
	}

	return prop;
}

QImage FlyCamera::retrieveImage(){
    getCamera()->StartCapture();
    Image img;
    getCamera()->RetrieveBuffer(&img);
    int size = img.GetDataSize();
    unsigned char* data = (unsigned char*) malloc(size * 3);
    unsigned char* picData = img.GetData();
    int j = 0;

    for(unsigned int i = 0; i<img.GetCols()  * img.GetRows() *3; i+=3)
    {
        data[i] = picData[j];
        data[i+1] = picData[j];
        data[i+2] = picData[j];
        j++;

    }

    QImage image(3, 3, QImage::Format_RGB32);
    QRgb value = qRgb(100,100,100);
    image.setPixel(1,1, value);
    return image;
}


bool FlyCamera::equalsTo(AbstractCamera *c){
    return guid == *((FlyCamera *)c)->getGuid();
}

FlyCamera::~FlyCamera()
{
    //dtor
}


