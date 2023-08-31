#include "earth2d.h"

Earth2D::Earth2D(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/images/icon.png"));

    pix=new QPixmap;
    pix->load("://earth/Basic.bmp");
    satellitePix=new QPixmap;
    satellitePix->load("://images/satellite.png");

    zoomFactor=0.4;

    timer=new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timer()));
}

void Earth2D::getTime(Scenario *scenario)
{
    double utc1,utc2,tai1,tai2,tt1,tt2;
    iauCal2jd(scenario->startYear,scenario->startMonth,scenario->startDay,&utc1,&utc2);
    iauUtctai(utc1,utc2+scenario->startFd,&tai1,&tai2);
    iauTaitt(tai1,tai2,&tt1,&tt2);

    foreach(auto item,date1)
    {
        date1.removeOne(item);
    }
//    qDebug()<<date1.size();
    foreach(auto item,date2)
    {
        date2.removeOne(item);
    }
//    qDebug()<<date2.size();

    date1.append(tt1);
    date2.append(tt2);
}

void Earth2D::getSatelliteOrbit(Satellite *satellite)
{
    this->satellite=satellite;
    double M[9],recf[3],longi,phi,hi;
    double rj2000[3]={satellite->rx.at(0),satellite->ry.at(0),satellite->rz.at(0)};
    J20002ecf(date1.at(0), date2.at(0), M);
    matrixmulti(M, rj2000, recf, 2);
    iauGc2gd(1, recf, &longi, &phi, &hi);

    foreach(auto item,longitude)
    {
        longitude.removeOne(item);
    }
//    qDebug()<<longitude.size();
    foreach(auto item,latitude)
    {
        latitude.removeOne(item);
    }
//    qDebug()<<latitude.size();
    foreach(auto item,h)
    {
        h.removeOne(item);
    }
//    qDebug()<<h.size();

    longitude.append(longi);
    latitude.append(phi);
    h.append(hi);
    for(int i=1;i<satellite->time.size();i++)
    {
        double tt2=date2.at(0)+satellite->time.at(i)/86400.0;
        date2.append(tt2);

        double rj2000[3]={satellite->rx.at(i),satellite->ry.at(i),satellite->rz.at(i)};
        J20002ecf(date1.at(0), date2.at(i), M);
        matrixmulti(M, rj2000, recf, 2);
        iauGc2gd(1, recf, &longi, &phi, &hi);
        longitude.append(longi);
        latitude.append(phi);
        h.append(hi);
    }

//    for(int i=0;i<longitude.size();i++)
//    {
//        qDebug()<<longitude.at(i)<<" "<<latitude.at(i);
//    }
//    qDebug()<<longitude.size()<<" "<<satellite->calculateNumber;
    drawOrbit=true;
    timer->start(1);
    mCounts=0;
    update();
}

