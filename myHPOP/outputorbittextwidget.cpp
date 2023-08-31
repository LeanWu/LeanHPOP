#include "outputorbittextwidget.h"
#include<QDebug>

OutputOrbitTextWidget::OutputOrbitTextWidget(Scenario *scenario,Satellite *satellite,QWidget *parent) : QWidget(parent)
{
    orbitTextEdit=new QTextEdit(this);
    orbitTextEdit->setReadOnly(true);
//    qDebug()<<satellite->calculateNumber;

    QString title("");
    title+=QString("%1").arg("时间",16,' ');
    title+=QString("%1").arg("x(m)",14,' ');
    title+=QString("%1").arg("y(m)",14,' ');
    title+=QString("%1").arg("z(m)",14,' ');
    title+=QString("%1").arg("vx(m/s)",14,' ');
    title+=QString("%1").arg("vy(m/s)",14,' ');
    title+=QString("%1").arg("vz(m/s)",14,' ');
    title+="\n";
    orbitTextEdit->insertPlainText(title);
    for(int i=0;i<satellite->time.size();i++)
    {
        orbitText.clear();

        double date01,date02,date11,date12,fd;
        iauCal2jd(scenario->startYear,scenario->startMonth,scenario->startDay,&date01,&date02);
        date11=date01;
        date12=date02+scenario->startFd+satellite->time.at(i)/86400.0;
        int year,month,day,hour,minute,sec;
        iauJd2cal(date11,date12,&year,&month,&day,&fd);

        hour=floor(fd*86400/3600);
        minute=floor((fd*86400-hour*3600)/60);
        sec=round(fd*86400-hour*3600-minute*60);

        QString ystr=QString::number(year);
        QString monthstr=QString::number(month);
        QString dstr=QString::number(day);
        QString fdstr=QString("%1:%2:%3").arg(hour,2,10,QLatin1Char('0')).arg(minute,2,10,QLatin1Char('0')).arg(sec,2,10,QLatin1Char('0'));
        orbitText+=QString("%1-%2-%3-%4").arg(ystr).arg(monthstr).arg(dstr).arg(fdstr);

//        orbitNumber=QString::number(satellite->time.at(i),'f',2);
//        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitNumber=QString::number(satellite->rx.at(i),'f',2);
        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitNumber=QString::number(satellite->ry.at(i),'f',2);
        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitNumber=QString::number(satellite->rz.at(i),'f',2);
        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitNumber=QString::number(satellite->vx.at(i),'f',2);
        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitNumber=QString::number(satellite->vy.at(i),'f',2);
        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitNumber=QString::number(satellite->vz.at(i),'f',2);
        orbitText+=QString("%1").arg(orbitNumber,14,' ');
        orbitText+="\n";
        orbitTextEdit->insertPlainText(orbitText);
    }

    orbitTextGridLayout=new QGridLayout(this);
    orbitTextGridLayout->addWidget(orbitTextEdit,0,0);
}
