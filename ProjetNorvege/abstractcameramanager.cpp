#include "abstractcameramanager.h"
#include "mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QCheckBox>
#include <QSlider>
#include <algorithm>
Q_DECLARE_METATYPE(AbstractCamera *)

AbstractCameraManager::AbstractCameraManager(bool empty)
    : cameraTree() , newCameraList("Detected Cameras"), propertiesList(), activeCameras() {

    propertiesList.setRootIsDecorated(false);
    propertiesList.setColumnCount(4);
    propertiesList.setHeaderLabels(QStringList() << "property" << "auto" << "value" << "slider");


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
void AbstractCameraManager::setProperties(std::vector<CameraProperty> &properties){
    for(int i=0; i<properties.size(); i++){
        CameraProperty &property = properties.at(i);
        qDebug() << property.getName().c_str() << reinterpret_cast<quintptr>(&property);
        QTreeWidgetItem* it = new QTreeWidgetItem();
        it->setText( 0, property.getName().c_str());
        propertiesList.addTopLevelItem(it);
        //checkbox
        QCheckBox* box = new QCheckBox();
        box->setProperty("CameraProperty", QVariant::fromValue(reinterpret_cast<quintptr>(&property)) );
        if(!property.getCanAuto()) box->setEnabled(false);
        propertiesList.setItemWidget(it, 1, box);
        connect( box, SIGNAL(stateChanged(int)), this, SLOT(on_propertyCheckbox_changed(int)) );
        //slider
        QSlider* slider = new QSlider(Qt::Horizontal);
        slider->setProperty("CameraProperty", QVariant::fromValue(reinterpret_cast<quintptr>(&property)) );
        slider->setTracking(false); //might be wanted
        propertiesList.setItemWidget(it, 3, slider);
        connect( slider, SIGNAL(valueChanged(int)), this, SLOT(on_propertyCheckbox_changed(int)) );
    }
}
void AbstractCameraManager::on_propertyCheckbox_changed(int state){
    CameraProperty* prop = reinterpret_cast<CameraProperty*>( sender()->property("CameraProperty").value<quintptr>() );
    qDebug() << sender()->property("CameraProperty").value<quintptr>();
    qDebug() << sender() << prop->getName().c_str();
}
void AbstractCameraManager::on_propertySlider_changed(int val){
    CameraProperty* prop = reinterpret_cast<CameraProperty*>( sender()->property("CameraProperty").value<quintptr>() );
    qDebug() << sender() << prop->getName().c_str();
}

QModelIndex AbstractCameraManager::detectNewCamerasAndExpand(){
    detectNewCameras();
    return newCameraList.index();
}
QModelIndex AbstractCameraManager::addGroup(){
    QStandardItem *newGroup = new QStandardItem("new Group");
    newGroup->setCheckable(true);
    cameraTree.appendRow(newGroup);
    return newGroup->index();
}

bool AbstractCameraManager::addNewCamera(std::string name, AbstractCamera *camera){
    //check if already detected
    if(cameraTree_recursiveSearch(cameraTree.invisibleRootItem(), camera)) return false;

    //adding
    QStandardItem *item = new QStandardItem(name.c_str());
    item->setData(QVariant::fromValue( reinterpret_cast<quintptr>(camera) ), CameraRole);
    //qDebug() << "setData " << camera << " data " << item->data(CameraRole).value<AbstractCamera *>();
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    item->setDropEnabled(false);
    newCameraList.appendRow(item);
    return true;
}

void AbstractCameraManager::activateCamera(AbstractCamera* camera, QStandardItem* item, bool active){
    qDebug() << "activateCamera( " << camera << ", " << active << ")";
    int i = activeCameras.size()-1;
    while(i>=0 && activeCameras.at(i).camera != camera) --i;

    if(i >= 0){ //trouve
        if(!active){ // desactivation
            //qDebug() << "desactivating Camera";
            activeCameraEntry* entry = &activeCameras.at(i);
            mainWindow->modifySubWindow(entry->window, false);
            activeCameras.erase(activeCameras.begin()+i);
        }else{
            activeCameras.at(i).window->setWindowTitle(item->text());
        }
    }else{
        if(active){// activation
            //qDebug() << "activating Camera";
            activeCameraEntry entry = activeCameraEntry(camera, item);
            connect(entry.window, SIGNAL(destroyed(QObject*)),
                    this, SLOT(on_subwindow_closing(QObject*)) );
            entry.window->setWindowTitle(item->text());
            mainWindow->modifySubWindow(entry.window, true);
            activeCameras.push_back(entry);
        }
    }
}
QStandardItemModel* AbstractCameraManager::getModel(){
    return &cameraTree;
}
QTreeWidget *AbstractCameraManager::getPropertiesWidget(){
    return &propertiesList;
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
        activateCamera( reinterpret_cast<AbstractCamera*>( item->data(CameraRole).value<quintptr>() ), item, checked==Qt::Checked);
    }else{
        cameraTree_recursiveCheck(item, checked);
    }
}
void AbstractCameraManager::cameraTree_recursiveCheck(QStandardItem* parent, Qt::CheckState checked){
    for(int i=0; i<parent->rowCount(); ++i){
         QStandardItem* currItem = parent->child(i);
         if(currItem->checkState() != checked){
             currItem->setCheckState(checked);
         }
    }
}
bool AbstractCameraManager::cameraTree_recursiveSearch(QStandardItem* parent, AbstractCamera* camera){
    QVariant data = parent->data(CameraRole);
    //qDebug() << "cameraTree_recursiveSearch( " << parent->text() << ", " << camera << ") " << data.value<AbstractCamera*>();
    if(data.isValid() &&  reinterpret_cast<AbstractCamera*>(data.value<quintptr>()) == camera) return true;

    for(int i=0; i<parent->rowCount(); ++i){
        if(cameraTree_recursiveSearch(parent->child(i), camera)) return true;
    }
    return false;
}

QString AbstractCameraManager::cameraTree_itemClicked(const QModelIndex & index){
    QStandardItem* clicked = getModel()->itemFromIndex(index);
    QStandardItem* first = cameraTree_recursiveFirstCamera(clicked);
    selectedCamera = first;
    if( first != NULL && !clicked->data(CameraRole).isValid() )
        return clicked->text() + " ("+ first->text() + ")";
    else{
        return clicked->text();
    }
}
QStandardItem* AbstractCameraManager::cameraTree_recursiveFirstCamera(QStandardItem* parent){
    QVariant data = parent->data(CameraRole);
    if(data.isValid())
        return parent;

    for(int i=0; i<parent->rowCount(); ++i){
        QStandardItem* tmp = cameraTree_recursiveFirstCamera(parent->child(i));
        if( tmp != NULL ) return tmp;
    }
    return NULL;
}
