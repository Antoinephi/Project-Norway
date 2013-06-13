#ifndef ISCAMERAMANAGER_H
#define ISAMERAMANAGER_H

#include "iscamera.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "abstractcamera.h"
#include "abstractcameramanager.h"

/**
 * @brief The IsCameraManager class deals with all the Imaging Source Cameras
 */

class IsCameraManager
	: public AbstractCameraManager
{
    public:
        IsCameraManager();
        virtual ~IsCameraManager();
        virtual void detectNewCameras(std::vector<AbstractCamera*> *newCameras);
        std::string getName() const;
        void getCamerasPropertiesList() const;

        unsigned int numCameras;

    private:
};

#endif // ISCAMERAMANAGER_H
