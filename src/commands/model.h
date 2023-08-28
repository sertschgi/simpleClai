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

void list
    (
    const QString& framework,
    const QString& scope
    );
}

#endif // MODEL_H
