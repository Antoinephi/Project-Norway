#include "testcameramanager.h"
#include "testcamera.h"

TestCameraManager::TestCameraManager()
    : AbstractCameraManager::AbstractCameraManager() {
    addNewCamera("Camera1", new TestCamera());
    addNewCamera("Camera2", new TestCamera());
    addNewCamera("Camera3", new TestCamera());
}

void TestCameraManager::detectNewCameras(){
    //Nothing here
}
void TestCameraManager::getCamerasPropertiesList() const{
    //Nothing here
}

std::string TestCameraManager::getName() const{
    return "TestManager";
}


