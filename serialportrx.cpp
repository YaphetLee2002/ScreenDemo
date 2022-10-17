#include "serialportrx.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QSerialPort>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QtGlobal>
#include <QTime>

static QByteArray PasteData;
static QByteArray ReadData;
int spo2num = 642;
int respnum = 50;

// 构造函数
SerialPortRx::SerialPortRx(QWidget *parent) : QWidget(parent){
    if( 0 != this->SerialInit()){
        qDebug("SerialInit failed");
        return;
    }
    tc = new TcpClient();
    tc->ConServer();
    connect(this,&SerialPortRx::newData,tc,&TcpClient::onNewData);//接收到完整数据后发送数据
    connect(com, &QSerialPort::readyRead, this, &SerialPortRx::readData);
}

// 串口参数初始化
int SerialPortRx::SerialInit(){
    qDebug() << "SerialInit";

    com = new QSerialPort;
    com->setPortName("COM2");

    if(!com->open(QIODevice::ReadWrite)){
        qDebug() << "Serial open failed!";
        return -1;
    }else{
        qDebug() << "Serial open success: " << com->portName();

        com -> setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
        com -> setDataBits(QSerialPort::Data8);
        com -> setFlowControl(QSerialPort::HardwareControl);
        com -> setParity(QSerialPort::NoParity);
        com ->setStopBits(QSerialPort::OneStop);
        return 0;
    }
}

// 读取串口中的数据，结果保存再ReadData中
void SerialPortRx::readData(){
    QByteArray tempData = com->readAll();
    if(!tempData.isEmpty()){
        do_DataHandler(tempData);
    }
    if(ReadData.contains("{") && ReadData.contains("}")){
        QByteArray data = ReadData;
        emit newData(data);
        handlePortData(ReadData);
        ReadData.clear();

        qDebug() << patient_name1;
    }
    tempData.clear();
}

// 处理读取的缓存数据
void SerialPortRx::do_DataHandler(QByteArray BufferData){

    // 异常类：无头且变量为空，已丢失头部，数据不可靠，直接返回
    if((!BufferData.contains("{")) && (PasteData.isNull())){
        return;
    }

    // 第一种：有头无尾， 先清空原有内容，再附加
    if((BufferData.contains("{") && (!BufferData.contains("}")))){
        PasteData.clear();
        PasteData.append(BufferData);
    }

    // 第二种:无头无尾且变量已有内容，数据中段部分，继续附加即可
    if(!BufferData.contains("{") && (!BufferData.contains("}")) && (!PasteData.isNull())){
        PasteData.append(BufferData);
    }

    // 第三种:无头有尾且变量已有内容，已完整读取，附加后输出数据，并清空变量
    if((!BufferData.contains("{")) && (BufferData.contains("}")) && (!PasteData.isNull())){
        PasteData.append(BufferData);
        ReadData = PasteData;
        PasteData.clear();
    }

    //第四种：有头有尾（一段完整的内容），先清空原有内容，再附加，然后输出，最后清空变量
    if ((BufferData.contains("{"))&(BufferData.contains("}")))
    {
        PasteData.clear();
        PasteData.append(BufferData);
        ReadData = PasteData;
        PasteData.clear();
    }
}

// 处理从串口中接收的数据，将对应数据赋给类的相应值
void SerialPortRx::handlePortData(QByteArray ReadData){
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(QString::fromLocal8Bit(ReadData).toUtf8(), &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qDebug() << parseError.errorString();
    }else{
        QJsonObject obj = doc.object();

        if(obj.contains("ecg_array")){
            QJsonValue ecgValue = obj.value("ecg_array");

            QJsonArray ecg_array = ecgValue.toArray();
            for(int i = 0; i < ecg_array.count(); i++){
                this->ecg_array1[i]=ecg_array[i].toInt();
            }
        }

        if(obj.contains("SPO2_array")){
            QJsonValue SPO2Value = obj.value("SPO2_array");

            QJsonArray SPO2_array = SPO2Value.toArray();
            for(int i = 0; i < SPO2_array.count(); i++){
                this->SPO2_array1[i] = SPO2_array[i].toInt();
            }

        }

        if(obj.contains("RESP_array")){
            QJsonValue RESPValue = obj.value("RESP_array");

            QJsonArray RESP_array = RESPValue.toArray();
            for(int i = 0; i < RESP_array.count(); i++){
                this->RESP_array1[i]=RESP_array[i].toInt();
            }
        }

        if(obj.contains("HR")){
            QJsonValue HRValue = obj.value("HR");

            this->HR1 = HRValue.toInt();
        }

        if(obj.contains("patient_name")){
            QJsonValue patient_nameValue = obj.value("patient_name");
            this->patient_name1 = patient_nameValue.toString();
        }

        if(obj.contains("patient_number")){
            QJsonValue patient_numberValue = obj.value("patient_number");

            this->patient_number1 = patient_numberValue.toString();
        }

        if(obj.contains("device_number")){
            QJsonValue device_numberValue = obj.value("device_number");

            this->device_number1 = device_numberValue.toString();
        }

        if(obj.contains("room_number")){
            QJsonValue room_numberValue = obj.value("room_number");

            this->room_number1 = room_numberValue.toString();
        }
    }
}
