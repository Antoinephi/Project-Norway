#include "flycameramanager.h"
#include "flycamera.h"
#include <sstream>
#include <QImage>
#include <QProcess>
using namespace std;

FlyCameraManager::FlyCameraManager()
	: AbstractCameraManager()
{
	#if defined(WIN32) || defined(WIN64)
		QProcess *myProcess = new QProcess(NULL);
		myProcess->start("PGRIdleStateFix.exe", QStringList("enable") );
	#endif

    std::vector<CameraProperty> prop = std::vector<CameraProperty>();
    prop.push_back(CameraProperty(CameraManager::BRIGHTNESS, 0, 255, 0, true));
    prop.push_back(CameraProperty(CameraManager::GAIN, 0, (float) 12.041, 3, true));
    prop.push_back(CameraProperty(CameraManager::EXPOSURE, 0, 62, 0, true));
    prop.push_back(CameraProperty(CameraManager::GAMMA, 0, 1, 0, false));
    prop.push_back(CameraProperty(CameraManager::SHUTTER, 0, (float) 33.174, 3, true));
    prop.push_back(CameraProperty(CameraManager::PAN, 0, 112, 0, true));
    prop.push_back(CameraProperty(CameraManager::FRAMERATE, 4, 30, 1, true));


    for(int i=prop.size()-1; i>=0; i--){
        prop.at(i).setValue(0.0);
    }
	setProperties(prop);
}

FlyCameraManager::~FlyCameraManager()
{
    //dtor
}


void FlyCameraManager::detectNewCameras(std::vector<AbstractCamera*> *newCameras)
{
    busMgr.GetNumOfCameras(&numCameras);
    for(unsigned int i = 0; i<numCameras; i++){
        FlyCamera* flyCam = new FlyCamera();
        busMgr.GetCameraFromIndex(i, flyCam->getGuid());
        flyCam->getCamera()->Connect(flyCam->getGuid());
        flyCam->getCamera()->GetCameraInfo(flyCam->getCameraInfo());
		
		newCameras->push_back(flyCam);
    }
}

void FlyCameraManager::getCamerasPropertiesList() const
{
    //Nothing here
}

string FlyCameraManager::getName() const
{
    return "FlyCapture Camera Manager";
}


