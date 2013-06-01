#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include <string>
#include <QImage>
#include "abstractcamera.h"

using namespace CameraManager;

class TestCamera : public AbstractCamera {
    public:
        TestCamera(std::string n);
        void setProperty(CameraProperty* p);
        void updateProperty(CameraProperty* p);
        std::string getString(){ return n; }
        QImage retrieveImage();
        void startAutoCapture();
        void stopAutoCapture();
    private:
        std::string n;
        bool capturing;
        int framerate, brightness, crop;
        QImage back;

        QImage generateImage();
        void generateBack();
};

#endif // TESTCAMERA_H
