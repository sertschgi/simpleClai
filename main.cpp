#include <QCoreApplication>
#include <QDebug>

#include "./src/core/parser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("SimpleCLai");
    QCoreApplication::setApplicationVersion("0.0.1");

    qDebug() << "Test";

    clparser::parseArgs(a);

    return a.exec();
}
