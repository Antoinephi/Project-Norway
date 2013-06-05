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
        case CameraManager::HUE : return "hue";
        case CameraManager::CROP : return "crop";
        case CameraManager::CROPX : return "cropX";
        case CameraManager::CROPY : return "cropY";
        case CameraManager::PAN : return "pan";
        case CameraManager::PANX : return "pan";
        case CameraManager::PANY : return "pan";
        case CameraManager::AUTOTRIGGER : return "automatic Trigger";
    }
    return "unknown type";
}
