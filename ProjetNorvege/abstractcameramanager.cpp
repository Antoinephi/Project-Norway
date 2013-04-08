#include "abstractcameramanager.h"


AbstractCameraManager::AbstractCameraManager(bool first)
    : cameraTree() , newCameraList("Detected Cameras") {
    if(first) return;
    cameraTree.appendRow(&newCameraList);
    newCameraList.setCheckable(true);
    newCameraList.setDragEnabled(false);
    //newCameraList.setCheckState(Qt::Checked);
    newCameraList.setEditable(false);
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
    item->setData(QVariant(QVariant::UserType, camera), CameraRole);
    item->setCheckable(true);
    item->setCheckState(Qt::Checked);
    newCameraList.appendRow(item);
    return true;
}

QStandardItemModel* AbstractCameraManager::getModel(){
    return &cameraTree;
}
