#ifndef ISCAMERA_H
#define ISCAMERA_H

#include "abstractcamera.h"
#include <iostream>
#include <sstream>
#include "tisudshl.h"
#include <algorithm>

/**
 * @brief The IsCamera class, represent a Image Source Camera with all its settings
 */

class IsCamera : public AbstractCamera
{
    public:
        IsCamera();
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

};

#endif // FLYCAMERA_H
