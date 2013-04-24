#ifndef FLYCAMERA_H
#define FLYCAMERA_H
#include "flycapture/FlyCapture2.h"


using namespace FlyCapture2;

class FlyCamera
{
    public:
        FlyCamera();
        virtual ~FlyCamera();
        Camera* getCamera();
        PGRGuid* getGuid();
        CameraInfo* getCameraInfo();

    protected:

    private:
        Camera* cam;
        PGRGuid guid;
        CameraInfo camInfo;

};

#endif // FLYCAMERA_H
