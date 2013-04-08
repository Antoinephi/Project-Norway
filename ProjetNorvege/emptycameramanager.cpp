#include "emptycameramanager.h"

EmptyCameraManager::EmptyCameraManager()
    : AbstractCameraManager::AbstractCameraManager(true) {
}
std::string EmptyCameraManager::getName(){
    return "Select";
}