void Earth2D::paintEvent(QPaintEvent *)
{
    QPainter painter(this);   
    painter.drawPixmap(0,0,zoomFactor*pix->width(),zoomFactor*pix->height(),*pix);

    QPen pen;
    pen.setColor( QColor(102,139,139) );
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(0.5);
    painter.setPen(pen);

    QFont font;
    font.setFamily("宋体");
    font.setPixelSize(20);
    painter.setFont(font);

    //经纬度
    QPoint startPos;
    QPoint endPos;
    for(int i=1;i<12;i++){
        double longituded=i/12.0;
        double longitude=360*longituded-180;
        QString str=QString::number(longitude,'f',0);
        startPos.setX(longituded*width());
        startPos.setY(0);
        endPos.setX(longituded*width());
        endPos.setY(height());
        painter.drawLine(startPos,endPos);
        painter.drawText(endPos,str);
    }
    for(int i=1;i<6;i++){
        double latituded=i/6.0;
        double latitude=-180*latituded+90;
        QString str=QString::number(latitude,'f',0);
        startPos.setX(0);
        startPos.setY(latituded*height());
        endPos.setX(width());
        endPos.setY(latituded*height());
        painter.drawLine(startPos,endPos);
        painter.drawText(startPos,str);
    }

    if(drawOrbit==true)
    {
        pen.setColor( QColor(122,197,205) );
        pen.setStyle(Qt::SolidLine);
        pen.setWidthF(2);
        painter.setPen(pen);

        //卫星轨道各点经纬度及对应图点
        QPointF points[longitude.size()],llpoints[longitude.size()];
        for(int i=0;i<longitude.size();i++)
        {
            llpoints[i].setX(longitude.at(i)*180/acos(-1.0));
            llpoints[i].setY(latitude.at(i)*180/acos(-1.0));
            points[i].setX((longitude.at(i)*180/acos(-1.0)+180)*width()/360);
            points[i].setY(-(latitude.at(i)*180/acos(-1.0)-90)*height()/180);
        }        
        //获取跨180°的圈数节点
        foreach(auto item,TurnNumber)
        {
            TurnNumber.removeOne(item);
        }
        for(int i=0;i<longitude.size()-1;i++)
        {
            if(abs(llpoints[i].x()-llpoints[i+1].x())>300)
            {
                TurnNumber.append(i);
            }
        }
//        qDebug()<<TurnNumber.size();
//        for(int i=0;i<TurnNumber.size();i++)
//        {
//            qDebug()<<i<<" "<<TurnNumber.at(i);
//        }

        //绘制卫星
//        qDebug()<<mCounts;
        if(mCounts>=longitude.size())
        {
            mCounts=0;
        }

        QPointF satellitePos;
        satellitePos.setX(points[mCounts].x());
        satellitePos.setY(points[mCounts].y());        

        QRectF target(satellitePos.x()-0.5*0.1*satellitePix->width(),satellitePos.y()-0.5*0.1*satellitePix->height(),0.1*satellitePix->width(),0.1*satellitePix->height());
        QRectF source(0,0,satellitePix->width(),satellitePix->height());
        painter.drawPixmap(target,*satellitePix,source);

        //绘制跨180°的轨道各圈
        if(TurnNumber.size()!=0)
        {
            if(drawAllOrbit==true)//绘制所有轨道
            {
                //第一圈
                {
                    int drawNumber=TurnNumber.at(0)+1;
                    QPointF drawPoints[drawNumber];
                    for(int j=0;j<drawNumber;j++)
                    {
                        drawPoints[j].setX(points[j].x());
                        drawPoints[j].setY(points[j].y());
                    }
                    painter.drawPolyline(drawPoints,drawNumber);
                }
                //中间圈
                for(int i=1;i<TurnNumber.size();i++)
                {
                    int drawNumber=TurnNumber.at(i)-TurnNumber.at(i-1);
                    QPointF drawPoints[drawNumber];
                    for(int j=0;j<drawNumber;j++)
                    {
                        drawPoints[j].setX(points[j+TurnNumber.at(i-1)+1].x());
                        drawPoints[j].setY(points[j+TurnNumber.at(i-1)+1].y());
                    }
                    painter.drawPolyline(drawPoints,drawNumber);
                }
                //最后一圈
                {
                    int drawNumber=longitude.size()-1-TurnNumber.last();
                    QPointF drawPoints[drawNumber];
                    for(int j=0;j<drawNumber;j++)
                    {
                        drawPoints[j].setX(points[j+TurnNumber.last()+1].x());
                        drawPoints[j].setY(points[j+TurnNumber.last()+1].y());
                    }
                    painter.drawPolyline(drawPoints,drawNumber);
                }
            }
            else if(drawAllOrbit==false)//绘制卫星当前圈轨道
            {
                int drawIndex;//获取当前圈
                if(mCounts<=TurnNumber.at(0))
                {
                    drawIndex=0;
                }
                else if(mCounts>TurnNumber.last())
                {
                    drawIndex=TurnNumber.size();
                }
                else
                {
                    for(int i=0;i<TurnNumber.size()-1;i++)
                    {
                        if(mCounts>TurnNumber.at(i) and mCounts<=TurnNumber.at(i+1))
                        {
                            drawIndex=i+1;
                        }
                    }
                }

                //绘制指定圈
                if(drawIndex==0)//第一圈
                {
                    int drawNumber=TurnNumber.at(0)+1;
                    QPointF drawPoints[drawNumber];
                    for(int j=0;j<drawNumber;j++)
                    {
                        drawPoints[j].setX(points[j].x());
                        drawPoints[j].setY(points[j].y());
                    }
                    painter.drawPolyline(drawPoints,drawNumber);
                }
                else if(drawIndex==TurnNumber.size())//最后一圈
                {
                    int drawNumber=longitude.size()-1-TurnNumber.last();
                    QPointF drawPoints[drawNumber];
                    for(int j=0;j<drawNumber;j++)
                    {
                        drawPoints[j].setX(points[j+TurnNumber.last()+1].x());
                        drawPoints[j].setY(points[j+TurnNumber.last()+1].y());
                    }
                    painter.drawPolyline(drawPoints,drawNumber);
                }
                else//中间各圈
                {
                    int drawNumber=TurnNumber.at(drawIndex)-TurnNumber.at(drawIndex-1);
                    QPointF drawPoints[drawNumber];
                    for(int j=0;j<drawNumber;j++)
                    {
                        drawPoints[j].setX(points[j+TurnNumber.at(drawIndex-1)+1].x());
                        drawPoints[j].setY(points[j+TurnNumber.at(drawIndex-1)+1].y());
                    }
                    painter.drawPolyline(drawPoints,drawNumber);
                }
            }
        }
        //绘制不跨180°的轨道各圈
        else
        {
            painter.drawPolyline(points,longitude.size());
        }
    }
}

void Earth2D::on_timer()
{    
    mCounts++;
    if(mCounts>=longitude.size())
    {        
        timer->stop();
        finishOrbit=true;
        mCounts=0;
//        qDebug()<<mCounts;
//        qDebug()<<"end:"<<longitude.size();
    }
    update();
//    qDebug()<<longitude.size();
}

void Earth2D::startOrPauseSatellite()
{
    if(startOrPause==false)
    {
        timer->stop();
    }
    else
    {
        timer->start(1);
    }
}

void Earth2D::sendmCounts()
{
    emit sendmCountsSignal(mCounts);
}

void Earth2D::acceptmCount(int m)
{
    mCounts=m;
    update();
}

void Earth2D::sendFinishOrbit()
{
    emit sendFinishOrbitSignal(finishOrbit);
}
