#ifndef EMPTYCAMERAMANAGER_H
#define EMPTYCAMERAMANAGER_H

#include "abstractcameramanager.h"

class EmptyCameraManager : public AbstractCameraManager {
    public:
        EmptyCameraManager();
        virtual void detectNewCameras();
        virtual void getCamerasPropertiesList() const;
        virtual std::string getName() const;
};

#endif // EMPTYCAMERAMANAGER_H
