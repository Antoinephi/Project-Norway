#include "emptycameramanager.h"

EmptyCameraManager::EmptyCameraManager()
    : /*AbstractCameraManager::*/AbstractCameraManager(true) {
}
void EmptyCameraManager::detectNewCameras(){
    //Nothing here
}
void EmptyCameraManager::getCamerasPropertiesList() const{
    //Nothing
}

std::string EmptyCameraManager::getName() const{
    return "Select";
}
