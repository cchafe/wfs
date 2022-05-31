#include "tcp.h"
#include <QThread>
TCP::TCP()
{
    socket = new QTcpSocket(this);
    fprintf(stderr,"new QTcpSocket\n");
}

TCP::~TCP()
{
}

void TCP::connectToHost()
{
    socket->connectToHost(QString("127.0.0.1"),5000);
}

void TCP::readyRead()
{
    quint16 bytes =  socket->bytesAvailable();
    //    ui->outputTextEdit->append("----------------------------------------");
    //    ui->outputTextEdit->append(QString::number(bytes)+ " for you to read");
    //    ui->outputTextEdit->append("----------------------------------------");
    //    QByteArray ba= socket->readAll();
    //    QString dataString (ba);
    //    QString pos("<source id='5'><position");
    //    if (dataString.contains(pos)) {
    //        ui->outputTextEdit->append(dataString);
    //        QString request0("<request><source id='2'><position x='0.0' y='0.0'/></source></request>" );
    //        QByteArray ba;
    //        ba.append(request0);
    //        ba.append('\0');
    //        socket->write(ba);
    //    }
}


void TCP::connected()
{
    fprintf(stderr,"Connected to server\n");
}

void TCP::disconnected()
{
    fprintf(stderr,"Disconnected from server\n");
}

void TCP::error(QAbstractSocket::SocketError socketError)
{
    QString errorStr=socket->errorString();
    fprintf(stderr,"An error occured :%s\n",errorStr.toLocal8Bit().data());
}

void TCP::hostFound()
{
    fprintf(stderr,"Host found\n");
}

void TCP::bytesWritten(qint64 bytes)
{
    QString outString = QString::number(bytes) + " bytes writen.";
    fprintf(stderr,"%s\n",outString.toLocal8Bit().data());

}
