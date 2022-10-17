#ifndef SERIALPORTRX_H
#define SERIALPORTRX_H
#include <QWidget>
#include <QVector>
#include <QSerialPort>
#include "tcpclient.h"
class SerialPortRx: public QWidget{
    Q_OBJECT
public:
    explicit SerialPortRx(QWidget * parent = 0);

    // 接收到的数据
    QString patient_name1;
    QString patient_number1;
    QString device_number1;
    QString room_number1;
    int HR1 = 0;
    QVector<int> ecg_array1 = QVector<int>(500, 2048);
    QVector<int> RESP_array1 = QVector<int>(50, 160);
    QVector<int> SPO2_array1 = QVector<int>(642, 975);

    void handlePortData(QByteArray ReadData); // 处理从串口中接收的数据，将对应    数据赋给类的相应值
    QSerialPort *com; // 串口
    int SerialInit(); // 初始化
    void readData(); // 读取串口中的数据，结果保存在ReadData中
    void do_DataHandler(QByteArray BufferData); // 处理读取的缓存数据

    TcpClient* tc;

signals:
    void newData(QByteArray Data);//收到新数据的信号（发送给tcpclient）
};

#endif // SERIALPORTRX_H
