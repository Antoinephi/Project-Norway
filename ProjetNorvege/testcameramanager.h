#ifndef TESTCAMERAMANAGER_H
#define TESTCAMERAMANAGER_H

#include <vector>
#include <string>
#include "abstractcamera.h"
#include "abstractcameramanager.h"

class TestCameraManager : public AbstractCameraManager {
    public:
        TestCameraManager();
        virtual void detectNewCameras();
        virtual void getCamerasPropertiesList() const;
        virtual std::string getName() const;
    private:
        struct FoundCamera{
            FoundCamera(AbstractCamera* c, std::string n)
                :camera(c), name(n){}
            AbstractCamera* camera;
            std::string name;
        };
        std::vector<FoundCamera> foundCameras;
};

#endif // TESTCAMERAMANAGER_H
