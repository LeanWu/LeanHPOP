#ifndef SATELLITE_H
#define SATELLITE_H

#include<QString>
#include<QList>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
#include"inputsatellitestartposwidget.h"
#include"inputperturbationwidget.h"

class Satellite
{
public:
    Satellite();
    QString satelliteName;

    //初始位置参数
    double a;
    double e;
    double i;
    double Omega;
    double omega;
    double f;

    QList<double> time;
    QList<double> rx;
    QList<double> ry;
    QList<double> rz;
    QList<double> vx;
    QList<double> vy;
    QList<double> vz;

    InputSatelliteStartPosWidget *inputSatelliteStartPosWidget;//初始位置输入对话框
    InputPerturbationWidget *inputPerturbationWidget;//摄动力模型输入对话框
    void newSatellite();//新建卫星
    void setSatellite();//设置卫星
    void changeSatellite();//改变场景
    void getSatellteStartPos();//得到卫星初始根数
    void setPerturbationWidget();//设置摄动力模型
    void getPerPara(double *para);//得到摄动力基本参数
    void getSatelliteOrbit();//得到结果数据

    void saveSatellite();//保存卫星
    void openSatellite(double *para);//打开卫星

private:
    double mu;
    double mus=1.32712e20;
    bool sunIncluded;
    double mum=4.903e12;
    bool moonIncluded;
    double Re;
    double Sm;
    double Ls=3.823e26;
    double Cr;
    double Fa;
    double F;
    double Ap;
    double fe;
    double Cd;
    double c=2.99792458e8;
    double omegaev;
    double n=5;
};

#endif // SATELLITE_H
