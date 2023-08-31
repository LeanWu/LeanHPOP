#ifndef SCENARIO_H
#define SCENARIO_H

#include<QString>
#include<QFileDialog>
#include<QDebug>

#include"inputscenariowidget.h"

class Scenario
{
public:
    Scenario();
    int scenarioOrder;
    QString ScenarioName;
    InputScenarioWidget *inputScenarioWidget;//输入对话框

    void newScenario();//新建场景
    void setScenario();//设置场景
    void changeScenario();//改变场景
    void getScenarioTime(int *t1, int *t2,double *fd1,double *fd2);//得到场景时间

    void saveScenario();//保存场景
    void openScenario(int *t1, int *t2,double *fd1,double *fd2);//打开场景

    int startYear;
    int startMonth;
    int startDay;
    double startFd;

    int endYear;
    int endMonth;
    int endDay;
    double endFd;
};

#endif // SCENARIO_H
