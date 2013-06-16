#include "iscamera.h"
#include "SimplePropertyAccess.h"
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QRgb>
#include <iostream>


using namespace DShowLib;


IsCamera::IsCamera(Grabber *grb, VideoCaptureDeviceItem deviceItem)
	: AbstractCamera(), grabber(grb), device(deviceItem), capturing(false)
{
	device.getSerialNumber(serialNum);
}

void IsCamera::setProperty(CameraManager::CameraProperty* p)
{
    if(grabber->openDev(device))
	{
		CSimplePropertyAccess prop = grabber->getAvailableVCDProperties();
		
		if(prop.isAvailable(getPropertyType(p)))
		{
			prop.setAuto(getPropertyType(p), p->getAuto());
			prop.setValue(getPropertyType(p), p->getValue());
		}

		grabber->closeDev();
	}
}
void IsCamera::updateProperty(CameraManager::CameraProperty* p)
{
	if(grabber->openDev(device))
	{
		CSimplePropertyAccess prop = grabber->getAvailableVCDProperties();
		
		if(prop.isAvailable(getPropertyType(p)))
		{
			p->setAuto(prop.getAuto(getPropertyType(p)));
			p->setValue(prop.getValue(getPropertyType(p)));
		}

		grabber->closeDev();
	}
}


GUID IsCamera::getPropertyType(CameraManager::CameraProperty* p)
{
	switch(p->getType()){
	case CameraManager::GAIN:
		return VCDID_Gain;
	case CameraManager::EXPOSURE:
		return VCDID_Exposure;
    case CameraManager::AUTOTRIGGER:
        return VCDID_Trigger;
	}

	return VCDID_Brightness;
}


void IsCamera::startAutoCapture(){
    capturing = true;
    qDebug() << "Starting autoCapture";

	while(capturing){
		AbstractCamera::sendFrame(retrieveImage());
    }
    qDebug() << "Stoped autoCapture !";
}

void IsCamera::stopAutoCapture(){
    qDebug() << "Stoping autoCapture";
    capturing = false;
}

QImage IsCamera::retrieveImage()
{
	if(grabber->openDev(device))
	{
		MemBufferCollection::tMemBufferPtr pActiveBuf = getSingleFrame(*grabber, eRGB24);

		struct RGB24Pixel {
			BYTE b;
			BYTE g;
			BYTE r;
		};
		RGB24Pixel* picData = (RGB24Pixel*) pActiveBuf->getPtr();
		SIZE dim = pActiveBuf->getFrameType().dim;

		unsigned int x = dim.cx;
		unsigned int y = dim.cy;
		QImage image(x, y, QImage::Format_RGB32);
		for(int i = y-1; i >= 0; i--){
			for(int j = 0; j <x; j++) {
				RGB24Pixel data = picData[i*x+j];
				image.setPixel(j, y-i, qRgb(data.r, data.g, data.b));
			}
		}

		grabber->closeDev();

		return image;
	}
	return QImage();
}

MemBufferCollection::tMemBufferPtr IsCamera::getSingleFrame(Grabber& gr, tColorformatEnum type)
{
	smart_ptr<FrameHandlerSink> pHandlerSink = FrameHandlerSink::create( type, 1 );
	pHandlerSink->setSnapMode( true );

	gr.setSinkType( pHandlerSink );

	gr.startLive( false );
	Sleep( 250 ); // give the device time to adjust automatic settings i.e. auto exposure
	pHandlerSink->snapImages( 1, 2000 );
	gr.stopLive();

	// get pointer to the image data
	return pHandlerSink->getLastAcqMemBuffer();
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
