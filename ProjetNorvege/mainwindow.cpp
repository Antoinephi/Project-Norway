#include <QMessageBox>
#include <QStandardItem>
#include <QDebug>
#include <QMdiArea>
#include <QMdiSubWindow>

#include <QWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "abstractcameramanager.h"
#include "testcameramanager.h"
#include "emptycameramanager.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      addGroup(new QAction("Add Group", this)), cameraManagers(), selectedCameraManager(-1)
{
    cameraManagers.push_back(new EmptyCameraManager());
    cameraManagers.push_back(new TestCameraManager());

    ui->setupUi(this);
    //ui->SelectCameras->addItem("Select");

    for (unsigned int i=0 ; i < cameraManagers.size(); ++i){
        AbstractCameraManager* manager = cameraManagers.at(i);
        manager->setMainWindow(this);
        ui->SelectCameras->addItem(manager->getName().c_str());
    }
    connect(ui->CameraTree, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(on_CameraTree_itemClicked(const QModelIndex &)));
    connect(addGroup, SIGNAL(triggered()),
            this, SLOT(on_createGroup_triggered()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::modifySubWindow(QMdiSubWindow* in, bool add){
    qDebug() << "modifySubWindow( " << in << ", " << add << ")";
    if(add){
        (ui->centralwidget->addSubWindow(in))->show();
    }else{
        ui->centralwidget->removeSubWindow(in);
    }
}

void MainWindow::on_actionQuitter_triggered()
{
    qApp->exit();
}

void MainWindow::on_Detect_clicked()
{
    ui->CameraTree->setExpanded(cameraManagers.at(selectedCameraManager)->detectNewCamerasAndExpand(), true);
}
void MainWindow::on_actionMosaic_triggered()
{
    ui->centralwidget->tileSubWindows();
}

void MainWindow::on_CameraTree_customContextMenuRequested(const QPoint &pos)
{
    //QModelIndex index = ui->CameraTree->currentIndex();
    //if(ui->CameraTree->model()->hasChildren(index))

    QMenu contextMenu(tr("Context menu"), this);

    contextMenu.addAction(addGroup);
    contextMenu.exec(ui->CameraTree->viewport()->mapToGlobal(pos));
}
void MainWindow::on_createGroup_triggered()
{
    ui->CameraTree->edit( cameraManagers.at(selectedCameraManager)->addGroup() );
}



void MainWindow::on_SelectCameras_currentIndexChanged(int index)
{
    if(selectedCameraManager >= 0)
        cameraManagers.at(selectedCameraManager)->getPropertiesWidget()->hide();
    selectedCameraManager = index;
    AbstractCameraManager* cm = cameraManagers.at(selectedCameraManager);
    ui->CameraTree->setModel(cm->getModel());
    ui->propertiesContainer->addWidget(cm->getPropertiesWidget());
    cm->getPropertiesWidget()->show();
}

//need to be moved to AbstractCameraManager
void MainWindow::on_CameraTree_itemClicked(const QModelIndex & index){
    ui->label->setText( cameraManagers.at(selectedCameraManager)->cameraTree_itemClicked(index) );
}




