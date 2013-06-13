#ifndef ISCAMERA_H
#define ISCAMERA_H

#include "abstractcamera.h"
#include <iostream>
#include <sstream>
#include "tisudshl.h"
#include <algorithm>

using namespace DShowLib;

/**
 * @brief The IsCamera class, represent a Image Source Camera with all its settings
 */

class IsCamera : public AbstractCamera
{
    public:
        IsCamera(Grabber*, VideoCaptureDeviceItem);
        virtual ~IsCamera();



        void setProperty(CameraManager::CameraProperty *p);

        void updateProperty(CameraManager::CameraProperty *p);

		void startAutoCapture();
        void stopAutoCapture();
		void sendFrame(QImage img);

        QImage retrieveImage();
        
        bool equalsTo(AbstractCamera *c);
        
		std::string getString();

    private:		
        bool capturing;
		VideoCaptureDeviceItem device;
		Grabber *grabber;
		long long serialNum;
};

#endif // FLYCAMERA_H
