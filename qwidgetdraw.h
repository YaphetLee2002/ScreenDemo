#ifndef QWIDGETDRAW_H
#define QWIDGETDRAW_H
#include "serialportrx.h"

inline bool between(int, int, int);

/*
 * @waveColor: 波形颜色
 * @waveData: 波形数据向量
 */

class QWidgetDraw : public QWidget
{
public:
    int dataIndex;
    qreal index;
    qreal range;
    QPixmap *pixmap;
    Qt::GlobalColor waveColor;
    QVector<int> waveData;

    /*
     * @QWidgetDraw: 构造函数
     * @color: 绘制线条的颜色
     * @data: 对应绘制波形的数据
     */
    QWidgetDraw(Qt::GlobalColor color, QWidget *parent = 0) : QWidget(parent)
    {
        pixmap = new QPixmap(this->width(), this->height());
        pixmap->fill(Qt::black);
        index = 0;
        range = 0;
        dataIndex = 0;
        waveColor = color;
        if (waveColor == Qt::green) {
            waveData = QVector<int>(500, 2048);
        } else if (waveColor == Qt::red) {
            waveData = QVector<int>(642, 975);
        } else {
            waveData = QVector<int>(50, 160);
        }
        QBasicTimer *timer = new QBasicTimer();
        timer->start(10, this);
    }

private:
    virtual void timerEvent(QTimerEvent *event)
    {
        drawWaveToPixmap();
        this->update();
    }

    void drawWaveToPixmap()
    {
        QPainter pixPainter;
        pixPainter.begin(this->pixmap);
        drawWave(&pixPainter);
        pixPainter.end();
    }

    virtual void paintEvent(QPaintEvent *event)
    {
        QPainter *painter = new QPainter();
        // qDebug() << "PaintEvent";
        painter->begin(this);
        painter->resetTransform();
        painter->drawPixmap(0, 0, *pixmap);
        painter->resetTransform();
        painter->end();
    }

    void drawWave(QPainter *painter)
    {
        QPen pen;
        pen.setWidth(2);
        pen.setColor(waveColor);
        painter->setPen(pen);

        index++;
        if (index > this->width())
            index = 1;

        painter->save();
        pen.setColor(Qt::black);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawLine(index, 0, index, this->height());
        painter->restore();

        qreal height = this->height();
        QPoint lineStart;
        QPoint lineEnd;
        lineStart.setX(index - 1);
        lineEnd.setX(index);

        qreal value = waveData[dataIndex];
        int y = between(ECG_MIN, value, ECG_MAX) ? round(height / 2 - ((value - 2048) / 600) * height / 2) :
                between(SPO2_MIN, value, SPO2_MAX) ? round(height / 2 - ((value - 975) / 30) * height / 2) :
                between(RESP_MIN, value, RESP_MAX) ? round(height / 2 - ((value - 160) / 1000)* height / 2) :
                0;

        lineStart.setY(y);

        dataIndex += 5;
        if (dataIndex >= waveData.size())
            dataIndex = 0;
        value = waveData[dataIndex];
        y = between(ECG_MIN, value, ECG_MAX) ? round(height / 2 - ((value - 2048) / 600) * height / 2) :
                between(SPO2_MIN, value, SPO2_MAX) ? round(height / 2 - ((value - 975) / 30) * height / 2) :
                between(RESP_MIN, value, RESP_MAX) ? round(height / 2 - ((value - 160) / 1000)* height / 2) :
                180;
        lineEnd.setY(y);

        painter->drawLine(lineStart, lineEnd);
    }
};



inline bool between(int left, int mid, int right)
{
    return mid >= left && mid <= right;
}
#endif // QWIDGETDRAW_H
