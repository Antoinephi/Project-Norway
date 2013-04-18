#include "cameraproperty.h"

CameraProperty::CameraProperty(PropertyType type, double min, double max, double step, bool canAuto)
    :type(type), min(min), max(max), step(step), canAuto(canAuto) {

}
