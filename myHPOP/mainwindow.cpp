#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化
    setWindowTitle("myorbit");
    setWindowIcon(QIcon(":/images/icon.png"));

    mdiArea=new QMdiArea(this);
    setCentralWidget(mdiArea);
//    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    earth2Dsub=new QMdiSubWindow(mdiArea);
    earth2D=new Earth2D;
    earth2Dsub->setWidget(earth2D);
    earth2Dsub->setAttribute(Qt::WA_DeleteOnClose);
    earth2Dsub->show();
    earth2D->setFixedSize(earth2D->zoomFactor*earth2D->pix->size());
    connect(earth2D,&Earth2D::sendFinishOrbitSignal,this,&MainWindow::finishOrbitYes);

    earth3Dsub=new QMdiSubWindow(mdiArea);
    earth3D=new Earth3D(earth2D);
    earth3Dsub->setWidget(earth3D);
    earth3Dsub->setAttribute(Qt::WA_DeleteOnClose);
    earth3Dsub->show();

    itemDockWidget=new QDockWidget("对象窗口",this);
    addDockWidget(Qt::LeftDockWidgetArea,itemDockWidget);

    timeDockWidget=new QDockWidget("时间窗口",this);
    addDockWidget(Qt::BottomDockWidgetArea,timeDockWidget);
    timeDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
    timeDockWidget->resize(width(),200);
    timeWidgetSet();

    timer=new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timer()));

    itemTreeWidget=new QTreeWidget(itemDockWidget);
    itemDockWidget->setWidget(itemTreeWidget);
    itemTreeWidget->setHeaderLabel("暂无对象");
//    updateMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNewScenario_triggered()
{
    if(scenarioTreeWidgetItem!=nullptr)
    {
        disconnect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showScenario(QTreeWidgetItem*,int)));
    }
    //对象树设置
    itemTreeWidget->setHeaderLabel("对象");
    scenarioTreeWidgetItem=new QTreeWidgetItem(itemTreeWidget);
    scenario=new Scenario;
    scenario->newScenario();
    scenarioTreeWidgetItem->setText(0,scenario->ScenarioName);

    connect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showScenario(QTreeWidgetItem*,int)));

    //工作区设置
    mdiArea->addSubWindow(scenario->inputScenarioWidget);
    scenario->inputScenarioWidget->show();
    scenario->inputScenarioWidget->setAttribute(Qt::WA_DeleteOnClose);
    connect(scenario->inputScenarioWidget->okPushButton,SIGNAL(clicked()),this,SLOT(setScenarioTime()));
    connect(scenario->inputScenarioWidget->okPushButton,SIGNAL(clicked()),mdiArea,SLOT(closeActiveSubWindow()));

//    updateMenu();
}

void MainWindow::showScenario(QTreeWidgetItem* in1,int)
{
    if(in1==scenarioTreeWidgetItem)
    {
        scenario->changeScenario();
        mdiArea->addSubWindow(scenario->inputScenarioWidget);
        scenario->inputScenarioWidget->show();
        scenario->inputScenarioWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(scenario->inputScenarioWidget->okPushButton,SIGNAL(clicked()),this,SLOT(setScenarioTime()));
        connect(scenario->inputScenarioWidget->okPushButton,SIGNAL(clicked()),mdiArea,SLOT(closeActiveSubWindow()));
    }
}

void MainWindow::setScenarioTime()
{
    scenario->getScenarioTime(t1,t2,&fd1,&fd2);
}

void MainWindow::on_actionInsertSatellite_triggered()
{
    if(scenario==nullptr)
    {
        QString text="未创建场景，请先创建场景";
        QMessageBox::warning(this,"错误",text);
    }
    else
    {
        if(satelliteTreeWidgetItem!=nullptr)
        {
            disconnect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSatellite(QTreeWidgetItem*,int)));
        }
        //对象树设置
        satelliteTreeWidgetItem=new QTreeWidgetItem(scenarioTreeWidgetItem);
        satellite=new Satellite;
        satellite->newSatellite();
        satelliteTreeWidgetItem->setText(0,satellite->satelliteName);

        connect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSatellite(QTreeWidgetItem*,int)));

        //工作区设置
        mdiArea->addSubWindow(satellite->inputSatelliteStartPosWidget);
        satellite->inputSatelliteStartPosWidget->show();
        satellite->inputSatelliteStartPosWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(satellite->inputSatelliteStartPosWidget->satelliteOkPushButton,SIGNAL(clicked()),this,SLOT(setSatellteStartPos()));
        connect(satellite->inputSatelliteStartPosWidget->satelliteOkPushButton,SIGNAL(clicked()),mdiArea,SLOT(closeActiveSubWindow()));

        connect(satellite->inputSatelliteStartPosWidget->perturbationModelPushButton,SIGNAL(clicked()),this,SLOT(showPerturbationWidget()));
    }

//    updateMenu();
}

