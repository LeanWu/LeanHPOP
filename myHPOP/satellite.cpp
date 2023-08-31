#include "satellite.h"

Satellite::Satellite()
{

}

void Satellite::newSatellite()
{
    static int satelliteNumber=1;

    satelliteName=QString("卫星%1").arg(satelliteNumber++);
    inputSatelliteStartPosWidget=new InputSatelliteStartPosWidget;
    this->inputSatelliteStartPosWidget->setWindowTitle(QString("%1初始位置设置").arg(satelliteName));
}

void Satellite::changeSatellite()
{
    inputSatelliteStartPosWidget=new InputSatelliteStartPosWidget;
    this->inputSatelliteStartPosWidget->setWindowTitle(QString("%1初始位置设置").arg(satelliteName));
}

void Satellite::getSatellteStartPos()
{
    this->a=inputSatelliteStartPosWidget->aDoubleSpinBox->value()*1e3;//单位为m
    this->e=inputSatelliteStartPosWidget->eDoubleSpinBox->value();
    this->i=inputSatelliteStartPosWidget->iDoubleSpinBox->value()*acos(-1.0)/180;
    this->Omega=inputSatelliteStartPosWidget->OmegaDoubleSpinBox->value()*acos(-1.0)/180;
    this->omega=inputSatelliteStartPosWidget->omegaDoubleSpinBox->value()*acos(-1.0)/180;
    this->f=inputSatelliteStartPosWidget->fDoubleSpinBox->value()*acos(-1.0)/180;
}

void Satellite::setPerturbationWidget()
{
    inputPerturbationWidget=new InputPerturbationWidget;
}

void Satellite::getPerPara(double *para)
{
    this->mu=this->inputPerturbationWidget->muDoubleSpinBox->value()*1e9;//单位为m^3/s^2
    this->sunIncluded=this->inputPerturbationWidget->sunCheckBox->isChecked();
    this->moonIncluded=this->inputPerturbationWidget->moonCheckBox->isChecked();
    this->Re=this->inputPerturbationWidget->ReDoubleSpinBox->value()*1e3;//单位为m
    this->Sm=this->inputPerturbationWidget->SmDoubleSpinBox->value();
    this->Cr=this->inputPerturbationWidget->CrDoubleSpinBox->value();
    this->Fa=this->inputPerturbationWidget->FaDoubleSpinBox->value();
    this->F=this->inputPerturbationWidget->FDoubleSpinBox->value();
    this->Ap=this->inputPerturbationWidget->ApDoubleSpinBox->value();
    this->fe=this->inputPerturbationWidget->feDoubleSpinBox->value();
    this->Cd=this->inputPerturbationWidget->CdDoubleSpinBox->value();
    this->omegaev=this->inputPerturbationWidget->omegaevDoubleSpinBox->value();

    para[0] = this->mu;
    para[1] = (this->mus)*(this->sunIncluded);
    para[2] = (this->mum)*(this->moonIncluded);
    para[3] = this->Re;
    para[4] = this->Sm;

    para[5] = this->Ls;
    para[6] = this->Cr;
    para[7] = this->Fa;
    para[8] = this->F;
    para[9] = this->Ap;

    para[10] = this->fe;
    para[11] = this->Cd;
    para[12] = this->c;
    para[13] = this->omegaev;
    para[14] = this->n;
}

void Satellite::getSatelliteOrbit()
{
    QFile file("temp.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream txtOutput(&file);
    QString str;
    QStringList strList;

    foreach(auto item,time)
    {
        time.removeOne(item);
    }
//    qDebug()<<time.size();
    foreach(auto item,rx)
    {
        rx.removeOne(item);
    }
//    qDebug()<<rx.size();
    foreach(auto item,ry)
    {
        ry.removeOne(item);
    }
//    qDebug()<<ry.size();
    foreach(auto item,rz)
    {
        rz.removeOne(item);
    }
//    qDebug()<<rz.size();
    foreach(auto item,vx)
    {
        vx.removeOne(item);
    }
//    qDebug()<<vx.size();
    foreach(auto item,vy)
    {
        vy.removeOne(item);
    }
//    qDebug()<<vy.size();
    foreach(auto item,vz)
    {
        vz.removeOne(item);
    }
//    qDebug()<<vz.size();

    for(int i=0;!txtOutput.atEnd();i++)
    {
        str=txtOutput.readLine();
        strList=str.split("  ");

        this->time.append(strList[0].toDouble());
        this->rx.append(strList[1].toDouble());
        this->ry.append(strList[2].toDouble());
        this->rz.append(strList[3].toDouble());
        this->vx.append(strList[4].toDouble());
        this->vy.append(strList[5].toDouble());
        this->vz.append(strList[6].toDouble());
    }
//    qDebug()<<this->time.size();
    file.close();
}

void Satellite::saveSatellite()
{
    QString fileName=QFileDialog::getSaveFileName(NULL,
                                                  QString("卫星数据"),
                                                  QString("."),
                                                  QString("Satellite files(*.mysa)"));
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out<<a<<endl;
    out<<e<<endl;
    out<<i<<endl;
    out<<Omega<<endl;
    out<<omega<<endl;
    out<<f<<endl;

    out<<mu<<endl;
    out<<sunIncluded<<endl;
    out<<moonIncluded<<endl;
    out<<Re<<endl;
    out<<Sm<<endl;
    out<<Cr<<endl;
    out<<Fa<<endl;
    out<<F<<endl;
    out<<Ap<<endl;
    out<<fe<<endl;
    out<<Cd<<endl;
    out<<omegaev<<endl;
    file.close();
}

void Satellite::openSatellite(double *para)
{
    QString fileName=QFileDialog::getOpenFileName(NULL,
                                                  QString("卫星数据"),
                                                  QString("."),
                                                  QString("Satellite files(*.mysa)"));
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString line[18];
    for(int i=0;i<18;i++)
    {
        line[i]=in.readLine();
    }

    a=line[0].toDouble();
    e=line[1].toDouble();
    i=line[2].toDouble();
    Omega=line[3].toDouble();
    omega=line[4].toDouble();
    f=line[5].toDouble();

    mu=line[6].toDouble();
    sunIncluded=bool(line[7].toInt());
    moonIncluded=bool(line[8].toInt());
    Re=line[9].toDouble();
    Sm=line[10].toDouble();
    Cr=line[11].toDouble();
    Fa=line[12].toDouble();
    F=line[13].toDouble();
    Ap=line[14].toDouble();
    fe=line[15].toDouble();
    Cd=line[16].toDouble();
    omegaev=line[17].toDouble();

    para[0] = this->mu;
    para[1] = (this->mus)*(this->sunIncluded);
    para[2] = (this->mum)*(this->moonIncluded);
    para[3] = this->Re;
    para[4] = this->Sm;

    para[5] = this->Ls;
    para[6] = this->Cr;
    para[7] = this->Fa;
    para[8] = this->F;
    para[9] = this->Ap;

    para[10] = this->fe;
    para[11] = this->Cd;
    para[12] = this->c;
    para[13] = this->omegaev;
    para[14] = this->n;

    file.close();
}
