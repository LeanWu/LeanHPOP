#ifndef INPUTPERTURBATIONWIDGET_H
#define INPUTPERTURBATIONWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDoubleSpinBox>
#include<QGridLayout>
#include<QCheckBox>
#include"float.h"
#include"math.h"

class InputPerturbationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputPerturbationWidget(QWidget *parent = nullptr);

    QGridLayout *perturbationMainLayout;
    QPushButton *perturbationOkPushButton;

    QGridLayout *nonsphericalGridLayout;
    QLabel *nonsphericalLavel;
    QLabel *muLabel;
    QDoubleSpinBox *muDoubleSpinBox;
    QLabel *ReLabel;
    QDoubleSpinBox *ReDoubleSpinBox;
    QLabel *omegaevLabel;
    QDoubleSpinBox *omegaevDoubleSpinBox;
    QLabel *feLabel;
    QDoubleSpinBox *feDoubleSpinBox;

    QGridLayout *dragGridLayout;
    QLabel *dragLabel;
    QLabel *CdLabel;
    QDoubleSpinBox *CdDoubleSpinBox;
    QLabel *SmLabel;
    QDoubleSpinBox *SmDoubleSpinBox;
    QLabel *FLabel;
    QDoubleSpinBox *FDoubleSpinBox;
    QLabel *FaLabel;
    QDoubleSpinBox *FaDoubleSpinBox;
    QLabel *ApLabel;
    QDoubleSpinBox *ApDoubleSpinBox;

    QGridLayout *solarPressureGridLayout;
    QLabel *solarPressureLabel;
    QLabel *CrLabel;
    QDoubleSpinBox *CrDoubleSpinBox;
    QLabel *SmLabel1;
    QDoubleSpinBox *SmDoubleSpinBox1;

    QGridLayout *thirdBodyGridLayout;
    QLabel *thirdBodyLabel;
    QCheckBox *sunCheckBox;
    QCheckBox *moonCheckBox;

};

#endif // INPUTPERTURBATIONWIDGET_H
