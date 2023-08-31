#include "inputsatellitestartposwidget.h"

InputSatelliteStartPosWidget::InputSatelliteStartPosWidget(QWidget *parent) : QWidget(parent)
{
    aLabel=new QLabel("轨道半长轴：");
    aDoubleSpinBox=new QDoubleSpinBox;
    aDoubleSpinBox->setRange(0,DBL_MAX);
    aDoubleSpinBox->setSingleStep(100);
    aDoubleSpinBox->setValue(6600);
    aDoubleSpinBox->setSuffix(" km");

    eLabel=new QLabel("轨道偏心率：");
    eDoubleSpinBox=new QDoubleSpinBox;
    eDoubleSpinBox->setRange(0,DBL_MAX);
    eDoubleSpinBox->setDecimals(7);
    eDoubleSpinBox->setSingleStep(0.01);
    eDoubleSpinBox->setValue(0.01);

    iLabel=new QLabel("轨道倾角：");
    iDoubleSpinBox=new QDoubleSpinBox;
    iDoubleSpinBox->setRange(0,180);
    iDoubleSpinBox->setSingleStep(10);
    iDoubleSpinBox->setValue(30);
    iDoubleSpinBox->setSuffix(" deg");

    OmegaLabel=new QLabel("升交点赤经：");
    OmegaDoubleSpinBox=new QDoubleSpinBox;
    OmegaDoubleSpinBox->setRange(0,360);
    OmegaDoubleSpinBox->setSingleStep(10);
    OmegaDoubleSpinBox->setValue(0);
    OmegaDoubleSpinBox->setSuffix(" deg");

    omegaLabel=new QLabel("近地点辐角：");
    omegaDoubleSpinBox=new QDoubleSpinBox;
    omegaDoubleSpinBox->setRange(0,360);
    omegaDoubleSpinBox->setSingleStep(10);
    omegaDoubleSpinBox->setValue(0);
    omegaDoubleSpinBox->setSuffix(" deg");

    fLabel=new QLabel("真近点角：");
    fDoubleSpinBox=new QDoubleSpinBox;
    fDoubleSpinBox->setRange(0,360);
    fDoubleSpinBox->setSingleStep(10);
    fDoubleSpinBox->setValue(0);
    fDoubleSpinBox->setSuffix(" deg");

    satelliteOkPushButton=new QPushButton("确认");
    perturbationModelPushButton=new QPushButton("摄动力模型");

    startPosMainLayout=new QGridLayout(this);
    startPosMainLayout->addWidget(aLabel,0,0);
    startPosMainLayout->addWidget(aDoubleSpinBox,0,1);
    startPosMainLayout->addWidget(eLabel,1,0);
    startPosMainLayout->addWidget(eDoubleSpinBox,1,1);
    startPosMainLayout->addWidget(iLabel,2,0);
    startPosMainLayout->addWidget(iDoubleSpinBox,2,1);
    startPosMainLayout->addWidget(OmegaLabel,3,0);
    startPosMainLayout->addWidget(OmegaDoubleSpinBox,3,1);
    startPosMainLayout->addWidget(omegaLabel,4,0);
    startPosMainLayout->addWidget(omegaDoubleSpinBox,4,1);
    startPosMainLayout->addWidget(fLabel,5,0);
    startPosMainLayout->addWidget(fDoubleSpinBox,5,1);

    startPosMainLayout->addWidget(perturbationModelPushButton,6,0);
    startPosMainLayout->addWidget(satelliteOkPushButton,6,1);
}
