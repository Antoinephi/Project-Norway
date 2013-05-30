#ifndef ISCAMERA_H
#define ISCAMERA_H

#include "abstractcamera.h"
#include <iostream>
#include <sstream>

#if defined(WIN64) || defined(WIN32)
	#include "FlyCapture2.h"
#elif defined(__unix__)
	#include "flycapture/FlyCapture2.h"
#endif

using namespace FlyCapture2;
using namespace std;

/**
 * @brief The IsCamera class, represent a Image Source Camera with all its settings
 */

class IsCamera : public AbstractCamera
{
    public:
        IsCamera();
        virtual ~IsCamera();

        Camera* getCamera();
        
        PGRGuid* getGuid();
        
        CameraInfo* getCameraInfo();

        void setProperty(CameraManager::CameraProperty *p);

        void updateProperty(CameraManager::CameraProperty *p);

		void startAutoCapture();
        void stopAutoCapture();
		void sendFrame(QImage img);

        QImage retrieveImage();
        
        bool equalsTo(AbstractCamera *c);
        
		std::string getString();

    private:
        /**
         * @brief cam object that represent the camera
         */
        Camera* cam;
        /**
         * @brief guid : unique ID for each camera
         */
        PGRGuid guid;
        /**
         * @brief camInfo : object that gather all camera informations (model name, serial number, ...)
         */
        CameraInfo camInfo;
        /**
         * @brief getPropertyType
         * @param p
         * @return
         */
		FlyCapture2::PropertyType getPropertyType(CameraManager::CameraProperty *p);

		
        bool capturing;

};

#endif // FLYCAMERA_H
