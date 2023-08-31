#ifndef OUTPUTORBITTEXTWIDGET_H
#define OUTPUTORBITTEXTWIDGET_H

#include <QWidget>
#include<QGridLayout>
#include<QTextEdit>
#include"scenario.h"
#include"satellite.h"
#include"calculate/SOFA/sofa.h"
#include"calculate/SOFA/sofam.h"

class OutputOrbitTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutputOrbitTextWidget(Scenario *scenario,Satellite *satellite,QWidget *parent = nullptr);

    QString orbitNumber,orbitText;
    QGridLayout *orbitTextGridLayout;
    QTextEdit *orbitTextEdit;
signals:

};

#endif // OUTPUTORBITTEXTWIDGET_H
