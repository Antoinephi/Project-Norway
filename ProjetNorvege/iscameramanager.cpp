#include "iscameramanager.h"
#include "iscamera.h"
#include <sstream>
#include <QImage>
#include <QProcess>
#include <QDebug>

using namespace std;
using namespace DShowLib;


IsCameraManager::IsCameraManager()
	: AbstractCameraManager()
{
	std::vector<CameraProperty> prop = std::vector<CameraProperty>();
    prop.push_back(CameraProperty(CameraManager::BRIGHTNESS, 0, 255, 0, true));
    prop.push_back(CameraProperty(CameraManager::GAIN, 0, (float) 12.041, 3, true));
    prop.push_back(CameraProperty(CameraManager::EXPOSURE, 0, 62, 0, true));

    for(int i=prop.size()-1; i>=0; i--){
        prop.at(i).setValue(0.0);
    }
	setProperties(prop);
}

IsCameraManager::~IsCameraManager()
{
    atexit(ExitLibrary);
}


void IsCameraManager::detectNewCameras(std::vector<AbstractCamera*> *newCameras)
{
    if(InitLibrary())
	{
		Grabber *grb = new Grabber();
		Grabber::tVidCapDevListPtr list = grb->getAvailableVideoCaptureDevices();
		
		for(int i = list->size()-1; i >= 0; i--){
			long long serialNum;
			IsCamera *cam = new IsCamera(grb, list->at(i));
			newCameras->push_back(cam);
		}
	}
}

string IsCameraManager::getName() const
{
    return "ImagingSource Camera Manager";
}


