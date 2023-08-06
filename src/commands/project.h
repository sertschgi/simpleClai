#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace project
{
void createProject
    (
    const QString& name,
    const QString& profile,
    const QString& dataset
    );

void init_tf_object_detection
    (
    const QJsonObject& newProject
    );

void list();
}

#endif // PROJECT_H
