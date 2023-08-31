#include "daytimedrawarea.h"

DayTimeDrawArea::DayTimeDrawArea(QWidget *parent) : QWidget(parent)
{
}

void DayTimeDrawArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QColor(255,222,173));
    painter.drawRect(rect());

    QPen pen;
    pen.setColor( QColor(0,0,0) );
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    painter.setPen(pen);

    QFont font;
    font.setFamily("宋体");
    int m=width()/120;
    font.setPixelSize(m);
    painter.setFont(font);

    pix.load(":/images/arrowup.png");
    QPoint startPos;
    QPoint endPos;
    for(int i=0;i<25;i++)
    {
        double daytimex=i*width()/24;
        QString str=QString("%1:00").arg(i,2,10,QLatin1Char('0'));
        startPos.setX(daytimex);
        startPos.setY(0);
        endPos.setX(daytimex);
        endPos.setY(20);
        painter.drawLine(startPos,endPos);
        endPos.setY(50);
        painter.drawText(endPos,str);
    }
    for(int i=0;i<145;i++)
    {
        double daytimex=i*width()/144;
        startPos.setX(daytimex);
        startPos.setY(0);
        endPos.setX(daytimex);
        endPos.setY(10);
        painter.drawLine(startPos,endPos);
    }
    if(scenario!=nullptr and satellite!=nullptr)
    {
        double date01,date02,date11,date12,fd;
        iauCal2jd(scenario->startYear,scenario->startMonth,scenario->startDay,&date01,&date02);
        date11=date01;
        date12=date02+scenario->startFd+satellite->time.at(mCounts)/86400.0;
        iauJd2cal(date11,date12,&year,&month,&day,&fd);

        double satelliteTimex=width()*fd;
        startPos.setX(satelliteTimex);
        startPos.setY(0);
        endPos.setX(satelliteTimex);
        endPos.setY(50);
        pen.setWidthF(2);
        painter.drawLine(startPos,endPos);
        painter.drawPixmap(startPos.x()-0.25*pix.width(),startPos.y()+40,0.5*pix.width(),0.5*pix.height(),pix);
    }

}

void DayTimeDrawArea::acceptCounts(int m)
{
    mCounts=m;
    update();
//    qDebug()<<mCounts;
}

void DayTimeDrawArea::getDisplayTime(Scenario *sc, Satellite *sa)
{
    scenario=sc;
    satellite=sa;
    mCounts=0;
}

void DayTimeDrawArea::sendTimeCount()
{
    emit sendTimeCountSignal(sendCounts);
//    qDebug()<<sendCounts;
}

void DayTimeDrawArea::mousePressEvent(QMouseEvent *e)
{
    if(scenario!=nullptr and satellite!=nullptr)
    {
        double fd=e->x()/double(width());
        getSendCounts(fd);
        sendTimeCount();
    }
}

void DayTimeDrawArea::mouseMoveEvent(QMouseEvent *e)
{
    if(scenario!=nullptr and satellite!=nullptr)
    {
        double fd=e->x()/double(width());
        getSendCounts(fd);
        sendTimeCount();
    }
}

void DayTimeDrawArea::getSendCounts(double fd)
{
    double date01,date02,date11,date12;
    iauCal2jd(scenario->startYear,scenario->startMonth,scenario->startDay,&date01,&date02);
    iauCal2jd(year,month,day,&date11,&date12);

    if(fd<=0)
        fd=0;
    else if(fd>=1)
        fd=1;
//    qDebug()<<fd;
//    qDebug()<<day;

    double time=(fd-scenario->startFd+date11+date12-date01-date02)*86400;
//    qDebug()<<time;
    if(time<0)
    {
        sendCounts=0;
    }
    if(time>satellite->time.last())
    {
        sendCounts=satellite->time.size()-1;
    }
    for(int i=0;i<satellite->time.size()-1;i++)
    {
        if(time>=satellite->time.at(i) and time<=satellite->time.at(i+1) and fd!=0 and fd!=1)
        {
            double a=satellite->time.at(i),b=satellite->time.at(i+1);
            if((time-a)<(b-time))
            {
                sendCounts=i;
            }
            else
            {
                sendCounts=i+1;
            }
        }
        else if(time>=satellite->time.at(i) and time<=satellite->time.at(i+1) and fd==0)
        {
            sendCounts=i+1;
        }
        else if(time>=satellite->time.at(i) and time<=satellite->time.at(i+1) and fd==1)
        {
            sendCounts=i;
        }
    }
}
