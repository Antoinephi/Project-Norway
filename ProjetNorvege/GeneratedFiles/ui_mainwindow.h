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
    QAction *actionUpdateImages;
    QAction *actionUpdateProperties;
    QAction *actionLiveView;
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
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addGroup;
    QPushButton *editItem;
    QPushButton *deleteGroup;
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
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuitter->setIcon(icon);
        actionMosaic = new QAction(MainWindow);
        actionMosaic->setObjectName(QStringLiteral("actionMosaic"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/mosaic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMosaic->setIcon(icon1);
        actionUpdateImages = new QAction(MainWindow);
        actionUpdateImages->setObjectName(QStringLiteral("actionUpdateImages"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/one.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpdateImages->setIcon(icon2);
        actionUpdateProperties = new QAction(MainWindow);
        actionUpdateProperties->setObjectName(QStringLiteral("actionUpdateProperties"));
        actionLiveView = new QAction(MainWindow);
        actionLiveView->setObjectName(QStringLiteral("actionLiveView"));
        actionLiveView->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/liveview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLiveView->setIcon(icon3);
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
        SelectCameras->setMinimumSize(QSize(0, 22));
        SelectCameras->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(SelectCameras);

        Detect = new QPushButton(dockWidgetContents);
        Detect->setObjectName(QStringLiteral("Detect"));
        Detect->setMinimumSize(QSize(0, 0));
        Detect->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        Detect->setIcon(icon4);

        horizontalLayout->addWidget(Detect);


        verticalLayout->addLayout(horizontalLayout);

        CameraTree = new QTreeView(dockWidgetContents);
        CameraTree->setObjectName(QStringLiteral("CameraTree"));
        CameraTree->setContextMenuPolicy(Qt::CustomContextMenu);
        CameraTree->setEditTriggers(QAbstractItemView::EditKeyPressed);
        CameraTree->setDragEnabled(true);
        CameraTree->setDragDropMode(QAbstractItemView::InternalMove);
        CameraTree->setAlternatingRowColors(true);
        CameraTree->setAutoExpandDelay(200);
        CameraTree->setRootIsDecorated(true);
        CameraTree->setItemsExpandable(true);
        CameraTree->setAnimated(true);
        CameraTree->setExpandsOnDoubleClick(true);
        CameraTree->header()->setVisible(false);
        CameraTree->header()->setDefaultSectionSize(0);

        verticalLayout->addWidget(CameraTree);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        addGroup = new QPushButton(dockWidgetContents);
        addGroup->setObjectName(QStringLiteral("addGroup"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/folder_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addGroup->setIcon(icon5);
        addGroup->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(addGroup);

        editItem = new QPushButton(dockWidgetContents);
        editItem->setObjectName(QStringLiteral("editItem"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        editItem->setIcon(icon6);
        editItem->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(editItem);

        deleteGroup = new QPushButton(dockWidgetContents);
        deleteGroup->setObjectName(QStringLiteral("deleteGroup"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/folder_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteGroup->setIcon(icon7);
        deleteGroup->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(deleteGroup);


        verticalLayout->addLayout(horizontalLayout_2);

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
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionQuitter);
        toolBar->addAction(actionLiveView);
        toolBar->addAction(actionUpdateImages);
        toolBar->addSeparator();
        toolBar->addAction(actionMosaic);
        toolBar->addSeparator();
        toolBar->addAction(actionUpdateProperties);

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
        actionUpdateImages->setText(QApplication::translate("MainWindow", "UpdateImages (Space)", 0));
        actionUpdateImages->setShortcut(QApplication::translate("MainWindow", "Space", 0));
        actionUpdateProperties->setText(QApplication::translate("MainWindow", "UpdateProperties", 0));
        actionLiveView->setText(QApplication::translate("MainWindow", "LiveView", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        CamerasWidget->setWindowTitle(QApplication::translate("MainWindow", "Cameras", 0));
#ifndef QT_NO_TOOLTIP
        Detect->setToolTip(QApplication::translate("MainWindow", "Detect new cameras", 0));
#endif // QT_NO_TOOLTIP
        Detect->setText(QString());
#ifndef QT_NO_TOOLTIP
        addGroup->setToolTip(QApplication::translate("MainWindow", "Add group", 0));
#endif // QT_NO_TOOLTIP
        addGroup->setText(QString());
#ifndef QT_NO_TOOLTIP
        editItem->setToolTip(QApplication::translate("MainWindow", "Edit", 0));
#endif // QT_NO_TOOLTIP
        editItem->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteGroup->setToolTip(QApplication::translate("MainWindow", "Delete group", 0));
#endif // QT_NO_TOOLTIP
        deleteGroup->setText(QString());
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
