/**
 * AbstractCameraManager
 * Class that need to be subclassed for each camera API
 * used to list and display Cameras, properties and liveview
 */
#ifndef ABSTRACTCAMERAMANAGER_H
#define ABSTRACTCAMERAMANAGER_H

#include <string>
#include <vector>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTreeWidget>
#include <QThread>
#include <QDebug>
#include "mainwindow.h"
#include "qvideowidget.h"
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
        /**
         * @brief detectNewCameras (Pure virtual) detect new cameras
         * @param newCameras wich will need to be filled with all the camera connected to the computer
         */
        virtual void detectNewCameras(std::vector<AbstractCamera*> *newCameras) = 0;

        /**
         * @brief getName (Pure virtual) get the name of the Manager
         * @return String containing the name manager
         */
        virtual std::string getName() const = 0;

        //do not reimplement
        /**
         * @brief detectNewCamerasAndExpand detect new cameras
         * @return the index in the model corresponding to the "Detected Cameras" group, in order to expand it in the view
         */
        QModelIndex detectNewCamerasAndExpand();

        //may be changed
        void updateImages();
        void updateProperties();

        /**
         * @brief addGroup add a empty group of cameras in the model
         * @return the index in the model corresponding to this group, in order to select it
         */
        QModelIndex addGroup();

        /**
         * @brief removeGroup remove a group from the model
         * @param index of the item to remove
         */
        void removeGroup(QModelIndex index);

        /**
         * @brief activateCamera check the camera in the model, add it in the activeCameras vector and open a subwindow for it
         * @param camera pointer to the camera to add
         * @param item position of the camera in the model
         * @param active true to activate, false to desactivate
         */
        void activateCamera(AbstractCamera* camera, QStandardItem* item, bool active);

        /**
         * @brief desactiveAllCameras used to close all liveviews from this manager
         */
        void desactiveAllCameras();

        /**
         * @brief cameraTree_itemClicked select a camera or a group to edit its properties
         * @param index index of the item in the model
         * @param string desccritive of the item
         * @param icon corresponding to the type of element selected
         * @param editable true if the item is editable
         * @param deletable true if the item is deletable
         */
        void cameraTree_itemClicked(const QModelIndex & index, QString &string, int &icon, bool &editable, bool &deleteable);

        void activateLiveView(bool active);

        /**
         * @brief getModel get the model ( camera list )
         * @return pointer to the model
         */
        QStandardItemModel* getModel();

        /**
         * @brief getPropertiesWidget get the model of the properties
         * @return pointer to the widget
         */
        QTreeWidget* getPropertiesWidget();

        /**
         * @brief setMainWindow to set the needed cross reference
         * @param window pointer to the main window
         */
        void setMainWindow(MainWindow* window);        
    protected:
        /**
         * @brief AbstractCameraManager constructor
         * @param empty true if the manager is an emty manager
         */
        AbstractCameraManager(bool empty=false);
        /**
         * @brief setProperties add properties tha can be set and retrieved to/from  cameras for this API
         * @param properties vector of CameraProperty
         */
        void setProperties(std::vector<CameraManager::CameraProperty> &properties);
    private slots:
        void on_CameraTree_itemChanged(QStandardItem* item);
        void on_subwindow_closing(QObject* window);
        void on_propertyCheckbox_changed(int state);
        void on_propertySlider_changed(int val);
    private:
        MainWindow* mainWindow;
        bool liveView;
        QStandardItemModel cameraTree;
        QStandardItem newCameraList;
        QTreeWidget propertiesList;
        QStandardItem* selectedItem;
        AbstractCamera* selectedCamera;
        QIcon folderIcon;
        struct activeCameraEntry{ public:
            activeCameraEntry(AbstractCamera *c, QStandardItem* i)
                : camera(c), treeItem(i), window(new QMdiSubWindow()) {
                window->setAttribute(Qt::WA_DeleteOnClose);
                window->setWindowFlags(Qt::Tool);
                QVideoWidget* videoWidget = new QVideoWidget();
                videoWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
                window->setWidget(videoWidget);
                window->resize(400, 300);
                QObject::connect(window, SIGNAL(windowStateChanged(Qt::WindowStates, Qt::WindowStates)),
                                 videoWidget, SLOT(changedState(Qt::WindowStates, Qt::WindowStates)) );
            }
            //~activeCameraEntry(){ delete window; }
            AbstractCamera* camera;
            QStandardItem* treeItem;
            QMdiSubWindow* window;
        };
        std::vector<activeCameraEntry> activeCameras;
        std::vector<CameraManager::CameraProperty> cameraProperties;
        void cameraTree_recursiveCheck(QStandardItem* parent, Qt::CheckState checked);
        QStandardItem* cameraTree_recursiveFirstCamera(QStandardItem* parent);
        void cameraTree_recursiveSetProperty(QStandardItem* parent, CameraManager::CameraProperty* prop);
        void cameraTree_getCameraList(QStandardItem* parent, std::vector<QStandardItem*> *list);
        AbstractCamera* getSelectedCamera();
};

#endif // ABSTRACTCAMERAMANAGER_H
