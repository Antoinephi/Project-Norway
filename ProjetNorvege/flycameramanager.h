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
        virtual void detectNewCameras(std::vector<AbstractCamera*> *newCameras);
        std::string getName() const;
        void getCamerasPropertiesList() const;

        CircularBuffer** camBuffer;
        unsigned int numCameras;

    private:
    BusManager busMgr;
    Error error;
};

#endif // FLYCAMERAMANAGER_H
