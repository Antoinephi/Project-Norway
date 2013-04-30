#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H

#include <string>
#include <cmath>
#include <QString>


namespace CameraManager {
	class CameraProperty;

	enum PropertyType {
		BRIGHTNESS,
		GAIN,
		EXPOSURE,
		GAMMA,
		SHUTTER
	};
}

class CameraProperty
{
public:
	CameraProperty(CameraManager::PropertyType type, double min, double max, double step = 1, bool canAuto = false);
	CameraManager::PropertyType getType(){ return type; }
	void setAuto(bool a){ isAuto = a; }
    bool getAuto(){ return isAuto; }
    bool getCanAuto(){ return canAuto; }
    void setValue(double value){ val = value; }
    double getValue(){ return val; }
    double getStep(){ return step; }
    double getPrecision(){ return (step>=1)? (0) : ceil(-log10(step)); }
    QString formatValue(){ return QString::number(val, 'f', getPrecision()); }
    std::string getName();
private:
	CameraManager::PropertyType type;
	double min, max, step;
	bool canAuto;

	double val;
	bool isAuto;
};

#endif // CAMERAPROPERTY_H
