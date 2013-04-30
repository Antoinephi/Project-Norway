#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H

#include <string>
#include <cmath>
#include <QString>

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
    CameraProperty(PropertyType type, double min, double max, int decimals = 0, bool canAuto = false);
    PropertyType getType(){ return type; }
    void setAuto(bool a){ isAuto = a; }
    bool getAuto(){ return isAuto; }
    bool getCanAuto(){ return canAuto; }
    void setValue(double value){ val = value; }
    double getValue(){ return val; }
    double getDecimals(){ return decimals; }

    void setValueFromSlider(int value){ val = value/pow(10, decimals); }
    int getValueToSlider(){ return val*pow(10, decimals); }
    int getMinToSlider(){ return min*pow(10, decimals); }
    int getMaxToSLider(){ return max*pow(10, decimals); }
    QString formatValue(){ return QString::number(val, 'f', decimals); }

    std::string getName();
private:
    PropertyType type;
    double min, max;
    int decimals;
    bool canAuto;

    double val;
    bool isAuto;
};

#endif // CAMERAPROPERTY_H
