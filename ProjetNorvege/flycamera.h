#ifndef FLYCAMERA_H
#define FLYCAMERA_H

#include "abstractcamera.h"
#include <iostream>

#if defined(WIN64) || defined(WIN32)
	#include "FlyCapture2.h"
#elif defined(__unix__)
	#include "flycapture/FlyCapture2.h"
#endif

using namespace FlyCapture2;



class FlyCamera : public AbstractCamera
{
    public:
        FlyCamera();
        virtual ~FlyCamera();
        Camera* getCamera();
        PGRGuid* getGuid();
        CameraInfo* getCameraInfo();
        void setProperty(CameraManager::CameraProperty *p);
        void updateProperty(CameraManager::CameraProperty *p);
        QImage retrieveImage();
        bool equalsTo(AbstractCamera *c);

    private:
        Camera* cam;
        PGRGuid guid;
        CameraInfo camInfo;
		Property getProperty(CameraManager::CameraProperty *p);

};

#endif // FLYCAMERA_H
