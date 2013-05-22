#include "abstractcameramanager.h"
#include "mainwindow.h"
#include <QtCore>
#include <QDebug>
#include <QCheckBox>
#include <QSlider>
#include <algorithm>
Q_DECLARE_METATYPE(AbstractCamera *)
Q_DECLARE_METATYPE(CameraProperty *)

enum PropertiesWidgetPosition{
    PropertyName = 0,
    PropertyAuto = 1,
    PropertyValue = 2,
    PropertySlider = 3
};

AbstractCameraManager::AbstractCameraManager(bool empty)
    : cameraTree() , newCameraList("Detected Cameras"), propertiesList(), selectedItem(NULL), selectedCamera(NULL), activeCameras(), cameraProperties() {

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
QStandardItemModel* AbstractCameraManager::getModel(){
    return &cameraTree;
}
QTreeWidget *AbstractCameraManager::getPropertiesWidget(){
    return &propertiesList;
}



void AbstractCameraManager::updateImages(){
    for(int i=activeCameras.size()-1; i>=0; i--){
        activeCameraEntry& camEntry = activeCameras.at(i);
        //qDebug() << camEntry.window->widget();
        QLabel* lbl = qobject_cast<QLabel *>( camEntry.window->widget() );
        //qDebug() << "setting img in widget" << lbl;
        //qDebug() << camEntry.window->size();
        QPixmap pxmap = QPixmap::fromImage(camEntry.camera->retrieveImage().scaled(lbl->size(), Qt::KeepAspectRatio));
        lbl->setPixmap(pxmap);
        lbl->show();
    }
}

void AbstractCameraManager::updateProperties(){
    AbstractCamera* selected = selectedCamera;
    if( selected == NULL ) return ;
    for( int i = propertiesList.topLevelItemCount()-1; i>=0; i--){
        QTreeWidgetItem* item = propertiesList.topLevelItem(i);
        QCheckBox* checkBox = qobject_cast<QCheckBox*>( propertiesList.itemWidget(item, PropertyAuto) );
        CameraProperty * prop = reinterpret_cast<CameraProperty*>( checkBox->property("CameraProperty").value<quintptr>() );
        //qDebug() << "updating:" << prop->getName().c_str();
        selected->updateProperty(prop);
        item->setText(PropertyValue, prop->formatValue() );
        checkBox->setChecked(prop->getAuto());

        //(de)activate slider
        //reinterpret_cast<QSlider*>( checkBox->property("TreeWidgetSlider").value<quintptr>() )->setEnabled(prop->getAuto());

    }

}

///////////////////////////////////////////////////
/////////////// Camera List related ///////////////
///////////////////////////////////////////////////

QModelIndex AbstractCameraManager::detectNewCamerasAndExpand(){
    std::vector<AbstractCamera*> newCameras;
    std::vector<QStandardItem*> oldCameras;
    cameraTree_getCameraList(cameraTree.invisibleRootItem(), &oldCameras);
    detectNewCameras(&newCameras);
    qDebug() << "oldCameras" << oldCameras.size();
    qDebug() << "newCameras" << newCameras.size();
    //removing disconnected cameras
    for(unsigned int i=0; i<oldCameras.size(); i++){
        QStandardItem* item = oldCameras.at(i);
        AbstractCamera* cam = reinterpret_cast<AbstractCamera *>( item->data(CameraRole).value<quintptr>() );
        qDebug() << "oldCameras(" << i << "):" << cam;
        bool found = false;
        for(int j=newCameras.size()-1; j>=0; j--){
            if(cam->equalsTo(newCameras.at(j))){
                found = true;
                newCameras.erase(newCameras.begin()+j);
                continue;
            }
        }
        if( !found ){ //remove if disconnected
            activateCamera(cam, item, false);
            item->parent()->removeRow(item->row());
        }
    }
    qDebug() << "newCameras" << newCameras.size();
    //adding new cameras
    for(unsigned int i=0; i<newCameras.size(); i++){
        AbstractCamera* cam = newCameras.at(i);
        QStandardItem *item = new QStandardItem(cam->getString().c_str());
        item->setData(QVariant::fromValue( reinterpret_cast<quintptr>(cam) ), CameraRole);
        //qDebug() << "setData " << camera << " data " << item->data(CameraRole).value<AbstractCamera *>();
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        item->setDropEnabled(false);
        newCameraList.appendRow(item);
    }


    return newCameraList.index();
}
QModelIndex AbstractCameraManager::addGroup(){
    QStandardItem *newGroup = new QStandardItem("new Group");
    newGroup->setCheckable(true);
    cameraTree.appendRow(newGroup);
    return newGroup->index();
}

/* removed
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
}*/

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


QString AbstractCameraManager::cameraTree_itemClicked(const QModelIndex & index){    
    QStandardItem* clicked = getModel()->itemFromIndex(index);
    selectedItem = clicked;
    QStandardItem* first = cameraTree_recursiveFirstCamera(clicked);
    selectedCamera = reinterpret_cast<AbstractCamera *>( selectedItem->data(CameraRole).value<quintptr>() );
    updateProperties();
    qDebug() << "selectedItem" << selectedItem->text();
    if( first != NULL && !clicked->data(CameraRole).isValid() )
        return clicked->text() + " ("+ first->text() + ")";
    else{
        return clicked->text();
    }
}


///////////////////////////////////////////////////
//////////// Recursive in Camera List /////////////
///////////////////////////////////////////////////

//uncheck all
void AbstractCameraManager::desactiveAllCameras(){
    cameraTree_recursiveCheck(cameraTree.invisibleRootItem(), Qt::Unchecked);
}

// check QStandardItem and its decendants
void AbstractCameraManager::cameraTree_recursiveCheck(QStandardItem* parent, Qt::CheckState checked){
    for(int i=0; i<parent->rowCount(); ++i){
         QStandardItem* currItem = parent->child(i);
         if(currItem->checkState() != checked){
             currItem->setCheckState(checked);
         }
    }
}


// get first AbstractCamera in QStandardItem
// @return first found AbstractCamera
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

// set a property for all the AbstractCamera in QStandardItem and its decendants
void AbstractCameraManager::cameraTree_recursiveSetProperty(QStandardItem* parent, CameraProperty* prop){
    QVariant data = parent->data(CameraRole);
    if(data.isValid()){
        reinterpret_cast<AbstractCamera *>( data.value<quintptr>() )->setProperty(prop);
        return;
    }

    for(int i=0; i<parent->rowCount(); ++i){
        cameraTree_recursiveSetProperty(parent->child(i), prop);
    }
}

//add to the vector all found AbstractCamera in QStandardItem and its decendants
void AbstractCameraManager::cameraTree_getCameraList(QStandardItem* parent, std::vector<QStandardItem*> *list){
    QVariant data = parent->data(CameraRole);
    if(data.isValid()){
        list->push_back( parent );
        return;
    }

    for(int i=0; i<parent->rowCount(); ++i){
        cameraTree_getCameraList(parent->child(i), list);
    }
}


///////////////////////////////////////////////////
//////////////// Properties related ///////////////
///////////////////////////////////////////////////

void AbstractCameraManager::setProperties(std::vector<CameraProperty> &properties){
    cameraProperties = std::vector<CameraProperty>(properties);
    for(unsigned int i=0; i<cameraProperties.size(); i++){
        CameraProperty &property = cameraProperties.at(i);
        //qDebug() << property.getName().c_str() << reinterpret_cast<quintptr>(&property);
        QTreeWidgetItem* it = new QTreeWidgetItem();
        it->setText( PropertyName, property.getName().c_str());
        propertiesList.addTopLevelItem(it);
        //checkbox
        QCheckBox* box = new QCheckBox();
        box->setProperty("CameraProperty", QVariant::fromValue(reinterpret_cast<quintptr>(&property)) );

        if(!property.getCanAuto()) box->setEnabled(false);
        propertiesList.setItemWidget(it, PropertyAuto, box);
        connect( box, SIGNAL(stateChanged(int)), this, SLOT(on_propertyCheckbox_changed(int)) );
        //slider
        QSlider* slider = new QSlider(Qt::Horizontal);
        slider->setProperty("CameraProperty", QVariant::fromValue(reinterpret_cast<quintptr>(&property)) );
        slider->setProperty("TreeWidgetItem", QVariant::fromValue(reinterpret_cast<quintptr>(it)) );
        slider->setTracking(true); //might be wanted
        slider->setRange(property.getMinToSlider(), property.getMaxToSLider());
        propertiesList.setItemWidget(it, PropertySlider, slider);

        box->setProperty("TreeWidgetSlider", QVariant::fromValue(reinterpret_cast<quintptr>(slider)) );
        connect( slider, SIGNAL(valueChanged(int)), this, SLOT(on_propertySlider_changed(int)) );
    }
    propertiesList.resizeColumnToContents(0);
    propertiesList.resizeColumnToContents(1);
    propertiesList.resizeColumnToContents(2);
}

void AbstractCameraManager::on_propertyCheckbox_changed(int state){
    if( selectedItem == NULL ) return;
    CameraProperty* prop = reinterpret_cast<CameraProperty*>( sender()->property("CameraProperty").value<quintptr>() );
    qDebug() << sender() << prop->getName().c_str();
    prop->setAuto(state == Qt::Checked);
    cameraTree_recursiveSetProperty(selectedItem, prop);

    //(de)activate slider
    QSlider* slider =  reinterpret_cast<QSlider*>( sender()->property("TreeWidgetSlider").value<quintptr>() );
    qDebug() << "Qslider" << slider;
    if(state != Qt::Checked){
        slider->setEnabled(true);
        slider->setValue(prop->getValueToSlider());
    }else{
        slider->setEnabled(false);
    }

}
void AbstractCameraManager::on_propertySlider_changed(int val){
    if( selectedItem == NULL ) return;
    CameraProperty* prop = reinterpret_cast<CameraProperty*>( sender()->property("CameraProperty").value<quintptr>() );
    prop->setValueFromSlider(val);
    cameraTree_recursiveSetProperty(selectedItem, prop);

    reinterpret_cast<QTreeWidgetItem*>( sender()->property("TreeWidgetItem").value<quintptr>() )->setText(PropertyValue, prop->formatValue() );
}
