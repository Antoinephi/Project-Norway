#ifndef TESTCAMERAMANAGER_H
#define TESTCAMERAMANAGER_H

#include "abstractcameramanager.h"

class TestCameraManager : public AbstractCameraManager {
    public:
        TestCameraManager();
        virtual void detectNewCameras();
        virtual void getCamerasPropertiesList() const;
        virtual std::string getName() const;
};

#endif // TESTCAMERAMANAGER_H
