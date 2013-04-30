#include "testcameramanager.h"
#include "testcamera.h"

TestCameraManager::TestCameraManager()
    : AbstractCameraManager(), foundCameras() {
    foundCameras.push_back(FoundCamera(new TestCamera(), "Camera1"));
    foundCameras.push_back(FoundCamera(new TestCamera(), "Camera2"));
    foundCameras.push_back(FoundCamera(new TestCamera(), "Camera3"));

	std::vector<CameraProperty> prop = std::vector<CameraProperty>();
    prop.push_back(CameraProperty(CameraManager::BRIGHTNESS, 0, 255, 1, true));
    prop.push_back(CameraProperty(CameraManager::GAIN, 0, 255, 1, true));
    prop.push_back(CameraProperty(CameraManager::EXPOSURE, 0, 255, 1, true));
    prop.push_back(CameraProperty(CameraManager::GAMMA, 0, 5, 0.01, false));
    prop.push_back(CameraProperty(CameraManager::SHUTTER, 0, 255, 1, true));
    for(int i=prop.size()-1; i>=0; i--){
        prop.at(i).setValue(0.0);
    }
	setProperties(prop);
}

void TestCameraManager::detectNewCameras(){
    for(unsigned int i=0; i < foundCameras.size(); i++)
        addNewCamera(foundCameras.at(i).name, foundCameras.at(i).camera);
}
void TestCameraManager::getCamerasPropertiesList() const{
    //Nothing here
}

std::string TestCameraManager::getName() const{
    return "TestManager";
}


