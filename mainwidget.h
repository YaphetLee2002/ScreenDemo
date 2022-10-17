#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <random>
#include "data.h"
#include "wave.h"
#include "serialportrx.h"
class MainWidget : public QWidget
{
private:
    QLabel * numberHr;
    QLabel * numberSpo2;
    QLabel * deviceNumberLabel;

    Wave *widgetWaveEcg;
    Wave *widgetWaveSpo2;
    Wave *widgetWaveResp;
public:
    QTimer * ecgTimer;
    QTimer * spo2Timer;
    QTimer * respTimer;
    QTimer * deviceTimer;

private slots:
    // 刷新显示数据的槽函数
    void refreshEcgData()
    {
        // numberHr->setText(QString::number(Hr1));

        // 随机数刷新测试
        int tempHr = rand() % 20 + 80;
        numberHr->setText(QString::number(tempHr));

        widgetWaveEcg->waveWin->waveData = ecg_array1;
    }

    void refreshSpo2Data()
    {
        // numberSpo2->setText(QString::number(SPO2_array1[0] / 10));

        //随机数刷新测试
        int tempSpo2 = rand() % 5 + 95;
        numberSpo2->setText(QString::number(tempSpo2));

        widgetWaveSpo2->waveWin->waveData = SPO2_array1;
    }

    void refreshRespData()
    {
        widgetWaveResp->waveWin->waveData = RESP_array1;
    }

    void refreshDeviceData()
    {
        // deviceNumberLabel->setText("  DEVICE: " + device_number1 + "   " + "PATIENT: " + patient_number1);

        int temp1 = rand() % 1000;
        int temp2 = rand() % 10000;
        // 数据刷新测试
        deviceNumberLabel->setText("  DEVICE: " + QString::number(temp1) + "   " + "PATIENT: " + QString::number(temp2));
    }

public:
    SerialPortRx* spr;
    QWidget * getNewBlackWeidgt()
    {
        QWidget* tempWidget = new QWidget();
        tempWidget->setStyleSheet("background-color:black");
        return tempWidget;
    }

