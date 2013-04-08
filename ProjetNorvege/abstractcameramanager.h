#ifndef ABSTRACTCAMERAMANAGER_H
#define ABSTRACTCAMERAMANAGER_H

#include <string>
#include <QStandardItemModel>
#include "abstractcamera.h"

enum MyRoles {
    CameraGroupRole = Qt::UserRole + 1,
    CameraRole = Qt::UserRole + 1
};

class AbstractCameraManager
{
    public:
        // Pure virtual
        virtual void detectNewCameras() = 0;
        virtual void getCamerasPropertiesList() const = 0;
        virtual std::string getName() const = 0;
        //do not reimplement
        QModelIndex addGroup();
        QStandardItemModel* getModel();
    protected:
        AbstractCameraManager(bool first=false);
        bool addNewCamera(std::string name, AbstractCamera *camera);
    private:
        QStandardItemModel cameraTree;
        QStandardItem newCameraList;

};

#endif // ABSTRACTCAMERAMANAGER_H
