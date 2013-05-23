#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include "abstractcamera.h"

using namespace CameraManager;

class TestCamera : public AbstractCamera {
    public:
        TestCamera(std::string n);
        void setProperty(CameraManager::CameraProperty* p);
        void updateProperty(CameraManager::CameraProperty* p);
        virtual std::string getString(){ return n; }
        virtual QImage retrieveImage();
    private:
        std::string n;
};

#endif // TESTCAMERA_H
