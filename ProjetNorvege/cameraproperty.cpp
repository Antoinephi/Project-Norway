#include "cameraproperty.h"
#include <QDebug>


CameraProperty::CameraProperty(CameraManager::PropertyType type, double min, double max, double step, bool canAuto)
    :type(type), min(min), max(max), step(step), canAuto(canAuto) {

}

std::string CameraProperty::getName(){
    //qDebug() << type;
    switch (type){
    case CameraManager::BRIGHTNESS : return "brightness";
    case CameraManager::GAIN : return "gain";
    case CameraManager::EXPOSURE : return "exposure";
    case CameraManager::GAMMA : return "gamma";
    case CameraManager::SHUTTER : return "shutter";
    }
    return "unknown type"/*+type*/;
}
