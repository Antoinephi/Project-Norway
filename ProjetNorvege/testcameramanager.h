#ifndef TESTCAMERAMANAGER_H
#define TESTCAMERAMANAGER_H

#include "abstractcameramanager.h"

class TestCameraManager : public AbstractCameraManager {
    public:
        TestCameraManager();
        virtual std::string getName();
};

#endif // TESTCAMERAMANAGER_H