void MainWindow::showSatellite(QTreeWidgetItem* in1,int)
{
    if(in1==satelliteTreeWidgetItem)
    {
        satellite->changeSatellite();

        mdiArea->addSubWindow(satellite->inputSatelliteStartPosWidget);
        satellite->inputSatelliteStartPosWidget->show();
        satellite->inputSatelliteStartPosWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(satellite->inputSatelliteStartPosWidget->satelliteOkPushButton,SIGNAL(clicked()),this,SLOT(setSatellteStartPos()));
        connect(satellite->inputSatelliteStartPosWidget->satelliteOkPushButton,SIGNAL(clicked()),mdiArea,SLOT(closeActiveSubWindow()));

        connect(satellite->inputSatelliteStartPosWidget->perturbationModelPushButton,SIGNAL(clicked()),this,SLOT(showPerturbationWidget()));
    }
}

void MainWindow::setSatellteStartPos()
{
    satellite->getSatellteStartPos();
//    qDebug()<<satellite->a;
}

void MainWindow::showPerturbationWidget()
{
    satellite->setPerturbationWidget();
    mdiArea->addSubWindow(satellite->inputPerturbationWidget);
    satellite->inputPerturbationWidget->show();
    satellite->inputPerturbationWidget->setAttribute(Qt::WA_DeleteOnClose);
    connect(satellite->inputPerturbationWidget->perturbationOkPushButton,SIGNAL(clicked()),this,SLOT(setPerPara()));
    connect(satellite->inputPerturbationWidget->perturbationOkPushButton,SIGNAL(clicked()),mdiArea,SLOT(closeActiveSubWindow()));
}

void MainWindow::setPerPara()
{
    satellite->getPerPara(para);
//    for(int i=0;i<15;i++)
//        qDebug()<<para[i];
}

void MainWindow::on_actionCalculate_triggered()
{
    if(satellite==nullptr)
    {
        QString text="未创建卫星，请先创建卫星";
        QMessageBox::warning(this,"错误",text);
    }
    else
    {
        double rv[6]={0};
        rorbit(this->satellite->a, this->satellite->e, this->satellite->i, this->satellite->Omega, this->satellite->omega, this->satellite->f, para[0], rv);

        int a;
        TBAll(rv, t1, t2, fd1, fd2, para,&a);

        satellite->getSatelliteOrbit();
        earth2D->getTime(scenario);
        earth2D->getSatelliteOrbit(satellite);

        mdiArea->setActiveSubWindow(earth3Dsub);
        mdiArea->closeActiveSubWindow();
        earth3Dsub=new QMdiSubWindow(mdiArea);
        earth3D=new Earth3D(earth2D);
        earth3Dsub->setWidget(earth3D);
        earth3Dsub->show();
        earth3Dsub->setAttribute(Qt::WA_DeleteOnClose);

        ui->actionPlayPause->setIcon(QIcon("://images/pause.png"));
        earth2D->startOrPause=true;

        timeWidget->getTime(scenario,satellite);

        timer->start(1);
    }

//    updateMenu();
}

void MainWindow::on_actionOutputOrbitText_triggered()
{
    if(satellite==nullptr)
    {
        QString text="未创建卫星，请先创建卫星";
        QMessageBox::warning(this,"错误",text);
    }
    else
    {
        outputOrbitTextWidget=new OutputOrbitTextWidget(scenario,satellite);

        mdiArea->addSubWindow(this->outputOrbitTextWidget);
        this->outputOrbitTextWidget->showMaximized();
        this->outputOrbitTextWidget->setAttribute(Qt::WA_DeleteOnClose);
    }
}

void MainWindow::on_actionPlayPause_triggered()
{
    if(satellite==nullptr)
    {
        QString text="未创建卫星，请先创建卫星";
        QMessageBox::warning(this,"错误",text);
    }
    else
    {
        if(earth2D->startOrPause==false)
        {
            ui->actionPlayPause->setIcon(QIcon("://images/pause.png"));
            earth2D->startOrPause=true;
    //        qDebug()<<earth2D->startOrPause;
        }
        else if(earth2D->startOrPause==true)
        {
            ui->actionPlayPause->setIcon(QIcon("://images/play.png"));
            earth2D->startOrPause=false;
    //        qDebug()<<earth2D->startOrPause;
        }
        earth2D->startOrPauseSatellite();
    }
}

void MainWindow::finishOrbitYes(bool b)
{
    if(b==true)
    {
        ui->actionPlayPause->setIcon(QIcon("://images/play.png"));
        earth2D->startOrPause=false;
        earth2D->finishOrbit=false;
    }
}

