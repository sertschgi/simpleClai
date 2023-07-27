#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "./src/core/parser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("sclai");
    QCoreApplication::setApplicationVersion("0.0.1");

    clparser::parseArgs(a);

    qInfo() << "\033[32m[INFO]: Finished!\033[0m";

    return 0;
}
