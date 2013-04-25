#ifndef FLYCAMERAMANAGER_H
#define FLYCAMERAMANAGER_H
#include "flycapture/FlyCapture2.h"
#include "circularbuffer.h"
#include "flycamera.h"
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace FlyCapture2;

class FlyCameraManager
{
    public:
        FlyCameraManager();
        virtual ~FlyCameraManager();
        void PrintCameraInfo(CameraInfo*);
        void detectNewCameras();
        std::string getName();
        void disconnectAllCameras();
        void getPicture(unsigned int numCam);
        void takePicture(unsigned int numCam);
        void showCamera();
        void startCapture(int numCam);
        void stopCapture(int numCam);

        CircularBuffer** camBuffer;
        unsigned int numCameras;


//        struct myCamera{
//            public:
//            Camera* cam;
//            PGRGuid guid;
//            CameraInfo camInfo;
//        };

    protected:

    private:
    BusManager busMgr;
    Error error;
    std::vector<FlyCamera> flyCameras;


};

#endif // FLYCAMERAMANAGER_H
