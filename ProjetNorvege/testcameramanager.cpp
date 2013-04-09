#include "testcameramanager.h"
#include "testcamera.h"

TestCameraManager::TestCameraManager()
    : AbstractCameraManager::AbstractCameraManager(), foundCameras() {
    foundCameras.push_back(FoundCamera(new TestCamera(), "Camera1"));
    foundCameras.push_back(FoundCamera(new TestCamera(), "Camera2"));
    foundCameras.push_back(FoundCamera(new TestCamera(), "Camera3"));
}

void TestCameraManager::detectNewCameras(){
    for(int i=0; i<foundCameras.size(); i++)
        addNewCamera(foundCameras.at(i).name, foundCameras.at(i).camera);
}
void TestCameraManager::getCamerasPropertiesList() const{
    //Nothing here
}

std::string TestCameraManager::getName() const{
    return "TestManager";
}


