#include "flycameramanager.h"
#include "flycamera.h"
#include <QImage>
using namespace std;

FlyCameraManager::FlyCameraManager()
	: AbstractCameraManager()
{
    //ctor
}

FlyCameraManager::~FlyCameraManager()
{
    //dtor
}


void FlyCameraManager::detectNewCameras()
{
    busMgr.GetNumOfCameras(&numCameras);
    for(unsigned int i = 0; i<numCameras; i++){
        FlyCamera* flyCam = new FlyCamera();
        busMgr.GetCameraFromIndex(i, flyCam->getGuid());
        flyCam->getCamera()->Connect(flyCam->getGuid());
        flyCam->getCamera()->GetCameraInfo(flyCam->getCameraInfo());
        addNewCamera("cam" ,flyCam);

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