    MainWidget(QWidget *parent = 0) : QWidget(parent)
    {
        ecgTimer = new QTimer();
        spo2Timer = new QTimer();
        respTimer = new QTimer();
        deviceTimer = new QTimer();

        connect(ecgTimer, QTimer::timeout, this, MainWidget::refreshEcgData);
        connect(spo2Timer, QTimer::timeout, this, MainWidget::refreshSpo2Data);
        connect(respTimer, QTimer::timeout, this, MainWidget::refreshRespData);
        connect(deviceTimer, QTimer::timeout, this, MainWidget::refreshDeviceData);

        deviceTimer->start(deviceRefreshTime);
        ecgTimer->start(ecgRefreshTime);
        spo2Timer->start(spo2RefreshTime);
        respTimer->start(respRefreshTime);

        //建立串口
        spr = new SerialPortRx();

        //这里是两个动态的Label
        numberHr = new QLabel();
        numberSpo2 = new QLabel();
        deviceNumberLabel = new QLabel();

        QFont titleFont ("Microsoft YaHei", 8, 75);
        QFont maxContainFont ("Microsoft YaHei", 25, 75);
        QFont midContainFont ("Microsoft YaHei", 12, 75);
        QFont minContainFont ("Microsoft YaHei", 10, 70);

        // 标题栏
        QWidget *widgetMainTitle = new QWidget();


        deviceNumberLabel->setText("  DEVICE: " + device_number1 + "   " + "PATIENT: " + patient_number1);
        deviceNumberLabel->setStyleSheet("color:white;");
        deviceNumberLabel->setFont(titleFont);


        QHBoxLayout *layoutTitle = new QHBoxLayout();
        layoutTitle->addWidget(deviceNumberLabel);
        layoutTitle->addWidget(widgetMainTitle);

        layoutTitle->setStretch(0, 1);
        layoutTitle->setStretch(1, 9);




        // 左侧三个波形窗口
        widgetWaveEcg = new Wave(Qt::green, "ECG Ⅱ", "x1");
        widgetWaveEcg->setStyleSheet("background-color:black");

        widgetWaveSpo2 = new Wave(Qt::red, "SPO2", "");
        widgetWaveSpo2->setStyleSheet("background-color:black");

        widgetWaveResp = new Wave(Qt::yellow, "RESP", "x1");
        widgetWaveResp->setStyleSheet("background-color:black");

        QVBoxLayout *layoutWave = new QVBoxLayout();
        layoutWave->setContentsMargins(0, 0, 0, 0);
        layoutWave->setSpacing(0);
        layoutWave->addWidget(widgetWaveEcg);
        layoutWave->addWidget(widgetWaveSpo2);
        layoutWave->addWidget(widgetWaveResp);



        // 右侧窗口
        // HR
        QWidget *widgetHr = getNewBlackWeidgt();

        QWidget *titleHr = new QWidget();
        titleHr->setMinimumHeight(28);
        titleHr->setMaximumHeight(28);
        titleHr->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelHr = new QLabel();
        labelHr->setText("  HR");
        labelHr->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelHr->setFont(titleFont);

        QHBoxLayout * titleLayoutHr = new QHBoxLayout();
        titleLayoutHr->addWidget(labelHr);
        titleLayoutHr->addWidget(titleHr);
        titleLayoutHr->setStretch(0, 1);
        titleLayoutHr->setStretch(1, 9);

        QLabel *labelHrEmpty = new QLabel();

        numberHr->setText(QString::number(spr->HR1)); //数值显示
        numberHr->setStyleSheet("color:rgb(37, 240, 38);");
        numberHr->setFont(maxContainFont);
        numberHr->setAlignment(Qt::AlignTop);

        QLabel *labelHrUnit = new QLabel();
        labelHrUnit->setAlignment(Qt::AlignTop);
        labelHrUnit->setText("bpm");
        labelHrUnit->setStyleSheet("color:rgb(37, 240, 38);");
        labelHrUnit->setFont(minContainFont);
        labelHrUnit->setAlignment(Qt::AlignRight);

        QHBoxLayout *layoutHrBottom = new QHBoxLayout();
        layoutHrBottom->addWidget(labelHrEmpty);
        layoutHrBottom->addWidget(numberHr);
        layoutHrBottom->addWidget(labelHrUnit);

        QVBoxLayout *layoutHr = new QVBoxLayout();
        layoutHr->setContentsMargins(0, 0, 0, 0);
        layoutHr->setSpacing(0);
        layoutHr->addLayout(titleLayoutHr);
        layoutHr->addLayout(layoutHrBottom);
        layoutHr->setStretch(0, 1);
        layoutHr->setStretch(1, 3);
        widgetHr->setLayout(layoutHr);



        //ST
        QWidget *widgetSt = getNewBlackWeidgt();

        QWidget *titleSt = new QWidget();
        titleSt->setMinimumHeight(28);
        titleSt->setMaximumHeight(28);
        titleSt->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelSt = new QLabel();
        labelSt->setText("  ST");
        labelSt->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelSt->setFont(titleFont);

        QHBoxLayout * titleLayoutSt = new QHBoxLayout();
        titleLayoutSt->addWidget(labelSt);
        titleLayoutSt->addWidget(titleSt);
        titleLayoutSt->setStretch(0, 1);
        titleLayoutSt->setStretch(1, 9);

        QLabel * ST1 = new QLabel();
        ST1->setText("ST1 -?-");
        ST1->setStyleSheet("color:rgb(37, 240, 38)");
        ST1->setFont(midContainFont);
        ST1->setAlignment(Qt::AlignCenter);

        QLabel * ST2 = new QLabel();
        ST2->setText("ST2 -?-");
        ST2->setStyleSheet("color:rgb(37, 240, 38)");
        ST2->setFont(midContainFont);
        ST2->setAlignment(Qt::AlignCenter);

        QLabel * PVCs = new QLabel();
        PVCs->setText("PVCs -?-");
        PVCs->setStyleSheet("color:rgb(37, 240, 38)");
        PVCs->setFont(midContainFont);
        PVCs->setAlignment(Qt::AlignCenter);

        QVBoxLayout *layoutSt = new QVBoxLayout();
        layoutSt->setContentsMargins(0, 0, 0, 0);
        layoutSt->setSpacing(0);
        layoutSt->addLayout(titleLayoutSt);
        layoutSt->addWidget(ST1);
        layoutSt->addWidget(ST2);
        layoutSt->addWidget(PVCs);
        layoutSt->setStretch(0, 1);
        layoutSt->setStretch(1, 1);
        layoutSt->setStretch(2, 1);
        layoutSt->setStretch(3, 1);
        widgetSt->setLayout(layoutSt);


        //NIBP
        QWidget *widgetNibp = getNewBlackWeidgt();

        QWidget *titleNibp = new QWidget();
        titleNibp->setMinimumHeight(28);
        titleNibp->setMaximumHeight(28);
        titleNibp->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelNibp = new QLabel();
        labelNibp->setText("  NIBP");
        labelNibp->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelNibp->setFont(titleFont);

        QHBoxLayout * titleLayoutNibp = new QHBoxLayout();
        titleLayoutNibp->addWidget(labelNibp);
        titleLayoutNibp->addWidget(titleNibp);
        titleLayoutNibp->setStretch(0, 1);
        titleLayoutNibp->setStretch(1, 9);

        QLabel * nibpTime = new QLabel();
        nibpTime->setText("00:00:00");
        nibpTime->setStyleSheet("color:rgb(72, 154, 217)");
        nibpTime->setFont(minContainFont);
        nibpTime->setAlignment(Qt::AlignRight);

        QLabel * nibpUnit = new QLabel();
        nibpUnit->setText("mmHg");
        nibpUnit->setStyleSheet("color:rgb(72, 154, 217)");
        nibpUnit->setFont(minContainFont);
        nibpUnit->setAlignment(Qt::AlignRight);

        QHBoxLayout * secondLayoutNibp = new QHBoxLayout();
        secondLayoutNibp->addWidget(nibpTime);
        secondLayoutNibp->addWidget(nibpUnit);
        secondLayoutNibp->setStretch(0, 1);
        secondLayoutNibp->setStretch(1, 1);

        QLabel * nibpLeft = new QLabel();
        nibpLeft->setText("-?-");
        nibpLeft->setStyleSheet("color:rgb(72, 154, 217)");
        nibpLeft->setFont(minContainFont);
        nibpLeft->setAlignment(Qt::AlignCenter);

        QLabel * nibpMid = new QLabel();
        nibpMid->setText("-?-");
        nibpMid->setStyleSheet("color:rgb(72, 154, 217)");
        nibpMid->setFont(maxContainFont);
        nibpMid->setAlignment(Qt::AlignTop);

        QLabel * nibpRight = new QLabel();
        nibpRight->setText("-?-");
        nibpRight->setStyleSheet("color:rgb(72, 154, 217)");
        nibpRight->setFont(midContainFont);
        nibpRight->setAlignment(Qt::AlignRight);

        QHBoxLayout * thirdLayoutNibp = new QHBoxLayout();
        thirdLayoutNibp->addWidget(nibpLeft);
        thirdLayoutNibp->addWidget(nibpMid);
        thirdLayoutNibp->addWidget(nibpRight);
        thirdLayoutNibp->setStretch(0, 1);
        thirdLayoutNibp->setStretch(1, 1);
        thirdLayoutNibp->setStretch(2, 1);

        QVBoxLayout *layoutNibp = new QVBoxLayout();
        layoutNibp->setContentsMargins(0, 0, 0, 0);
        layoutNibp->setSpacing(0);
        layoutNibp->addLayout(titleLayoutNibp);
        layoutNibp->addLayout(secondLayoutNibp);
        layoutNibp->addLayout(thirdLayoutNibp);
        widgetNibp->setLayout(layoutNibp);


        //SPO2
        QWidget *widgetSpo2 = getNewBlackWeidgt();

        QWidget *titleSpo2 = new QWidget();
        titleSpo2->setMinimumHeight(28);
        titleSpo2->setMaximumHeight(28);
        titleSpo2->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelSpo2 = new QLabel();
        labelSpo2->setText("  SPO2");
        labelSpo2->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelSpo2->setFont(titleFont);

        QHBoxLayout * titleLayoutSpo2 = new QHBoxLayout();
        titleLayoutSpo2->addWidget(labelSpo2);
        titleLayoutSpo2->addWidget(titleSpo2);
        titleLayoutSpo2->setStretch(0, 1);
        titleLayoutSpo2->setStretch(1, 9);

        numberSpo2->setText(QString::number(spr->SPO2_array1[0] / 10)); //数值显示
        numberSpo2->setStyleSheet("color:rgb(246, 6, 10);");
        numberSpo2->setFont(maxContainFont);
        numberSpo2->setAlignment(Qt::AlignRight);

        QLabel *labelSpo2Unit = new QLabel();
        labelSpo2Unit->setText("%");
        labelSpo2Unit->setStyleSheet("color:rgb(246, 6, 10);");
        labelSpo2Unit->setFont(minContainFont);
        labelSpo2Unit->setAlignment(Qt::AlignCenter);

        QHBoxLayout * secondLayoutSpo2 = new QHBoxLayout();
        secondLayoutSpo2->addWidget(numberSpo2);
        secondLayoutSpo2->addWidget(labelSpo2Unit);
        secondLayoutSpo2->setStretch(0, 1);
        secondLayoutSpo2->setStretch(1, 1);

        QLabel *littleNumberSpo2 = new QLabel();
        littleNumberSpo2->setText("85");
        littleNumberSpo2->setStyleSheet("color:rgb(246, 6, 10);");
        littleNumberSpo2->setFont(midContainFont);
        littleNumberSpo2->setAlignment(Qt::AlignRight);

        QLabel *littleSpo2Unit = new QLabel();
        littleSpo2Unit->setText("bmp");
        littleSpo2Unit->setStyleSheet("color:rgb(246, 6, 10);");
        littleSpo2Unit->setFont(minContainFont);
        littleSpo2Unit->setAlignment(Qt::AlignRight);

        QHBoxLayout * thirdLayoutSpo2 = new QHBoxLayout();
        thirdLayoutSpo2->addWidget(littleNumberSpo2);
        thirdLayoutSpo2->addWidget(littleSpo2Unit);
        thirdLayoutSpo2->setStretch(0, 3);
        thirdLayoutSpo2->setStretch(1, 1);

        QVBoxLayout *layoutSpo2 = new QVBoxLayout();
        layoutSpo2->setContentsMargins(0, 0, 0, 0);
        layoutSpo2->setSpacing(0);
        layoutSpo2->addLayout(titleLayoutSpo2);
        layoutSpo2->addLayout(secondLayoutSpo2);
        layoutSpo2->addLayout(thirdLayoutSpo2);
        widgetSpo2->setLayout(layoutSpo2);


        //TEMP
        QWidget *widgetTemp = getNewBlackWeidgt();

        QWidget *titleTemp = new QWidget();
        titleTemp->setMinimumHeight(28);
        titleTemp->setMaximumHeight(28);
        titleTemp->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelTemp = new QLabel();
        labelTemp->setText("  TEMP");
        labelTemp->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelTemp->setFont(titleFont);


        QHBoxLayout * titleLayoutTemp = new QHBoxLayout();
        titleLayoutTemp->addWidget(labelTemp);
        titleLayoutTemp->addWidget(titleTemp);
        titleLayoutTemp->setStretch(0, 1);
        titleLayoutTemp->setStretch(1, 9);

        QLabel *T1 = new QLabel();
        T1->setText("T1 -?-"); //数值显示
        T1->setStyleSheet("color:rgb(234, 21, 194);");
        T1->setFont(minContainFont);
        T1->setAlignment(Qt::AlignCenter);

        QLabel *T2 = new QLabel();
        T2->setText("T1 -?-");
        T2->setStyleSheet("color:rgb(234, 21, 194);");
        T2->setFont(minContainFont);
        T2->setAlignment(Qt::AlignCenter);

        QVBoxLayout * secondLayoutTemp = new QVBoxLayout();
        secondLayoutTemp->addWidget(T1);
        secondLayoutTemp->addWidget(T2);
        secondLayoutTemp->setStretch(0, 1);
        secondLayoutTemp->setStretch(1, 1);

        QLabel *unitTemp = new QLabel();
        unitTemp->setText("℃");
        unitTemp->setStyleSheet("color:rgb(234, 21, 194);");
        unitTemp->setFont(minContainFont);
        unitTemp->setAlignment(Qt::AlignRight);

        QLabel *TD = new QLabel();
        TD->setText("TD -?-");
        TD->setStyleSheet("color:rgb(234, 21, 194);");
        TD->setFont(minContainFont);
        TD->setAlignment(Qt::AlignCenter);

        QVBoxLayout * thirdLayoutTemp = new QVBoxLayout();
        thirdLayoutTemp->addWidget(unitTemp);
        thirdLayoutTemp->addWidget(TD);
        thirdLayoutSpo2->setStretch(0, 1);
        thirdLayoutTemp->setStretch(1, 3);

        QHBoxLayout * mainLayoutTemp = new QHBoxLayout();
        mainLayoutTemp->addLayout(secondLayoutTemp);
        mainLayoutTemp->addLayout(thirdLayoutTemp);
        mainLayoutTemp->setStretch(0, 1);
        mainLayoutTemp->setStretch(1, 1);

        QVBoxLayout *layoutTemp = new QVBoxLayout();
        layoutTemp->setContentsMargins(0, 0, 0, 0);
        layoutTemp->setSpacing(0);
        layoutTemp->addLayout(titleLayoutTemp);
        layoutTemp->addLayout(mainLayoutTemp);
        widgetTemp->setLayout(layoutTemp);


        //RESP
        QWidget *widgetResp = getNewBlackWeidgt();

        QWidget *titleResp = new QWidget();
        titleResp->setMinimumHeight(28);
        titleResp->setMaximumHeight(28);
        titleResp->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelResp = new QLabel();
        labelResp->setText("  RESP");
        labelResp->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelResp->setFont(titleFont);

        QHBoxLayout * titleLayoutResp = new QHBoxLayout();
        titleLayoutResp->addWidget(labelResp);
        titleLayoutResp->addWidget(titleResp);
        titleLayoutResp->setStretch(0, 1);
        titleLayoutResp->setStretch(1, 9);

        QLabel *labelRespEmpty = new QLabel();

        QLabel *numberResp = new QLabel();
        numberResp->setText("-?-"); //数值显示
        numberResp->setStyleSheet("color:rgb(239, 213, 63);");
        numberResp->setFont(maxContainFont);
        numberResp->setAlignment(Qt::AlignTop);

        QLabel *labelRespUnit = new QLabel();
        labelRespUnit->setAlignment(Qt::AlignTop);
        labelRespUnit->setText("bpm");
        labelRespUnit->setStyleSheet("color:rgb(239, 213, 63);");
        labelRespUnit->setFont(minContainFont);
        labelRespUnit->setAlignment(Qt::AlignRight);

        QHBoxLayout *layoutRespBottom = new QHBoxLayout();
        layoutRespBottom->addWidget(labelRespEmpty);
        layoutRespBottom->addWidget(numberResp);
        layoutRespBottom->addWidget(labelRespUnit);

        QVBoxLayout *layoutResp = new QVBoxLayout();
        layoutResp->setContentsMargins(0, 0, 0, 0);
        layoutResp->setSpacing(0);
        layoutResp->addLayout(titleLayoutResp);
        layoutResp->addLayout(layoutRespBottom);
        layoutResp->setStretch(0, 1);
        layoutResp->setStretch(1, 3);
        widgetResp->setLayout(layoutResp);


        //CO2
        QWidget *widgetCo2 = getNewBlackWeidgt();
        QWidget *titleCo2 = new QWidget();
        titleCo2->setMinimumHeight(28);
        titleCo2->setMaximumHeight(28);
        titleCo2->setStyleSheet("background-color:rgb(100,100,100)");

        QLabel *labelCo2 = new QLabel();
        labelCo2->setText("  CO2");
        labelCo2->setStyleSheet("background-color:rgb(100,100,100);color:white;");
        labelCo2->setFont(titleFont);

        QHBoxLayout * titleLayoutCo2 = new QHBoxLayout();
        titleLayoutCo2->addWidget(labelCo2);
        titleLayoutCo2->addWidget(titleCo2);
        titleLayoutCo2->setStretch(0, 1);
        titleLayoutCo2->setStretch(1, 9);

        QLabel *labelCo2Empty = new QLabel();

        QLabel *numberCo2 = new QLabel();
        numberCo2->setText("-?-"); //数值显示
        numberCo2->setStyleSheet("color:rgb(239, 213, 63);");
        numberCo2->setFont(maxContainFont);
        numberCo2->setAlignment(Qt::AlignTop);

        QLabel *labelCo2Unit = new QLabel();
        labelCo2Unit->setAlignment(Qt::AlignTop);
        labelCo2Unit->setText("bpm");
        labelCo2Unit->setStyleSheet("color:rgb(239, 213, 63);");
        labelCo2Unit->setFont(minContainFont);
        labelCo2Unit->setAlignment(Qt::AlignRight);

        QHBoxLayout *layoutCo2Bottom = new QHBoxLayout();
        layoutCo2Bottom->addWidget(labelCo2Empty);
        layoutCo2Bottom->addWidget(numberCo2);
        layoutCo2Bottom->addWidget(labelCo2Unit);

        QLabel *leftCo2Label = new QLabel();
        leftCo2Label->setText("ins -?-");
        leftCo2Label->setStyleSheet("color:rgb(239, 213, 63);");
        leftCo2Label->setFont(minContainFont);
        leftCo2Label->setAlignment(Qt::AlignCenter);

        QLabel *rightCo2Label = new QLabel();
        rightCo2Label->setText("awrr -?-");
        rightCo2Label->setStyleSheet("color:rgb(239, 213, 63);");
        rightCo2Label->setFont(minContainFont);
        rightCo2Label->setAlignment(Qt::AlignCenter);

        QHBoxLayout * thirdLayoutCo2 = new QHBoxLayout();
        thirdLayoutCo2->addWidget(leftCo2Label);
        thirdLayoutCo2->addWidget(rightCo2Label);
        thirdLayoutCo2->setStretch(0, 1);
        thirdLayoutCo2->setStretch(1, 1);

        QVBoxLayout *layoutCo2 = new QVBoxLayout();
        layoutCo2->setContentsMargins(0, 0, 0, 0);
        layoutCo2->setSpacing(0);
        layoutCo2->addLayout(titleLayoutCo2);
        layoutCo2->addLayout(layoutCo2Bottom);
        layoutCo2->addLayout(thirdLayoutCo2);
        layoutCo2->setStretch(0, 1);
        layoutCo2->setStretch(1, 3);
        widgetCo2->setLayout(layoutCo2);

        //布局
        QHBoxLayout *layoutTableLine1 = new QHBoxLayout();
        layoutTableLine1->setContentsMargins(0, 0, 0, 0);
        layoutTableLine1->setSpacing(0);
        layoutTableLine1->addWidget(widgetHr);
        layoutTableLine1->addWidget(widgetSt);
        layoutTableLine1->setStretch(0, 1);
        layoutTableLine1->setStretch(1, 1);

        QHBoxLayout *layoutTableLine2 = new QHBoxLayout();
        layoutTableLine2->setContentsMargins(0, 0, 0, 0);
        layoutTableLine2->setSpacing(0);
        layoutTableLine2->addWidget(widgetNibp);

        QHBoxLayout *layoutTableLine3 = new QHBoxLayout();
        layoutTableLine3->setContentsMargins(0, 0, 0, 0);
        layoutTableLine3->setSpacing(0);
        layoutTableLine3->addWidget(widgetSpo2);
        layoutTableLine3->addWidget(widgetTemp);
        layoutTableLine3->setStretch(0, 1);
        layoutTableLine3->setStretch(1, 1);

        QHBoxLayout *layoutTableLine4 = new QHBoxLayout();
        layoutTableLine4->setContentsMargins(0, 0, 0, 0);
        layoutTableLine4->setSpacing(0);
        layoutTableLine4->addWidget(widgetResp);
        layoutTableLine4->addWidget(widgetCo2);
        layoutTableLine4->setStretch(0, 1);
        layoutTableLine4->setStretch(1, 1);

        QVBoxLayout *layoutTable = new QVBoxLayout();
        layoutTable->setContentsMargins(0, 0, 0, 0);
        layoutTable->setSpacing(0);
        layoutTable->addLayout(layoutTableLine1);
        layoutTable->addLayout(layoutTableLine2);
        layoutTable->addLayout(layoutTableLine3);
        layoutTable->addLayout(layoutTableLine4);
        layoutTable->setStretch(0, 1);
        layoutTable->setStretch(1, 1);
        layoutTable->setStretch(2, 1);
        layoutTable->setStretch(3, 1);

        QHBoxLayout *layoutDown = new QHBoxLayout();
        layoutDown->setContentsMargins(0, 0, 0, 0);
        layoutDown->setSpacing(0);
        layoutDown->addLayout(layoutWave);
        layoutDown->addLayout(layoutTable);
        layoutDown->setStretch(0, 2);
        layoutDown->setStretch(1, 1);

        QVBoxLayout *layoutMain = new QVBoxLayout();
        layoutMain->setContentsMargins(0, 0, 0, 0);
        layoutMain->setSpacing(0);
        layoutMain->addLayout(layoutTitle);
        layoutMain->addLayout(layoutDown);
        layoutMain->setStretch(0, 1);
        layoutMain->setStretch(1, 20);

        //QWidget *widgetMain = new QWidget();
        this->setStyleSheet("background-color:black");
        this->setLayout(layoutMain);
        // this->resize(1024, 640);
    }
};

#endif // MAINWIDGET_H
