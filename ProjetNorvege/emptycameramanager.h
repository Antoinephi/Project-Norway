#ifndef EMPTYCAMERAMANAGER_H
#define EMPTYCAMERAMANAGER_H

#include "abstractcamera.h"
#include "abstractcameramanager.h"

class EmptyCameraManager : public AbstractCameraManager {
    public:
        EmptyCameraManager();
        virtual void detectNewCameras(std::vector<AbstractCamera*> *newCameras);
        virtual void getCamerasPropertiesList() const;
        virtual std::string getName() const;
};

#endif // EMPTYCAMERAMANAGER_H
