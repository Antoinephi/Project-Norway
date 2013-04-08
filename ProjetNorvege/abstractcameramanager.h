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
        AbstractCameraManager(bool first=false);
        QModelIndex addGroup();
        void detectNewCameras();
        //virtual void getCamerasPropertiesList() const = 0;
        virtual std::string getName() = 0;
        QStandardItemModel* getModel();
    protected:
        bool addNewCamera(std::string name, AbstractCamera *camera);
    private:
        QStandardItemModel cameraTree;
        QStandardItem newCameraList;

};

#endif // ABSTRACTCAMERAMANAGER_H
