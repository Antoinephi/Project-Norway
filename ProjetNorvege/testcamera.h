#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include "abstractcamera.h"

class TestCamera : public AbstractCamera {
    public:
        TestCamera();
        virtual /**/void getProperty(/**/);
    private:
};

#endif // TESTCAMERA_H
