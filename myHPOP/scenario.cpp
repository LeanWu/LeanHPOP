#include "scenario.h"

Scenario::Scenario()
{

}

void Scenario::newScenario()
{
    static int scenarioNumber=1;
    scenarioOrder=scenarioNumber;

    ScenarioName=QString("场景%1").arg(scenarioNumber++);
    inputScenarioWidget=new InputScenarioWidget;
    inputScenarioWidget->setWindowTitle(QString("%1时间设置").arg(ScenarioName));
}

void Scenario::changeScenario()
{
    inputScenarioWidget=new InputScenarioWidget;
    inputScenarioWidget->setWindowTitle(QString("%1时间设置").arg(ScenarioName));
}

void Scenario::setScenario()
{

}

void Scenario::getScenarioTime(int *t1, int *t2,double *fd1,double *fd2)
{
    this->startYear=this->inputScenarioWidget->startYearSpinBox->value();
    this->startMonth=this->inputScenarioWidget->startMonthSpinBox->value();
    this->startDay=this->inputScenarioWidget->startDaySpinBox->value();
    this->startFd=double((this->inputScenarioWidget->startHourSpinBox->value()*3600+this->inputScenarioWidget->startMinuteSpinBox->value()*60+this->inputScenarioWidget->startSecondSpinBox->value())/86400.0);
//    qDebug()<<"写入"<<this->startYear;
    this->endYear=this->inputScenarioWidget->endYearSpinBox->value();
    this->endMonth=this->inputScenarioWidget->endMonthSpinBox->value();
    this->endDay=this->inputScenarioWidget->endDaySpinBox->value();
    this->endFd=double((this->inputScenarioWidget->endHourSpinBox->value()*3600+this->inputScenarioWidget->endMinuteSpinBox->value()*60+this->inputScenarioWidget->endSecondSpinBox->value())/86400.0);

//    qDebug()<<this->startYear;
    *t1=this->startYear;
    *(t1+1)=this->startMonth;
    *(t1+2)=this->startDay;

    *t2=this->endYear;
    *(t2+1)=this->endMonth;
    *(t2+2)=this->endDay;

    *fd1=this->startFd;
    *fd2=this->endFd;
}

void Scenario::saveScenario()
{
    QString fileName=QFileDialog::getSaveFileName(NULL,
                                                  QString("场景数据"),
                                                  QString("."),
                                                  QString("Scenario files(*.mysc)"));
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out<<startYear<<endl;
    out<<startMonth<<endl;
    out<<startDay<<endl;
    out<<startFd<<endl;

    out<<endYear<<endl;
    out<<endMonth<<endl;
    out<<endDay<<endl;
    out<<endFd;
    file.close();
}

void Scenario::openScenario(int *t1, int *t2,double *fd1,double *fd2)
{
    QString fileName=QFileDialog::getOpenFileName(NULL,
                                                  QString("场景数据"),
                                                  QString("."),
                                                  QString("Scenario files(*.mysc)"));
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString line01=in.readLine();
    QString line02=in.readLine();
    QString line03=in.readLine();
    QString line04=in.readLine();

    QString line11=in.readLine();
    QString line12=in.readLine();
    QString line13=in.readLine();
    QString line14=in.readLine();

    startYear=line01.toInt();
    startMonth=line02.toInt();
    startDay=line03.toInt();
    startFd=line04.toDouble();

    endYear=line11.toInt();
    endMonth=line12.toInt();
    endDay=line13.toInt();
    endFd=line14.toDouble();

    *t1=this->startYear;
    *(t1+1)=this->startMonth;
    *(t1+2)=this->startDay;

    *t2=this->endYear;
    *(t2+1)=this->endMonth;
    *(t2+2)=this->endDay;

    *fd1=this->startFd;
    *fd2=this->endFd;

//    qDebug()<<startYear<<" "<<startMonth<<" "<<startDay<<" "<<startFd;
//    qDebug()<<endYear<<" "<<endMonth<<" "<<endDay<<" "<<endFd;
    file.close();
}
