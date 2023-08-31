/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewScenario;
    QAction *actionInsertSatellite;
    QAction *actionCalculate;
    QAction *actionOutputOrbitText;
    QAction *actionPlayPause;
    QAction *actionOpenScenario;
    QAction *actionSaveScenario;
    QAction *actionOpenSatellite;
    QAction *actionSaveSatellite;
    QAction *action2D;
    QAction *action3D;
    QAction *actionItem;
    QAction *actionTime;
    QAction *actionHelp;
    QAction *actionDrawAll;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_I;
    QMenu *menu_W;
    QMenu *menu_H;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionNewScenario = new QAction(MainWindow);
        actionNewScenario->setObjectName(QString::fromUtf8("actionNewScenario"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewScenario->setIcon(icon);
        actionInsertSatellite = new QAction(MainWindow);
        actionInsertSatellite->setObjectName(QString::fromUtf8("actionInsertSatellite"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/satellite.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsertSatellite->setIcon(icon1);
        actionCalculate = new QAction(MainWindow);
        actionCalculate->setObjectName(QString::fromUtf8("actionCalculate"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/calculate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalculate->setIcon(icon2);
        actionOutputOrbitText = new QAction(MainWindow);
        actionOutputOrbitText->setObjectName(QString::fromUtf8("actionOutputOrbitText"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/orbitText.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOutputOrbitText->setIcon(icon3);
        actionPlayPause = new QAction(MainWindow);
        actionPlayPause->setObjectName(QString::fromUtf8("actionPlayPause"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlayPause->setIcon(icon4);
        actionOpenScenario = new QAction(MainWindow);
        actionOpenScenario->setObjectName(QString::fromUtf8("actionOpenScenario"));
        actionSaveScenario = new QAction(MainWindow);
        actionSaveScenario->setObjectName(QString::fromUtf8("actionSaveScenario"));
        actionOpenSatellite = new QAction(MainWindow);
        actionOpenSatellite->setObjectName(QString::fromUtf8("actionOpenSatellite"));
        actionSaveSatellite = new QAction(MainWindow);
        actionSaveSatellite->setObjectName(QString::fromUtf8("actionSaveSatellite"));
        action2D = new QAction(MainWindow);
        action2D->setObjectName(QString::fromUtf8("action2D"));
        action3D = new QAction(MainWindow);
        action3D->setObjectName(QString::fromUtf8("action3D"));
        actionItem = new QAction(MainWindow);
        actionItem->setObjectName(QString::fromUtf8("actionItem"));
        actionTime = new QAction(MainWindow);
        actionTime->setObjectName(QString::fromUtf8("actionTime"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionDrawAll = new QAction(MainWindow);
        actionDrawAll->setObjectName(QString::fromUtf8("actionDrawAll"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/allOrbit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawAll->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menu_I = new QMenu(menubar);
        menu_I->setObjectName(QString::fromUtf8("menu_I"));
        menu_W = new QMenu(menubar);
        menu_W->setObjectName(QString::fromUtf8("menu_W"));
        menu_H = new QMenu(menubar);
        menu_H->setObjectName(QString::fromUtf8("menu_H"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_W->menuAction());
        menubar->addAction(menu_I->menuAction());
        menubar->addAction(menu_H->menuAction());
        menu_F->addAction(actionNewScenario);
        menu_F->addAction(actionOpenScenario);
        menu_F->addAction(actionSaveScenario);
        menu_F->addSeparator();
        menu_F->addAction(actionSaveSatellite);
        menu_I->addAction(actionInsertSatellite);
        menu_I->addSeparator();
        menu_I->addAction(actionOpenSatellite);
        menu_W->addAction(action2D);
        menu_W->addAction(action3D);
        menu_W->addSeparator();
        menu_W->addAction(actionItem);
        menu_W->addAction(actionTime);
        menu_W->addSeparator();
        menu_W->addAction(actionDrawAll);
        menu_W->addSeparator();
        menu_W->addAction(actionOutputOrbitText);
        menu_H->addAction(actionHelp);
        toolBar->addAction(actionNewScenario);
        toolBar->addSeparator();
        toolBar->addAction(actionInsertSatellite);
        toolBar->addAction(actionCalculate);
        toolBar->addSeparator();
        toolBar->addAction(actionPlayPause);
        toolBar->addAction(actionDrawAll);
        toolBar->addSeparator();
        toolBar->addAction(actionOutputOrbitText);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNewScenario->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\345\234\272\346\231\257(&N)...", nullptr));
#if QT_CONFIG(tooltip)
        actionNewScenario->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\345\234\272\346\231\257", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNewScenario->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionInsertSatellite->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\345\215\253\346\230\237(&S)...", nullptr));
#if QT_CONFIG(tooltip)
        actionInsertSatellite->setToolTip(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\345\215\253\346\230\237", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCalculate->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227", nullptr));
#if QT_CONFIG(tooltip)
        actionCalculate->setToolTip(QCoreApplication::translate("MainWindow", "\351\253\230\347\262\276\345\272\246\350\275\250\351\201\223\350\256\241\347\256\227", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOutputOrbitText->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272\347\273\223\346\236\234", nullptr));
#if QT_CONFIG(tooltip)
        actionOutputOrbitText->setToolTip(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272\347\273\223\346\236\234", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPlayPause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234\345\274\200\345\247\213\346\214\211\351\222\256", nullptr));
        actionOpenScenario->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\234\272\346\231\257", nullptr));
        actionSaveScenario->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\234\272\346\231\257", nullptr));
        actionOpenSatellite->setText(QCoreApplication::translate("MainWindow", "\350\275\275\345\205\245\345\215\253\346\230\237", nullptr));
        actionSaveSatellite->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\215\253\346\230\237", nullptr));
        action2D->setText(QCoreApplication::translate("MainWindow", "\344\272\214\347\273\264\350\247\206\345\233\276", nullptr));
        action3D->setText(QCoreApplication::translate("MainWindow", "\344\270\211\347\273\264\350\247\206\345\233\276", nullptr));
        actionItem->setText(QCoreApplication::translate("MainWindow", "\345\257\271\350\261\241\347\252\227\345\217\243", nullptr));
        actionTime->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264\347\252\227\345\217\243", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\350\257\264\346\230\216", nullptr));
        actionDrawAll->setText(QCoreApplication::translate("MainWindow", "\347\273\230\345\210\266\346\211\200\346\234\211\350\275\250\351\201\223", nullptr));
        menu_F->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_I->setTitle(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245(&I)", nullptr));
        menu_W->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\345\233\276(&W)", nullptr));
        menu_H->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
