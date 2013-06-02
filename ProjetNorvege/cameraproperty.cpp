#include "cameraproperty.h"
#include <QDebug>

using namespace CameraManager;

CameraProperty::CameraProperty(CameraManager::PropertyType type, float min, float max, int decimals, bool canAuto)
    :type(type), min(min), max(max), decimals(decimals), canAuto(canAuto) {

}

std::string CameraProperty::getName(){
    //qDebug() << type;
    switch (type){
        case CameraManager::BRIGHTNESS : return "brightness";
        case CameraManager::GAIN : return "gain";
        case CameraManager::EXPOSURE : return "exposure";
        case CameraManager::GAMMA : return "gamma";
        case CameraManager::SHUTTER : return "shutter";
        case CameraManager::FRAMERATE : return "framerate";
        case CameraManager::CROP : return "crop";
        case CameraManager::HUE : return "hue";
    }
    return "unknown type";
}
