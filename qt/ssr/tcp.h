#ifndef TCP_H
#define TCP_H

#include <QTcpSocket>

class TCP : QObject
{
    Q_OBJECT

public:
    explicit TCP();
    ~TCP();
    void connectToHost();
    void sendToHost(double x, double y);
    void addSrc(int i, double x, double y);
    void mvSrc(int i, double x, double y, double z);
QTcpSocket * socket;
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void hostFound();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // TCP_H
