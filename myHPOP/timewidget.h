#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include<QFrame>
#include<QPainter>
#include"satellite.h"
#include"scenario.h"
#include"calculate/SOFA/sofa.h"
#include"calculate/SOFA/sofam.h"
#include"math.h"
#include"daytimedrawarea.h"
#include"wholetimedrawarea.h"

class TimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeWidget(QWidget *parent = nullptr);

    void setTimeDisplay(int m);//设置展示时间
    void sendTimeCount();
    void getTime(Scenario *sc,Satellite *sa);

    QPushButton *timeSetPushButton;
    DayTimeDrawArea *dayTimeDrawArea;//一天的时间轴绘制区域
    WholeTimeDrawArea *wholeTimeDrawArea;//整个计算时间的时间轴绘制区域

private:    
    void resizeEvent(QResizeEvent *);

    QGridLayout *timeLayout;
    QGridLayout *mainLayout;
    QLineEdit *timeDisplayLineEdit;
    QLineEdit *timeSetLineEdit;    

    Scenario *scenario;
    Satellite *satellite;

signals:
    void sendTimeCountSignal(int m);
};

#endif // TIMEWIDGET_H
