#include "frameworks.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <cstdlib> // for linux system variable
#include <exception>

#include <QCoreApplication>
#include <QString>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>

void frameworks::list()
{
    QJsonObject jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");

    qInfo().noquote() << tools::list(jsonFrameworks).toUtf8();
}
