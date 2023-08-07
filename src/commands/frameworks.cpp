#include "frameworks.h"
#include "../utils/tools.h"

#include <QCoreApplication>
#include <QDebug>
#include <QJsonObject>

void frameworks::list()
{
    QJsonObject jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");

    qInfo().noquote() << tools::list(jsonFrameworks).toUtf8();
}
