#include "cameraproperty.h"
#include <QDebug>
CameraProperty::CameraProperty(PropertyType type, double min, double max, double step, bool canAuto)
    :type(type), min(min), max(max), step(step), canAuto(canAuto) {

}

std::string CameraProperty::getName(){
    //qDebug() << type;
    switch (type){
    case BRIGHTNESS : return "brightness";
    case GAIN : return "gain";
    case EXPOSURE : return "exposure";
    case GAMMA : return "gamma";
    case SHUTTER : return "shutter";
    }
    return "unknown type"/*+type*/;
}
