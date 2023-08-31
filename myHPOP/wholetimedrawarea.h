#ifndef WHOLETIMEDRAWAREA_H
#define WHOLETIMEDRAWAREA_H

#include <QWidget>
#include<QDebug>
#include<QPainter>
#include<QMouseEvent>
#include"satellite.h"

class WholeTimeDrawArea : public QWidget
{
    Q_OBJECT
public:
    explicit WholeTimeDrawArea(QWidget *parent = nullptr);
    void acceptCounts(int m);//接受计数信号
    void getSatellite(Satellite *sa);

    void sendTimeCount();//发送计数信号

signals:
    void sendTimeCountSignal(int m);

private:
    QPixmap pix;
    Satellite *satellite=nullptr;
    int mCounts=0;//计数信号
    int sendCounts=0;//发送的计数信号
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void getSendCounts(double time);//根据时间得到对应的计数信号
};

#endif // WHOLETIMEDRAWAREA_H
