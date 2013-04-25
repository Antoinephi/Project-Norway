/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuitter;
    QAction *actionMosaic;
    QMdiArea *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QStatusBar *statusbar;
    QDockWidget *CamerasWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *SelectCameras;
    QPushButton *Detect;
    QTreeView *CameraTree;
    QPushButton *pushButton;
    QDockWidget *PropertiesWidget;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *propertiesContainer;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(711, 604);
        MainWindow->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->setDockOptions(QMainWindow::AnimatedDocks);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionMosaic = new QAction(MainWindow);
        actionMosaic->setObjectName(QStringLiteral("actionMosaic"));
        centralwidget = new QMdiArea(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 711, 19));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        CamerasWidget = new QDockWidget(MainWindow);
        CamerasWidget->setObjectName(QStringLiteral("CamerasWidget"));
        CamerasWidget->setStyleSheet(QStringLiteral(""));
        CamerasWidget->setFeatures(QDockWidget::DockWidgetMovable);
        CamerasWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        SelectCameras = new QComboBox(dockWidgetContents);
        SelectCameras->setObjectName(QStringLiteral("SelectCameras"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SelectCameras->sizePolicy().hasHeightForWidth());
        SelectCameras->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(SelectCameras);

        Detect = new QPushButton(dockWidgetContents);
        Detect->setObjectName(QStringLiteral("Detect"));
        Detect->setCursor(QCursor(Qt::ArrowCursor));

        horizontalLayout->addWidget(Detect);


        verticalLayout->addLayout(horizontalLayout);

        CameraTree = new QTreeView(dockWidgetContents);
        CameraTree->setObjectName(QStringLiteral("CameraTree"));
        CameraTree->setContextMenuPolicy(Qt::CustomContextMenu);
        CameraTree->setDragEnabled(true);
        CameraTree->setDragDropMode(QAbstractItemView::InternalMove);
        CameraTree->setAlternatingRowColors(true);
        CameraTree->setAutoExpandDelay(200);
        CameraTree->setRootIsDecorated(true);
        CameraTree->setAnimated(true);
        CameraTree->header()->setVisible(false);
        CameraTree->header()->setDefaultSectionSize(0);

        verticalLayout->addWidget(CameraTree);

        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        CamerasWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), CamerasWidget);
        PropertiesWidget = new QDockWidget(MainWindow);
        PropertiesWidget->setObjectName(QStringLiteral("PropertiesWidget"));
        PropertiesWidget->setFeatures(QDockWidget::DockWidgetMovable);
        PropertiesWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(dockWidgetContents_2);
        label->setObjectName(QStringLiteral("label"));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        propertiesContainer = new QVBoxLayout();
        propertiesContainer->setObjectName(QStringLiteral("propertiesContainer"));

        verticalLayout_2->addLayout(propertiesContainer);

        PropertiesWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), PropertiesWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionQuitter);
        toolBar->addAction(actionMosaic);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        actionQuitter->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionMosaic->setText(QApplication::translate("MainWindow", "Mosaic", 0));
#ifndef QT_NO_TOOLTIP
        actionMosaic->setToolTip(QApplication::translate("MainWindow", "Make a mosaic with camera views", 0));
#endif // QT_NO_TOOLTIP
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        CamerasWidget->setWindowTitle(QApplication::translate("MainWindow", "Cameras", 0));
        Detect->setText(QApplication::translate("MainWindow", "Detect", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Update images", 0));
        PropertiesWidget->setWindowTitle(QApplication::translate("MainWindow", "Properties", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
