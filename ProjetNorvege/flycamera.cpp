#include "flycamera.h"



FlyCamera::FlyCamera()
{
    cam = new Camera();

    }

 Camera* FlyCamera::getCamera() {
    return cam;
}

 PGRGuid* FlyCamera::getGuid(){
    return &guid;
}

CameraInfo* FlyCamera::getCameraInfo(){
    return &camInfo;
}

FlyCamera::~FlyCamera()
{
    //dtor
}
