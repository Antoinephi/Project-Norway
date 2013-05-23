#ifndef FLYCAMERA_H
#define FLYCAMERA_H

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
 * @brief The FlyCamera class, represent a FlyCapture Camera with all its settings
 */

class FlyCamera : public AbstractCamera
{
    public:
        FlyCamera();
        virtual ~FlyCamera();

        /**
         * @brief getCamera returns a camera object that correspond to a physical camera
         * @return Camera
         */
        Camera* getCamera();
        /**
         * @brief getGuid returns the unique number associated to a camera
         * @return PGRGuid
         */
        PGRGuid* getGuid();
        /**
         * @brief getCameraInfo returns an object that contains all cameras informations
         * @return CameraInfo
         */
        CameraInfo* getCameraInfo();

        void setProperty(CameraManager::CameraProperty *p);

        void updateProperty(CameraManager::CameraProperty *p);
        /**
         * @brief retrieveImage capture one image from the camera and convert it in QImage 32bits image
         * @return QImage
         */
        QImage retrieveImage();
        /**
         * @brief equalsTo
         * @param c
         * @return bool
         */
        bool equalsTo(AbstractCamera *c);
        /**
         * @brief getString return the type of Camera (Fly Capture Camera here)
         * @return String
         */
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

};

#endif // FLYCAMERA_H
