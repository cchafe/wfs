#include "tcp.h"
#include <QThread>
TCP::TCP()
{
    socket = new QTcpSocket(this);
//    fprintf(stderr,"new QTcpSocket\n");
}

TCP::~TCP()
{
}

#define HOST_IP "127.0.0.1"

void TCP::connectToHost()
{
    socket->connectToHost(QString(HOST_IP),5000);
}

void TCP::sendToHost(double x, double y)
{
    int i = 0;
    QString request("<request><source id=\""+QString::number(i+1)+
                    "\"><position x=\""+QString::number(x)+
                    "\" y=\""+QString::number(y)+
                    "\"/></source></request>" );
    QByteArray ba;
    ba.append(request);
    ba.append('\n');
    socket->write(ba);
    socket->waitForBytesWritten(1000);
//    socket->waitForReadyRead(3000);
//    fprintf(stderr,"wrote :%s\n",request.toLocal8Bit().data());
}

// Error: Either file name or port name must be specified! (legacy_network/commandparser.cpp:239)
// so using BinauralRenderer:in_<n>
#define SSR_BR "BinauralRenderer"
#define SSR_BRS "BrsRenderer"
void TCP::addSrc(int i, double x, double y)
{
    QString request("<request><source new=\"true\" name=\"src"+QString::number(i)+
                    "\" port=\""+SSR_BR+":in_"+QString::number(i)+
                    "\" ><position x=\""+QString::number(x)+
                    "\" y=\""+QString::number(y)+
                    "\"/></source></request>" );
    QByteArray ba;
    ba.append(request);
    ba.append('\n');
    socket->write(ba);
    socket->waitForBytesWritten(1000);
//    socket->waitForReadyRead(3000);
//    fprintf(stderr,"wrote :%s\n",request.toLocal8Bit().data());
}

void TCP::mvSrc(int i, double x, double y, double z)
{
    QString request("<request><source id=\""+QString::number(i+1)+
                    "\"><position x=\""+QString::number(x)+
                    "\" y=\""+QString::number(y)+
                    "\"/></source></request>" );
    QByteArray ba;
    ba.append(request);
    ba.append('\n');
    if (socket->state()==QTcpSocket::ConnectedState) {
        socket->write(ba);
        socket->waitForBytesWritten(1000);
    }
//    socket->waitForReadyRead(3000);
//    fprintf(stderr,"wrote :%s\n",request.toLocal8Bit().data());
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
