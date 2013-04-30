#ifndef ABSTRACTCAMERAMANAGER_H
#define ABSTRACTCAMERAMANAGER_H

#include <string>
#include <vector>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTreeWidget>
#include <QLabel>
#include "abstractcamera.h"
#include "cameraproperty.h"

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
        virtual std::string getName() const = 0;
        //do not reimplement
        QModelIndex detectNewCamerasAndExpand();
        void updateImages();
        void updateProperties();
        QModelIndex addGroup();
        void activateCamera(AbstractCamera* camera, QStandardItem* item, bool active);
        QString cameraTree_itemClicked(const QModelIndex & index);
        QStandardItemModel* getModel();
        QTreeWidget* getPropertiesWidget();
        void setMainWindow(MainWindow* window);        
    protected:
        AbstractCameraManager(bool empty=false);
        void setProperties(std::vector<CameraProperty> &properties);
        bool addNewCamera(std::string name, AbstractCamera *camera);
    private slots:
        void on_CameraTree_itemChanged(QStandardItem* item);
        void on_subwindow_closing(QObject* window);
        void on_propertyCheckbox_changed(int state);
        void on_propertySlider_changed(int val);
    private:
        MainWindow* mainWindow;
        QStandardItemModel cameraTree;
        QStandardItem newCameraList;
        QTreeWidget propertiesList;
        QStandardItem* selectedCamera;
        struct activeCameraEntry{
            activeCameraEntry(AbstractCamera *c, QStandardItem* i)
                : camera(c), window(new QMdiSubWindow()), treeItem(i){
                window->setAttribute(Qt::WA_DeleteOnClose);
                //window->setWindowFlags(window->windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
                window->setWindowFlags(Qt::Tool);
                window->setWidget(new QLabel());
            }
            //~activeCameraEntry(){ delete window; }
            AbstractCamera* camera;
            QStandardItem* treeItem;
            QMdiSubWindow* window;
        };
        std::vector<activeCameraEntry> activeCameras;
        std::vector<CameraProperty> cameraProperties;
        void cameraTree_recursiveCheck(QStandardItem* parent, Qt::CheckState checked);
        bool cameraTree_recursiveSearch(QStandardItem* parent, AbstractCamera* camera);
        QStandardItem* cameraTree_recursiveFirstCamera(QStandardItem* parent);
        AbstractCamera* getSelectedCamera();
};

#endif // ABSTRACTCAMERAMANAGER_H
