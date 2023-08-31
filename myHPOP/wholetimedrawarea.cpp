#include "wholetimedrawarea.h"

WholeTimeDrawArea::WholeTimeDrawArea(QWidget *parent) : QWidget(parent)
{    
}

void WholeTimeDrawArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QColor(0,238,238));
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

    pix.load(":/images/arrow.png");
    QPoint startPos;
    QPoint endPos;
    for(int i=0;i<10;i++)
    {
        double wholetimex=i*width()/10;
        QString str=QString("%1%").arg(i*10);
        startPos.setX(wholetimex);
        startPos.setY(0);
        endPos.setX(wholetimex);
        endPos.setY(10);
        painter.drawLine(startPos,endPos);
        endPos.setY(25);
        painter.drawText(endPos,str);
    }
    if(satellite!=nullptr)
    {
//        qDebug()<<satellite->time.size();
        double satelliteTimex=width()*(satellite->time.at(mCounts)-satellite->time.at(0))/(satellite->time.last()-satellite->time.at(0));
        startPos.setX(satelliteTimex);
        startPos.setY(0);
        endPos.setX(satelliteTimex);
        endPos.setY(25);
        pen.setWidthF(2);
        painter.drawLine(startPos,endPos);
        painter.drawPixmap(startPos.x()-0.25*pix.width(),startPos.y(),0.5*pix.width(),0.5*pix.height(),pix);
    }
}

void WholeTimeDrawArea::acceptCounts(int m)
{
    mCounts=m;
    update();
//    qDebug()<<mCounts;
}

void WholeTimeDrawArea::getSatellite(Satellite *sa)
{
    satellite=sa;
    mCounts=0;
}

void WholeTimeDrawArea::mousePressEvent(QMouseEvent *e)
{
//    qDebug()<<e->x();
    if(satellite!=nullptr)
    {
        double time=e->x()*(satellite->time.last()-satellite->time.at(0))/width()+satellite->time.at(0);
        getSendCounts(time);
        if (sendCounts>=satellite->time.size())
            sendCounts=satellite->time.size()-1;
        if (sendCounts<0)
            sendCounts=0;
    }
    sendTimeCount();
//    qDebug()<<sendCounts;
}

void WholeTimeDrawArea::mouseMoveEvent(QMouseEvent *e)
{
    if(satellite!=nullptr)
    {
        double time=e->x()*(satellite->time.last()-satellite->time.at(0))/width()+satellite->time.at(0);
        getSendCounts(time);
        if (sendCounts>=satellite->time.size())
            sendCounts=satellite->time.size()-1;
        if (sendCounts<0)
            sendCounts=0;
    }
    sendTimeCount();
}

void WholeTimeDrawArea::sendTimeCount()
{
    emit sendTimeCountSignal(sendCounts);
//    qDebug()<<sendCounts;
}

void WholeTimeDrawArea::getSendCounts(double time)
{
    for(int i=0;i<satellite->time.size()-1;i++)
    {
        if(time>=satellite->time.at(i) and time<=satellite->time.at(i+1))
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
    }
}
