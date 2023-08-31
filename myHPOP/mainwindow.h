#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMdiArea>
#include<QMdiSubWindow>
#include<QDockWidget>
#include<QTreeWidget>
#include<QDebug>
#include<QGridLayout>
#include<QTimer>
#include<QMouseEvent>
#include<QMessageBox>

#include"calculate/TB.h"
#include"scenario.h"
#include"satellite.h"
#include"outputorbittextwidget.h"
#include"earth2d.h"
#include"earth3d.h"
#include"timewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void setScenarioTime();//设置场景时间
    void setSatellteStartPos();//设置卫星初始位置
    void setPerPara();//设置摄动力基本参数
    void showPerturbationWidget();//摄动力模型对话框展示

    void showScenario(QTreeWidgetItem*,int);//场景窗口
    void showSatellite(QTreeWidgetItem*,int);//卫星窗口

    void finishOrbitYes(bool b);//判断是否绘制完

    void on_timer();//实时信号发送
    void timeSet();//发送指定时间信号    
//    void updateMenu();//更新菜单栏状态

    void on_actionNewScenario_triggered();

    void on_actionInsertSatellite_triggered();

    void on_actionCalculate_triggered();

    void on_actionOutputOrbitText_triggered();

    void on_actionPlayPause_triggered();

    void on_actionSaveScenario_triggered();

    void on_actionOpenScenario_triggered();

    void on_actionSaveSatellite_triggered();

    void on_actionOpenSatellite_triggered();

    void on_action2D_triggered();

    void on_actionItem_triggered();

    void on_actionTime_triggered();

    void on_action3D_triggered();

    void on_actionDrawAll_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    QMdiArea *mdiArea;//主要工作区
    QDockWidget *itemDockWidget=nullptr;//对象窗口
    QDockWidget *timeDockWidget=nullptr;//时间窗口

    QTreeWidget *itemTreeWidget=nullptr;//对象树
    QTreeWidgetItem *scenarioTreeWidgetItem=nullptr;//对象树中对应的场景
    QTreeWidgetItem *satelliteTreeWidgetItem=nullptr;//对象树中对应的卫星

    void timeWidgetSet();//时间窗口设置
    TimeWidget *timeWidget=nullptr;

    QMdiSubWindow *earth2Dsub=nullptr;
    QMdiSubWindow *earth3Dsub=nullptr;
    Earth2D *earth2D=nullptr;//2D窗口
    Earth3D *earth3D=nullptr;//3D窗口

    Scenario *scenario=nullptr;
    int t1[3]={0},t2[3]={0};
    double fd1=0,fd2=0;

    Satellite *satellite=nullptr;
    double para[15]={0};

    OutputOrbitTextWidget *outputOrbitTextWidget=nullptr;//结果输出对话框
};
#endif // MAINWINDOW_H
