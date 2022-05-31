#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect( socket,SIGNAL(connected()),this,SLOT(connected()));
    connect( socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect( socket,SIGNAL(error(QAbstractSocket::SocketError)),
             this,SLOT(error(QAbstractSocket::SocketError)));
    connect( socket,SIGNAL(hostFound()),this,SLOT(hostFound()));
    connect( socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect( socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    setMouseTracking(true); // E.g. set in your constructor of your widget.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    socket->connectToHost(ui->hostLineEdit->text(),5000);
}

void MainWindow::on_moveButton_clicked()
{
    QString request("<request><source new='true' name='new' port='system:capture_1' ><position x='1' y='1'/></source></request>" );
    QString request0("<request><source id='2'><position x='0.0' y='0.0'/></source></request>" );
    QByteArray ba;
    ba.append(request);
    ba.append('\0');
    socket->write(ba);
    //    for (int i=1; i<=1; i++) {
    //        double p = -0.1+i*1.0;
    //        QString moz("<request><source new='true' file='/home/cc/Desktop/Mozart_Mvt1.wav'  channel='" + QString::number(i) + "' ><position x='" + QString::number(p) + "' y='2'/></source></request>" );
    //        QByteArray ba;
    //        ba.append(moz);
    //        ba.append('\0');
    //        socket->write(ba);
    //    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if(event->button()==Qt::NoButton) { // a move event
        pt = event->pos();
        double dX = lastPt.x() - pt.x();
        double dY = lastPt.y() - pt.y();
        //    qDebug() << dX << dY;
        sa.moveX(dX*0.01);
        sa.moveY(dY*0.01);
    } else {
        sa.setX(.1);
        sa.setY(.1);
    }
    for (int i=0; i<62; i++) {
        QString request("<request><source id='"+QString::number(i+1)+
                        "'><position x='"+QString::number(sa.getX(i))+
                        "' y='"+QString::number(sa.getY(i))+
                        "'/></source></request>" );
//        qDebug() << request;
        QByteArray ba;
        ba.append(request);
        ba.append('\0');
        socket->write(ba);
    }
    lastPt = pt;
}

void MainWindow::readyRead()
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


void MainWindow::connected()
{
    ui->outputTextEdit->append("Connected to server");
}

void MainWindow::disconnected()
{
    ui->outputTextEdit->append("Disconnected from server");
}

void MainWindow::error(QAbstractSocket::SocketError socketError)
{
    QString errorStr=socket->errorString();
    ui->outputTextEdit->append("An error occured :"+ errorStr);
}

void MainWindow::hostFound()
{
    ui->outputTextEdit->append("Host found");
}

void MainWindow::bytesWritten(qint64 bytes)
{
    QString outString = QString::number(bytes) + " bytes writen.";
    ui->outputTextEdit->append(outString);

}

void MainWindow::on_disconnectButton_clicked()
{
    socket->disconnectFromHost();
}
