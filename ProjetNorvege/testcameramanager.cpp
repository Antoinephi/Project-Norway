#include "testcameramanager.h"
#include "testcamera.h"

TestCameraManager::TestCameraManager()
    : AbstractCameraManager::AbstractCameraManager() {
    addNewCamera("Camera1", new TestCamera());
    addNewCamera("Camera2", new TestCamera());
    addNewCamera("Camera3", new TestCamera());
}

std::string TestCameraManager::getName(){
    return "TestManager";
}
