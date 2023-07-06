#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "./src/core/parser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("SimpleCLai");
    QCoreApplication::setApplicationVersion("0.0.1");

    clparser::parseArgs(a);

    return a.exec();
}
