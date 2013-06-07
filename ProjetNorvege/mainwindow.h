#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abstractcameramanager.h"


namespace Ui {
	class MainWindow;

    enum PropertiesWidgetPosition{
        PropertyName = 0, PropertyAuto = 1, PropertyValue = 2, PropertySlider = 3
    };

    extern bool crosshair, crosshairReal, forceHighQuality;
}

class AbstractCameraManager;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void modifySubWindow(QMdiSubWindow* in, bool add);
	
public slots:
	void on_actionQuitter_triggered();
	
	void on_actionLiveView_toggled(bool arg1);
	void on_actionUpdateImages_triggered();
	void on_actionCrosshair_toggled(bool arg1);
    void on_actionCrosshairReal_toggled(bool arg1);
	void on_actionMosaic_triggered();
    void on_actionHighQuality_toggled(bool arg1);		

	void on_SelectCameras_currentIndexChanged(int index);
	void on_Detect_clicked();
	void on_CameraTree_itemClicked(const QModelIndex & index);

    void on_addGroup_clicked();
	void on_deleteGroup_clicked();
    void on_editItem_clicked();
	void on_resetItem_clicked();    

	void on_updatePropertiesButton_clicked();

signals:
    void activateCrosshair(bool);

private:
	Ui::MainWindow *ui;
	std::vector<AbstractCameraManager*> cameraManagers;
	int selectedCameraManager;
    QPixmap propertiesIcons[3];
};

#endif // MAINWINDOW_H
