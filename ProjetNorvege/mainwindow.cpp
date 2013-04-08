#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "testcameramanager.h"
#include "emptycameramanager.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      addGroup(new QAction("Add Group", this)), cameraManagers(), selectedCameraManager(-1)
{
    ui->setupUi(this);
    //ui->SelectCameras->addItem("Select");
    cameraManagers.push_back(new EmptyCameraManager());
    cameraManagers.push_back(new TestCameraManager());
    for (unsigned int i=0 ; i < cameraManagers.size(); ++i){
        ui->SelectCameras->addItem(cameraManagers.at(i)->getName().c_str());
    }
    connect(ui->CameraTree, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_CameraTree_itemClicked(const QModelIndex &)));
    connect(addGroup, SIGNAL(triggered()), this, SLOT(on_createGroup_triggered()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
    qApp->exit();
}

void MainWindow::on_Detect_clicked()
{
    QMessageBox::critical(this, "Error", "Not implemented");
    //then expend Detected Cameras...
}
void MainWindow::on_actionMosaic_triggered()
{
    QMessageBox::critical(this, "Error", "Not implemented");
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
    selectedCameraManager = index;
    ui->CameraTree->setModel(cameraManagers.at(selectedCameraManager)->getModel());
}

void MainWindow::on_CameraTree_itemClicked(const QModelIndex & index){
    ui->label->setText(cameraManagers.at(selectedCameraManager)->getModel()->itemFromIndex(index)->text());
}
