#include "inputscenariowidget.h"

InputScenarioWidget::InputScenarioWidget(QWidget *parent) : QWidget(parent)
{
    //开始时间设置
    startTimeLabel=new QLabel("开始时间：");

    startYearLabel=new QLabel("年");
    startYearSpinBox=new QSpinBox;
    startYearSpinBox->setSingleStep(1);
    startYearSpinBox->setMinimum(0);
    startYearSpinBox->setMaximum(INT_MAX);
    startYearSpinBox->setValue(2020);

    startMonthLabel=new QLabel("月");
    startMonthSpinBox=new QSpinBox;
    startMonthSpinBox->setSingleStep(1);
    startMonthSpinBox->setMinimum(1);
    startMonthSpinBox->setMaximum(12);
    startMonthSpinBox->setValue(12);

    startDayLabel=new QLabel("日");
    startDaySpinBox=new QSpinBox;
    startDaySpinBox->setSingleStep(1);
    startDaySpinBox->setMinimum(1);
    startDaySpinBox->setMaximum(31);
    startDaySpinBox->setValue(1);

    startHourLabel=new QLabel("时");
    startHourSpinBox=new QSpinBox;
    startHourSpinBox->setSingleStep(1);
    startHourSpinBox->setMinimum(0);
    startHourSpinBox->setMaximum(23);
    startHourSpinBox->setValue(12);

    startMinuteLabel=new QLabel("分");
    startMinuteSpinBox=new QSpinBox;
    startMinuteSpinBox->setSingleStep(1);
    startMinuteSpinBox->setMinimum(0);
    startMinuteSpinBox->setMaximum(59);
    startMinuteSpinBox->setValue(0);

    startSecondLabel=new QLabel("秒");
    startSecondSpinBox=new QSpinBox;
    startSecondSpinBox->setSingleStep(1);
    startSecondSpinBox->setMinimum(0);
    startSecondSpinBox->setMaximum(59);
    startSecondSpinBox->setValue(0);

    //结束时间设置
    endTimeLabel=new QLabel("结束时间：");

    endYearLabel=new QLabel("年");
    endYearSpinBox=new QSpinBox;
    endYearSpinBox->setSingleStep(1);
    endYearSpinBox->setMinimum(0);
    endYearSpinBox->setMaximum(INT_MAX);
    endYearSpinBox->setValue(2020);

    endMonthLabel=new QLabel("月");
    endMonthSpinBox=new QSpinBox;
    endMonthSpinBox->setSingleStep(1);
    endMonthSpinBox->setMinimum(1);
    endMonthSpinBox->setMaximum(12);
    endMonthSpinBox->setValue(12);

    endDayLabel=new QLabel("日");
    endDaySpinBox=new QSpinBox;
    endDaySpinBox->setSingleStep(1);
    endDaySpinBox->setMinimum(1);
    endDaySpinBox->setMaximum(31);
    endDaySpinBox->setValue(2);

    endHourLabel=new QLabel("时");
    endHourSpinBox=new QSpinBox;
    endHourSpinBox->setSingleStep(1);
    endHourSpinBox->setMinimum(0);
    endHourSpinBox->setMaximum(23);
    endHourSpinBox->setValue(12);

    endMinuteLabel=new QLabel("分");
    endMinuteSpinBox=new QSpinBox;
    endMinuteSpinBox->setSingleStep(1);
    endMinuteSpinBox->setMinimum(0);
    endMinuteSpinBox->setMaximum(59);
    endMinuteSpinBox->setValue(0);

    endSecondLabel=new QLabel("秒");
    endSecondSpinBox=new QSpinBox;
    endSecondSpinBox->setSingleStep(1);
    endSecondSpinBox->setMinimum(0);
    endSecondSpinBox->setMaximum(59);
    endSecondSpinBox->setValue(0);

    okPushButton=new QPushButton("确认");

    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(startTimeLabel,0,0);
    mainLayout->addWidget(startYearSpinBox,0,1);
    mainLayout->addWidget(startYearLabel,0,2);
    mainLayout->addWidget(startMonthSpinBox,0,3);
    mainLayout->addWidget(startMonthLabel,0,4);
    mainLayout->addWidget(startDaySpinBox,0,5);
    mainLayout->addWidget(startDayLabel,0,6);
    mainLayout->addWidget(startHourSpinBox,0,7);
    mainLayout->addWidget(startHourLabel,0,8);
    mainLayout->addWidget(startMinuteSpinBox,0,9);
    mainLayout->addWidget(startMinuteLabel,0,10);
    mainLayout->addWidget(startSecondSpinBox,0,11);
    mainLayout->addWidget(startSecondLabel,0,12);

    mainLayout->addWidget(endTimeLabel,1,0);
    mainLayout->addWidget(endYearSpinBox,1,1);
    mainLayout->addWidget(endYearLabel,1,2);
    mainLayout->addWidget(endMonthSpinBox,1,3);
    mainLayout->addWidget(endMonthLabel,1,4);
    mainLayout->addWidget(endDaySpinBox,1,5);
    mainLayout->addWidget(endDayLabel,1,6);
    mainLayout->addWidget(endHourSpinBox,1,7);
    mainLayout->addWidget(endHourLabel,1,8);
    mainLayout->addWidget(endMinuteSpinBox,1,9);
    mainLayout->addWidget(endMinuteLabel,1,10);
    mainLayout->addWidget(endSecondSpinBox,1,11);
    mainLayout->addWidget(endSecondLabel,1,12);

    mainLayout->addWidget(okPushButton,2,11);
}
