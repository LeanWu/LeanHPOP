#include "inputperturbationwidget.h"

InputPerturbationWidget::InputPerturbationWidget(QWidget *parent) : QWidget(parent)
{
    nonsphericalLavel=new QLabel("非球形引力");

    muLabel=new QLabel("地球引力系数：");
    muDoubleSpinBox=new QDoubleSpinBox;
    muDoubleSpinBox->setRange(0,DBL_MAX);
    muDoubleSpinBox->setDecimals(4);
    muDoubleSpinBox->setValue(3.986004415e5);
    muDoubleSpinBox->setSingleStep(100);
    muDoubleSpinBox->setSuffix(" km^3/s^2");

    ReLabel=new QLabel("赤道平均半径：");
    ReDoubleSpinBox=new QDoubleSpinBox;
    ReDoubleSpinBox->setRange(0,DBL_MAX);
    ReDoubleSpinBox->setDecimals(4);
    ReDoubleSpinBox->setValue(6378.1363);
    ReDoubleSpinBox->setSingleStep(1);
    ReDoubleSpinBox->setSuffix(" km");

    omegaevLabel=new QLabel("地球自转角速率：");
    omegaevDoubleSpinBox=new QDoubleSpinBox;
    omegaevDoubleSpinBox->setRange(0,DBL_MAX);
    omegaevDoubleSpinBox->setDecimals(11);
    omegaevDoubleSpinBox->setValue(7.292115e-5);
    omegaevDoubleSpinBox->setSingleStep(1e-5);
    omegaevDoubleSpinBox->setSuffix(" rad/s");

    feLabel=new QLabel("地球扁率：");
    feDoubleSpinBox=new QDoubleSpinBox;
    feDoubleSpinBox->setRange(0,DBL_MAX);
    feDoubleSpinBox->setDecimals(7);
    feDoubleSpinBox->setValue(1/298.257223563);
    feDoubleSpinBox->setSingleStep(1e-3);

    nonsphericalGridLayout=new QGridLayout;
    nonsphericalGridLayout->addWidget(nonsphericalLavel,0,0);
    nonsphericalGridLayout->addWidget(muLabel,1,0);
    nonsphericalGridLayout->addWidget(muDoubleSpinBox,1,1);
    nonsphericalGridLayout->addWidget(ReLabel,2,0);
    nonsphericalGridLayout->addWidget(ReDoubleSpinBox,2,1);
    nonsphericalGridLayout->addWidget(omegaevLabel,3,0);
    nonsphericalGridLayout->addWidget(omegaevDoubleSpinBox,3,1);
    nonsphericalGridLayout->addWidget(feLabel,4,0);
    nonsphericalGridLayout->addWidget(feDoubleSpinBox,4,1);

    dragLabel=new QLabel("大气阻力");

    CdLabel=new QLabel("阻力系数：");
    CdDoubleSpinBox=new QDoubleSpinBox;
    CdDoubleSpinBox->setRange(0,DBL_MAX);
    CdDoubleSpinBox->setDecimals(4);
    CdDoubleSpinBox->setValue(2.1);
    CdDoubleSpinBox->setSingleStep(0.1);

    SmLabel=new QLabel("卫星面质比：");
    SmDoubleSpinBox=new QDoubleSpinBox;
    SmDoubleSpinBox->setRange(0,DBL_MAX);
    SmDoubleSpinBox->setDecimals(4);
    SmDoubleSpinBox->setValue(0.0021);
    SmDoubleSpinBox->setSingleStep(1e-4);
    SmDoubleSpinBox->setSuffix("m^2/kg");

    FLabel=new QLabel("Daily F10.7：");
    FDoubleSpinBox=new QDoubleSpinBox;
    FDoubleSpinBox->setRange(0,DBL_MAX);
    FDoubleSpinBox->setDecimals(4);
    FDoubleSpinBox->setValue(180);
    FDoubleSpinBox->setSingleStep(10);

    FaLabel=new QLabel("Average F10.7：");
    FaDoubleSpinBox=new QDoubleSpinBox;
    FaDoubleSpinBox->setRange(0,DBL_MAX);
    FaDoubleSpinBox->setDecimals(4);
    FaDoubleSpinBox->setValue(180);
    FaDoubleSpinBox->setSingleStep(10);

    ApLabel=new QLabel("地磁系数：");
    ApDoubleSpinBox=new QDoubleSpinBox;
    ApDoubleSpinBox->setRange(0,DBL_MAX);
    ApDoubleSpinBox->setDecimals(4);
    ApDoubleSpinBox->setValue(15);
    ApDoubleSpinBox->setSingleStep(1);

    dragGridLayout=new QGridLayout;
    dragGridLayout->addWidget(dragLabel,0,0);
    dragGridLayout->addWidget(CdLabel,1,0);
    dragGridLayout->addWidget(CdDoubleSpinBox,1,1);
    dragGridLayout->addWidget(SmLabel,2,0);
    dragGridLayout->addWidget(SmDoubleSpinBox,2,1);
    dragGridLayout->addWidget(FLabel,3,0);
    dragGridLayout->addWidget(FDoubleSpinBox,3,1);
    dragGridLayout->addWidget(FaLabel,4,0);
    dragGridLayout->addWidget(FaDoubleSpinBox,4,1);
    dragGridLayout->addWidget(ApLabel,5,0);
    dragGridLayout->addWidget(ApDoubleSpinBox,5,1);

    solarPressureLabel=new QLabel("太阳光压力");
    CrLabel=new QLabel("太阳辐射系数：");
    CrDoubleSpinBox=new QDoubleSpinBox;
    CrDoubleSpinBox->setRange(0,DBL_MAX);
    CrDoubleSpinBox->setDecimals(4);
    CrDoubleSpinBox->setValue(1);
    CrDoubleSpinBox->setSingleStep(0.1);

    SmLabel1=new QLabel("卫星面质比：");
    SmDoubleSpinBox1=new QDoubleSpinBox;
    SmDoubleSpinBox1->setRange(0,DBL_MAX);
    SmDoubleSpinBox1->setDecimals(4);
    SmDoubleSpinBox1->setValue(0.0021);
    SmDoubleSpinBox1->setSingleStep(1e-4);
    SmDoubleSpinBox1->setSuffix("m^2/kg");

    solarPressureGridLayout=new QGridLayout;
    solarPressureGridLayout->addWidget(solarPressureLabel,0,0);
    solarPressureGridLayout->addWidget(CrLabel,1,0);
    solarPressureGridLayout->addWidget(CrDoubleSpinBox,1,1);
    solarPressureGridLayout->addWidget(SmLabel1,2,0);
    solarPressureGridLayout->addWidget(SmDoubleSpinBox1,2,1);

    thirdBodyLabel=new QLabel("第三体引力");
    sunCheckBox=new QCheckBox("Sun");
    sunCheckBox->setCheckState(Qt::Checked);
    moonCheckBox=new QCheckBox("Moon");
    moonCheckBox->setCheckState(Qt::Checked);

    thirdBodyGridLayout=new QGridLayout;
    thirdBodyGridLayout->addWidget(thirdBodyLabel,0,0);
    thirdBodyGridLayout->addWidget(sunCheckBox,1,0);
    thirdBodyGridLayout->addWidget(moonCheckBox,1,1);

    perturbationOkPushButton=new QPushButton("确认");

    perturbationMainLayout=new QGridLayout(this);
    perturbationMainLayout->addLayout(nonsphericalGridLayout,0,0);
    perturbationMainLayout->addLayout(dragGridLayout,0,1);
    perturbationMainLayout->addLayout(solarPressureGridLayout,1,0);
    perturbationMainLayout->addLayout(thirdBodyGridLayout,1,1);
    perturbationMainLayout->addWidget(perturbationOkPushButton,2,1);

}
