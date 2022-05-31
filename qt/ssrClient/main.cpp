#include "mainwindow.h"
#include <QApplication>

//http://www.blikoontech.com/networking/http-potocol-writting-a-simple-client-using-qt-qtcpsocket-and-
//troubleshooting-using-telnet

#include <QLoggingCategory>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    fprintf(stderr, "%s\n", localMsg.constData());
    fflush(stderr);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=true\nqt.*.debug=false"));
    qInstallMessageHandler(myMessageOutput);
    MainWindow w;
    w.show();

    return a.exec();
}
