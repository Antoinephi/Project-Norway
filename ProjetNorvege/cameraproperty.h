#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H

#include <string>
#include <cmath>
#include <QString>

namespace CameraManager {

	enum PropertyType {
        BRIGHTNESS,
        HUE,
        GAIN,
        EXPOSURE,
        GAMMA,
        SHUTTER,
        FRAMERATE,
        CROPX,
        CROPY,
        CROP,
        PANX,
        PANY,
        PAN
    };


    class CameraProperty
	{
	public:
		CameraProperty(PropertyType type, float min, float max, int decimals = 0, bool canAuto = false);
		PropertyType getType(){ return type; }
		void setAuto(bool a){ isAuto = a; }
		bool getAuto(){ return isAuto; }
		bool getCanAuto(){ return canAuto; }
		void setValue(float value){ val = value; }
		float getValue(){ return val; }
		float getDecimals(){ return decimals; }

		void setValueFromSlider(int value){ val = value/pow(10, (double) decimals); }
		int getValueToSlider(){ return val*pow(10, (double) decimals); }
		int getMinToSlider(){ return min*pow(10, (double) decimals); }
		int getMaxToSLider(){ return max*pow(10, (double) decimals); }
		QString formatValue(){ return QString::number(val, 'f', decimals); }

		std::string getName();
	private:
		PropertyType type;
		float min, max;
		int decimals;
		bool canAuto;

		float val;
		bool isAuto;
	};
}

#endif // CAMERAPROPERTY_H
