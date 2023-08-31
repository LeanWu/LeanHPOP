#include "timewidget.h"

TimeWidget::TimeWidget(QWidget *parent) : QWidget(parent)
{
    resize(parent->width(),200);

    timeDisplayLineEdit=new QLineEdit;
    timeDisplayLineEdit->setPlaceholderText("暂无时间");
    timeDisplayLineEdit->setFixedSize(300,25);

    timeSetLineEdit=new QLineEdit;
    timeSetLineEdit->setPlaceholderText("设置时间节点");
    timeSetLineEdit->setFixedSize(300,25);

    timeSetPushButton=new QPushButton("确认");
    timeSetPushButton->setFixedSize(50,25);

    dayTimeDrawArea=new DayTimeDrawArea(this);
    dayTimeDrawArea->show();
    dayTimeDrawArea->setFixedHeight(50);

    wholeTimeDrawArea=new WholeTimeDrawArea;
    wholeTimeDrawArea->setFixedHeight(25);

    timeLayout=new QGridLayout;
    timeLayout->setSpacing(0);
    timeLayout->addWidget(timeDisplayLineEdit,0,0,Qt::AlignLeft);
    timeLayout->addWidget(wholeTimeDrawArea,0,1,Qt::AlignLeft);
//    timeLayout->addWidget(timeSetLineEdit,1,0,Qt::AlignLeft);
//    timeLayout->addWidget(timeSetPushButton,2,0,Qt::AlignLeft);

    mainLayout=new QGridLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(dayTimeDrawArea,0,0,Qt::AlignLeft);
    mainLayout->addLayout(timeLayout,1,0,Qt::AlignLeft);
}

void TimeWidget::setTimeDisplay(int m)
{
    double date01,date02,date11,date12,fd;
    iauCal2jd(scenario->startYear,scenario->startMonth,scenario->startDay,&date01,&date02);
    date11=date01;
    date12=date02+scenario->startFd+satellite->time.at(m)/86400.0;
    int year,month,day,hour,minute,sec;
    iauJd2cal(date11,date12,&year,&month,&day,&fd);    

    hour=floor(fd*86400/3600);
    minute=floor((fd*86400-hour*3600)/60);
    sec=round(fd*86400-hour*3600-minute*60);

    QString ystr=QString::number(year);
    QString monthstr=QString::number(month);
    QString dstr=QString::number(day);
    QString fdstr=QString("%1:%2:%3").arg(hour,2,10,QLatin1Char('0')).arg(minute,2,10,QLatin1Char('0')).arg(sec,2,10,QLatin1Char('0'));
    timeDisplayLineEdit->setText("当前时间："+ystr+"-"+monthstr+"-"+dstr+" "+fdstr);

    QString mstr=QString::number(m);
    timeSetLineEdit->setText(mstr);
}

void TimeWidget::sendTimeCount()
{
    int m=timeSetLineEdit->text().toInt();
    emit sendTimeCountSignal(m);
}

void TimeWidget::getTime(Scenario *sc, Satellite *sa)
{
    scenario=sc;
    satellite=sa;
    dayTimeDrawArea->getDisplayTime(sc,sa);
    wholeTimeDrawArea->getSatellite(sa);
}

void TimeWidget::resizeEvent(QResizeEvent *)
{
    dayTimeDrawArea->resize(width()-25,50);
    wholeTimeDrawArea->resize(width()-325,25);
}
