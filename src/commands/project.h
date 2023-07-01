#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace project
{
class ProjectNameError;
class NoSuchProfileError;
class NoSuchModelError;
class NoSuchDatasetError;
class DatasetNotCompatibleLabelsError;

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
}



#endif // PROJECT_H