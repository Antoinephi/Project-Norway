#ifndef ABSTRACTCAMERAMANAGER_H
#define ABSTRACTCAMERAMANAGER_H

#include <string>
#include <vector>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMdiArea>
#include <QMdiSubWindow>
#include "abstractcamera.h"

class MainWindow;


enum MyRoles {
    CameraGroupRole = Qt::UserRole + 1,
    CameraRole = Qt::UserRole + 1
};

class AbstractCameraManager : public QObject
{
    Q_OBJECT
    public:
        // Pure virtual -> to implement
        virtual void detectNewCameras() = 0;
        virtual void getCamerasPropertiesList() const = 0;
        virtual std::string getName() const = 0;
        //do not reimplement
        QModelIndex detectNewCamerasAndExpand();
        QModelIndex addGroup();
        void activateCamera(AbstractCamera* camera, QStandardItem* item, bool active);
        QStandardItemModel* getModel();
        void setMainWindow(MainWindow* window);
    protected:
        AbstractCameraManager(bool empty=false);
        bool addNewCamera(std::string name, AbstractCamera *camera);
    private slots:
        void on_CameraTree_itemChanged(QStandardItem* item);
        void on_subwindow_closing(QObject* window);
    private:
        MainWindow* mainWindow;
        QStandardItemModel cameraTree;
        QStandardItem newCameraList;
        struct activeCameraEntry{
            activeCameraEntry(AbstractCamera *c, QStandardItem* i)
                : camera(c), window(new QMdiSubWindow()), treeItem(i){
                window->setAttribute(Qt::WA_DeleteOnClose);
                window->setWindowFlags(window->windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
            }
            //~activeCameraEntry(){ delete window; }
            AbstractCamera* camera;
            QStandardItem* treeItem;
            QMdiSubWindow* window;
        };
        std::vector<activeCameraEntry> activeCameras;
        void cameraTree_recursiveCheck(QStandardItem* parent, Qt::CheckState checked);
        bool cameraTree_recursiveSearch(QStandardItem* parent, AbstractCamera* camera);

};

#endif // ABSTRACTCAMERAMANAGER_H
