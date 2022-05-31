#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
#include <QTcpSocket>
#include <QMainWindow>
#include "sourcearray.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_connectButton_clicked();
    void on_moveButton_clicked();

    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void hostFound();
    void bytesWritten(qint64 bytes);
    void readyRead();

    void on_disconnectButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket * socket;
    QPoint pt;
    QPoint lastPt;
    double x[17];
    double y;
    SourceArray sa;
};

#endif // MAINWINDOW_H
