#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H

#include <string>

enum PropertyType {
    BRIGHTNESS,
    GAIN,
    EXPOSURE,
    GAMMA,
    SHUTTER
};

class CameraProperty
{
public:
    CameraProperty(PropertyType type, double min, double max, double step = 1, bool canAuto = false);
    PropertyType getType(){ return type; }
    void setAuto(bool a){ isAuto = a; }
    bool getAuto(){ return isAuto; }
    bool getCanAuto(){ return canAuto; }
    void setValue(double value){ val = value; }
    double getValue(){ return val; }
    std::string getName();
private:
    PropertyType type;
    double min, max, step;
    bool canAuto;

    double val;
    bool isAuto;
};

#endif // CAMERAPROPERTY_H
