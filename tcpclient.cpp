#include "tcpclient.h"

TcpClient::TcpClient(QWidget *parent) : QTcpSocket(parent){
    ip = new QHostAddress("127.0.0.1");
    port = 8888;
}
void TcpClient::ConServer()
{
    this->connectToHost(*ip,port);
    if(this->waitForConnected(10000))
    {
        qDebug()<<"connected!";
    }else{
        qDebug()<<"connect failed!";
    }



}
void TcpClient::onNewData(QByteArray readData)
{
    qDebug()<<"sendData!";
    this->write(readData);
    //this->write("test",4);
}
