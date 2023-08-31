#ifndef EARTH2D_H
#define EARTH2D_H

#include <QWidget>
#include<QPainter>
#include<QString>
#include<QEvent>
#include<satellite.h>
#include<scenario.h>
#include<QTimer>
#include"calculate/SOFA/sofa.h"
#include"calculate/SOFA/sofam.h"
#include"calculate/timecoor.h"
#include<QToolBar>
#include<QVBoxLayout>

class Earth2D : public QWidget
{
    Q_OBJECT
public:
    explicit Earth2D(QWidget *parent = nullptr);

    QPixmap *pix;//地图图片
    QPixmap *satellitePix;//卫星图片

    double zoomFactor;//缩放因子
    bool drawOrbit=false;//轨道绘制开关
    bool drawAllOrbit=false;//所有圈轨道绘制
    bool startOrPause=true;//卫星开始暂停移动
    bool finishOrbit=false;//是否完成卫星整个绘制

    int mCounts=0;//时间计数

    void getTime(Scenario *scenario);
    void getSatelliteOrbit(Satellite *satellite);

    void startOrPauseSatellite();

    void sendFinishOrbit();//发送是否完成卫星整圈绘制信号

    void sendmCounts();//发射时间计数的信号

    void acceptmCount(int m);//接收时间计数

    QList<double> longitude;
    QList<double> latitude;
    QList<double> h;
    QList<int> TurnNumber;//圈数及其对应的节点
    Satellite *satellite=nullptr;

protected:
    void paintEvent(QPaintEvent *);

    QList<double> date1;
    QList<double> date2;    
    QTimer *timer;

private slots:
    void on_timer();

signals:
    void sendFinishOrbitSignal(bool b);//传递是否完成卫星绘制
    void sendmCountsSignal(int m);//时间计数的信号
};

#endif // EARTH2D_H
