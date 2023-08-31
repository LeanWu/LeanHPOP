#ifndef INPUTSATELLITESTARTPOSWIDGET_H
#define INPUTSATELLITESTARTPOSWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDoubleSpinBox>
#include<QGridLayout>
#include"float.h"
#include"math.h"

class InputSatelliteStartPosWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputSatelliteStartPosWidget(QWidget *parent = nullptr);

    //卫星初始位置输入对话框
    QLabel *aLabel;
    QLabel *eLabel;
    QLabel *iLabel;
    QLabel *OmegaLabel;
    QLabel *omegaLabel;
    QLabel *fLabel;

    QDoubleSpinBox *aDoubleSpinBox;
    QDoubleSpinBox *eDoubleSpinBox;
    QDoubleSpinBox *iDoubleSpinBox;
    QDoubleSpinBox *OmegaDoubleSpinBox;
    QDoubleSpinBox *omegaDoubleSpinBox;
    QDoubleSpinBox *fDoubleSpinBox;

    QGridLayout *startPosMainLayout;

    QPushButton *perturbationModelPushButton;
    QPushButton *satelliteOkPushButton;

};

#endif // INPUTSATELLITESTARTPOSWIDGET_H
