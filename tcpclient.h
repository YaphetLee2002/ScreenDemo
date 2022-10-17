#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>

class TcpClient : public QTcpSocket
{
public:
    TcpClient(QWidget* parent = 0);
    QHostAddress *ip;
    quint16 port;
    void ConServer();
public slots:
    void onNewData(QByteArray readData);
};

#endif // TCPCLIENT_H
