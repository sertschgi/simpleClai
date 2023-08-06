#ifndef MODEL_H
#define MODEL_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace model
{
void createModel
    (
    const QString& name,
    const QString& project,
    const QString& model
    );

void trainModel
    (
    const QString& name,
    const QString& project
    );
}

#endif // MODEL_H
