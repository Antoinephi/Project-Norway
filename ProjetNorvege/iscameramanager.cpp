#include "iscameramanager.h"
#include "iscamera.h"
#include <sstream>
#include <QImage>
#include <QProcess>

using namespace std;


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
    //dtor
}


void IsCameraManager::detectNewCameras(std::vector<AbstractCamera*> *newCameras)
{
    if( ! DShowLib::InitLibrary() )
	{
		return FALSE;
	}
 
	atexit( DShowLib::ExitLibrary );
}

void IsCameraManager::getCamerasPropertiesList() const
{
    //Nothing here
}

string IsCameraManager::getName() const
{
    return "FlyCapture Camera Manager";
}


