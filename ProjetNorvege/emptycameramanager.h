#ifndef EMPTYCAMERAMANAGER_H
#define EMPTYCAMERAMANAGER_H


#include "abstractcameramanager.h"

class EmptyCameraManager : public AbstractCameraManager {
    public:
        EmptyCameraManager();
        virtual std::string getName();
};

#endif // EMPTYCAMERAMANAGER_H
