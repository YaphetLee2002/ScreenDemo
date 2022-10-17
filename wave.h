#ifndef WAVE_H
#define WAVE_H
#include "qwidgetdraw.h"

class Wave : public QWidget
{

private:
    Qt::GlobalColor waveColor;
    QString waveTitle;
    QString waveTimes;
public:
    QWidgetDraw * waveWin;

public:
    Wave(QWidget * parent = 0) : QWidget(parent) {}
    Wave(Qt::GlobalColor color, QString waveTitle, QString waveTimes, QWidget * parent = 0) : QWidget(parent)
    {
        QFont titleFont ("Microsoft YaHei", 8, 75);

        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setStyleSheet("background-color:black");

        waveColor = color;

        QLabel *title = new QLabel(waveTitle);
        title->setFont(titleFont);
        title->setStyleSheet("color:white");
        QLabel *times = new QLabel(waveTimes);
        times->setStyleSheet("color:white");
        times->setFont(titleFont);
        waveWin = new QWidgetDraw(waveColor);

        QHBoxLayout * bLayout = new QHBoxLayout();
        bLayout->addWidget(title);
        bLayout->addWidget(times);
        bLayout->setStretch(0, 1);
        bLayout->setStretch(1, 10);

        QVBoxLayout * layout = new QVBoxLayout();
        layout->addLayout(bLayout);
        layout->addWidget(waveWin);
        layout->setStretch(0, 1);
        layout->setStretch(1, 5);
        this->setLayout(layout);
    }
};
#endif // WAVE_H
