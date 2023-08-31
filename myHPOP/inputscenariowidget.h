#ifndef INPUTSCENARIOWIDGET_H
#define INPUTSCENARIOWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QSpinBox>
#include<QGridLayout>
#include<QPushButton>

class InputScenarioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputScenarioWidget(QWidget *parent = nullptr);
    //输入对话框设置
    QPushButton *okPushButton;

    QLabel *startTimeLabel;
    QLabel *endTimeLabel;

    QLabel *startYearLabel;
    QSpinBox *startYearSpinBox;
    QLabel *startMonthLabel;
    QSpinBox *startMonthSpinBox;
    QLabel *startDayLabel;
    QSpinBox *startDaySpinBox;
    QLabel *startHourLabel;
    QSpinBox *startHourSpinBox;
    QLabel *startMinuteLabel;
    QSpinBox *startMinuteSpinBox;
    QLabel *startSecondLabel;
    QSpinBox *startSecondSpinBox;

    QLabel *endYearLabel;
    QSpinBox *endYearSpinBox;
    QLabel *endMonthLabel;
    QSpinBox *endMonthSpinBox;
    QLabel *endDayLabel;
    QSpinBox *endDaySpinBox;
    QLabel *endHourLabel;
    QSpinBox *endHourSpinBox;
    QLabel *endMinuteLabel;
    QSpinBox *endMinuteSpinBox;
    QLabel *endSecondLabel;
    QSpinBox *endSecondSpinBox;

    QGridLayout *mainLayout;
};

#endif // INPUTSCENARIOWIDGET_H
