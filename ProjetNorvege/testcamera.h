#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include "abstractcamera.h"

class TestCamera : public AbstractCamera {
    public:
        TestCamera();
        void setProperty(CameraManager::CameraProperty* p);
        void updateProperty(CameraManager::CameraProperty* p);
        virtual QImage retrieveImage();
    private:
};

#endif // TESTCAMERA_H
