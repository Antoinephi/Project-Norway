#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include "abstractcamera.h"

class TestCamera : public AbstractCamera {
    public:
        TestCamera();
        void setProperty(CameraProperty* p);
        void updateProperty(CameraProperty* p);
    private:
};

#endif // TESTCAMERA_H
