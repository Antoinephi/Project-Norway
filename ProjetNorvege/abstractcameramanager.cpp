#include "abstractcameramanager.h"
#include "mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <algorithm>
Q_DECLARE_METATYPE(AbstractCamera *)

AbstractCameraManager::AbstractCameraManager(bool empty)
    : cameraTree() , newCameraList("Detected Cameras"), activeCameras() {

    if(empty) return;
    QObject::connect(&cameraTree, SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(on_CameraTree_itemChanged(QStandardItem*)));
    cameraTree.appendRow(&newCameraList);
    newCameraList.setCheckable(true);
    newCameraList.setDragEnabled(false);
    //newCameraList.setCheckState(Qt::Checked);
    newCameraList.setEditable(false);
}
void AbstractCameraManager::setMainWindow(MainWindow* window){
    mainWindow = window;
}
QModelIndex AbstractCameraManager::addGroup(){
    QStandardItem *newGroup = new QStandardItem("new Group");
    newGroup->setCheckable(true);
    cameraTree.appendRow(newGroup);
    return newGroup->index();
}

bool AbstractCameraManager::addNewCamera(std::string name, AbstractCamera *camera){
    //To add: check if already in cameraTree
    QStandardItem *item = new QStandardItem(name.c_str());
    item->setData(QVariant::fromValue(camera), CameraRole);
    //qDebug() << "setData " << camera << " data " << item->data(CameraRole).value<AbstractCamera *>();
    item->setCheckable(true);
    item->setCheckState(Qt::Checked);
    item->setDropEnabled(false);
    newCameraList.appendRow(item);
    return true;
}

void AbstractCameraManager::activateCamera(AbstractCamera* camera, QStandardItem* item, bool active){
    qDebug() << "activateCamera( " << camera << ", " << active << ")";
    int i = activeCameras.size()-1;
    while(i>=0 && activeCameras.at(i).camera != camera) --i;

    if(i >= 0){
        if(!active){
            qDebug() << "desactivating Camera";
            activeCameraEntry* entry = &activeCameras.at(i);
            mainWindow->modifySubWindow(entry->window, false);
            activeCameras.erase(activeCameras.begin()+i);
        }
    }else{
        if(active){
            qDebug() << "activating Camera";
            activeCameraEntry entry = activeCameraEntry(camera, item);
            connect(entry.window, SIGNAL(destroyed(QObject*)),
                    this, SLOT(on_subwindow_closing(QObject*)) );
            mainWindow->modifySubWindow(entry.window, true);
            activeCameras.push_back(entry);
        }
    }
}
QStandardItemModel* AbstractCameraManager::getModel(){
    return &cameraTree;
}
void AbstractCameraManager::on_subwindow_closing(QObject *window){
    qDebug() << "closing " << window;
    int i = activeCameras.size()-1;
    while(i>=0 && activeCameras.at(i).window != window) --i;

    if(i>=0) activeCameras.at(i).treeItem->setCheckState(Qt::Unchecked);
}
void AbstractCameraManager::on_CameraTree_itemChanged(QStandardItem* item){
    qDebug() << "itemChanged on " << item->text();
    Qt::CheckState checked = item->checkState();
    if( item->data(CameraRole).isValid() ){
        activateCamera( item->data(CameraRole).value<AbstractCamera *>(), item, checked==Qt::Checked);
    }else{
        cameraTree_recursive(item, checked);
    }
}
void AbstractCameraManager::cameraTree_recursive(QStandardItem* parent, Qt::CheckState checked){
    for(int i=0; i<parent->rowCount(); ++i){
         QStandardItem* currItem = parent->child(i);
         if(currItem->checkState() != checked){
             currItem->setCheckState(checked);
         }
    }
}
