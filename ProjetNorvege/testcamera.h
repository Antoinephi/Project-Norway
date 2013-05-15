#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include "abstractcamera.h"

class TestCamera : public AbstractCamera {
    public:
<<<<<<< HEAD
        TestCamera();
        void setProperty(CameraManager::CameraProperty* p);
        void updateProperty(CameraManager::CameraProperty* p);
=======
        TestCamera(std::string n);
        void setProperty(CameraProperty* p);
        void updateProperty(CameraProperty* p);
        virtual std::string getString(){ return n; }
>>>>>>> origin/QT_only
        virtual QImage retrieveImage();
    private:
        std::string n;
};

#endif // TESTCAMERA_H
