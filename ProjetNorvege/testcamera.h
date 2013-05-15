#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include "abstractcamera.h"

class TestCamera : public AbstractCamera {
    public:
        TestCamera(std::string n);
        void setProperty(CameraProperty* p);
        void updateProperty(CameraProperty* p);
        virtual std::string getString(){ return n; }
        virtual QImage retrieveImage();
    private:
        std::string n;
};

#endif // TESTCAMERA_H