void MainWindow::timeWidgetSet()
{
    timeWidget=new TimeWidget(timeDockWidget);
    timeDockWidget->setWidget(timeWidget);
    connect(earth2D,&Earth2D::sendmCountsSignal,timeWidget,&TimeWidget::setTimeDisplay);    
    connect(earth2D,&Earth2D::sendmCountsSignal,timeWidget->wholeTimeDrawArea,&WholeTimeDrawArea::acceptCounts);
    connect(earth2D,&Earth2D::sendmCountsSignal,timeWidget->dayTimeDrawArea,&DayTimeDrawArea::acceptCounts);

    connect(timeWidget,&TimeWidget::sendTimeCountSignal,earth2D,&Earth2D::acceptmCount);
    connect(timeWidget->wholeTimeDrawArea,&WholeTimeDrawArea::sendTimeCountSignal,earth2D,&Earth2D::acceptmCount);
    connect(timeWidget->dayTimeDrawArea,&DayTimeDrawArea::sendTimeCountSignal,earth2D,&Earth2D::acceptmCount);

    connect(timeWidget->timeSetPushButton,SIGNAL(clicked()),this,SLOT(timeSet()));
}

void MainWindow::on_timer()
{
    earth2D->sendmCounts();
    earth2D->sendFinishOrbit();
}

void MainWindow::timeSet()
{
    timeWidget->sendTimeCount();    
}

void MainWindow::on_actionSaveScenario_triggered()
{
    scenario->saveScenario();
}

void MainWindow::on_actionOpenScenario_triggered()
{
    if(scenarioTreeWidgetItem!=nullptr)
    {
        disconnect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showScenario(QTreeWidgetItem*,int)));
    }
    //对象树设置
    itemTreeWidget->setHeaderLabel("对象");
    scenarioTreeWidgetItem=new QTreeWidgetItem(itemTreeWidget);
    scenario=new Scenario;
    scenario->newScenario();
    scenarioTreeWidgetItem->setText(0,scenario->ScenarioName);

    connect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showScenario(QTreeWidgetItem*,int)));
    scenario->openScenario(t1,t2,&fd1,&fd2);
//    updateMenu();
}

void MainWindow::on_actionSaveSatellite_triggered()
{
    satellite->saveSatellite();
}

void MainWindow::on_actionOpenSatellite_triggered()
{
    if(satelliteTreeWidgetItem!=nullptr)
    {
        disconnect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSatellite(QTreeWidgetItem*,int)));
    }
    //对象树设置
    satelliteTreeWidgetItem=new QTreeWidgetItem(scenarioTreeWidgetItem);
    satellite=new Satellite;
    satellite->newSatellite();
    satelliteTreeWidgetItem->setText(0,satellite->satelliteName);

    connect(itemTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSatellite(QTreeWidgetItem*,int)));

    satellite->openSatellite(para);
//    updateMenu();
}

void MainWindow::on_actionItem_triggered()
{
    if(itemDockWidget->isHidden())
    {
        itemDockWidget->show();
    }
    else
    {
        itemDockWidget->hide();
    }
}

void MainWindow::on_actionTime_triggered()
{
    if(timeDockWidget->isHidden())
    {
        timeDockWidget->show();
    }
    else
    {
        timeDockWidget->hide();
    }
}

void MainWindow::on_action2D_triggered()
{
    if(earth2Dsub->isHidden())
    {
        earth2Dsub->show();
    }
    else
    {
        earth2Dsub->hide();
    }
}

void MainWindow::on_action3D_triggered()
{
    if(earth3Dsub->isHidden())
    {
        earth3Dsub->show();
    }
    else
    {
        earth3Dsub->hide();
    }
}

void MainWindow::on_actionDrawAll_triggered()
{
    earth2D->drawAllOrbit=!earth2D->drawAllOrbit;
    earth2D->update();
}

//void MainWindow::updateMenu()
//{
//    bool hasScenario=(scenario!=nullptr);
//    ui->actionInsertSatellite->setEnabled(hasScenario);
//    ui->actionSaveScenario->setEnabled(hasScenario);
//    ui->actionOpenSatellite->setEnabled(hasScenario);

//    bool hasSatellite=(satellite!=nullptr);
//    ui->actionCalculate->setEnabled(hasSatellite);
//    ui->actionSaveSatellite->setEnabled(hasSatellite);
//    ui->actionPlayPause->setEnabled(hasSatellite);
//    ui->actionDrawAll->setEnabled(hasSatellite);
//    ui->actionOutputOrbitText->setEnabled(hasSatellite);
//}

void MainWindow::on_actionHelp_triggered()
{
    QString text="该软件模块的基本使用步骤如下：\n"
                 "1、建立场景和卫星，并在输入窗口中输入对应的基本参数；\n"
                 "2、点击计算功能键，进行高精度轨道预报计算；\n"
                 "3、完成计算后可以通过时间窗口对可视化窗口中的卫星运动进行控制；\n"
                 "4、用户可以通过点击输出结果功能键查看计算结果，即详细的卫星状态量数据；\n"
                 "5、用户可以通过双击对象窗口中的场景或卫星修改对应的计算参数；\n";
    QMessageBox::about(this,"使用说明",text);
}
