#ifndef FLYCAMERAMANAGER_H
#define FLYCAMERAMANAGER_H

#include "circularbuffer.h"
#include "flycamera.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "abstractcamera.h"
#include "abstractcameramanager.h"

using namespace FlyCapture2;



class FlyCameraManager
	: public AbstractCameraManager
{
    public:
        FlyCameraManager();
        virtual ~FlyCameraManager();
        void PrintCameraInfo(CameraInfo*);
        void detectNewCameras();
        std::string getName() const;
        void getCamerasPropertiesList() const;
        void disconnectAllCameras();
        void getPicture(unsigned int numCam);
        void takePicture(unsigned int numCam);
        void showCamera();
        void startCapture(int numCam);
        void stopCapture(int numCam);

        CircularBuffer** camBuffer;
        unsigned int numCameras;

    private:
    BusManager busMgr;
    Error error;
    std::vector<FlyCamera> flyCameras;
};

#endif // FLYCAMERAMANAGER_H
