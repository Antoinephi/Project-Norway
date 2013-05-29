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
    propertiesIcons[0] = QIcon(":/icons/camera").pixmap(16,16);
    propertiesIcons[1] = QIcon(":/icons/folder").pixmap(16,16);
    propertiesIcons[2] = QIcon(":/icons/folder_camera").pixmap(16,16);

    ui->setupUi(this);


	cameraManagers.push_back(new EmptyCameraManager());
	cameraManagers.push_back(new TestCameraManager());


	for (unsigned int i=0 ; i < cameraManagers.size(); ++i){
		AbstractCameraManager* manager = cameraManagers.at(i);
		manager->setMainWindow(this);
		ui->SelectCameras->addItem(manager->getName().c_str());
	}

    ui->SelectCameras->setFixedHeight( ui->Detect->sizeHint().height()-2 );

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
    if(selectedCameraManager >= 0){
        AbstractCameraManager* camManager = cameraManagers.at(selectedCameraManager);
        camManager->activateLiveView(false);
        camManager->desactiveAllCameras();
        camManager->getPropertiesWidget()->hide();
    }
	selectedCameraManager = index;
	AbstractCameraManager* cm = cameraManagers.at(selectedCameraManager);
	ui->CameraTree->setModel(cm->getModel());
	ui->propertiesContainer->addWidget(cm->getPropertiesWidget());
	cm->getPropertiesWidget()->show();
    on_Detect_clicked();
    if( ui->actionLiveView->isChecked() )
        cm->activateLiveView( true );
}

//need to be moved to AbstractCameraManager
void MainWindow::on_CameraTree_itemClicked(const QModelIndex & index){
    QString str = "";
    bool editable, deleteable;
    int icon = 0;
    cameraManagers.at(selectedCameraManager)->cameraTree_itemClicked(index, str, icon, editable, deleteable);

    ui->label->setText( str );
    ui->editItem->setEnabled( editable );
    ui->deleteGroup->setEnabled( deleteable );

    if( icon>=0 && icon < 3 )
        ui->propertiesIcon->setPixmap(propertiesIcons[icon]);
}


void MainWindow::on_actionUpdateImages_triggered()
{
    cameraManagers.at(selectedCameraManager)->updateImages();
}

void MainWindow::on_actionUpdateProperties_triggered()
{
    cameraManagers.at(selectedCameraManager)->updateProperties();
}

void MainWindow::on_actionLiveView_toggled(bool arg1)
{
    ui->actionUpdateImages->setEnabled(!arg1);
    cameraManagers.at(selectedCameraManager)->activateLiveView( arg1 );
}




void MainWindow::on_addGroup_clicked()
{
    ui->CameraTree->edit( cameraManagers.at(selectedCameraManager)->addGroup() );
}

void MainWindow::on_editItem_clicked()
{
    ui->CameraTree->edit( ui->CameraTree->currentIndex() );
}

void MainWindow::on_deleteGroup_clicked()
{
    if( !ui->CameraTree->currentIndex().isValid() ) return;
    cameraManagers.at(selectedCameraManager)->removeGroup( ui->CameraTree->currentIndex() );
    on_CameraTree_itemClicked( ui->CameraTree->currentIndex() );
}
