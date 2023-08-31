#ifndef DAYTIMEDRAWAREA_H
#define DAYTIMEDRAWAREA_H

#include <QWidget>
#include<QDebug>
#include<QPainter>
#include<QMouseEvent>
#include"scenario.h"
#include"satellite.h"
#include"calculate/SOFA/sofa.h"
#include"calculate/SOFA/sofam.h"

class DayTimeDrawArea : public QWidget
{
    Q_OBJECT
public:
    explicit DayTimeDrawArea(QWidget *parent = nullptr);
    void acceptCounts(int m);//接受计数信号
    void getDisplayTime(Scenario *sc,Satellite *sa);

    void sendTimeCount();//发送计数信号

signals:
    void sendTimeCountSignal(int m);

private:
    QPixmap pix;
    Scenario *scenario=nullptr;
    Satellite *satellite=nullptr;
    int mCounts=0;//计数信号
    int year,month,day;//当下天数
    int sendCounts=0;//发送的计数信号
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void getSendCounts(double fd);//根据时间得到对应的计数信号
};

#endif // DAYTIMEDRAWAREA_H
