#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace project
{
class ProjectError : public std::exception
{
public:
    virtual const char* what() const noexcept = 0;
};
class ProjectNameError : public ProjectError
{
public:
    const char* what() const noexcept override;
};
class NoSuchProfileError : public ProjectError
{
public:
    const char* what() const noexcept override;
};
class NoSuchModelError : public ProjectError
{
public:
    const char* what() const noexcept override;
};
class NoSuchDatasetError : public ProjectError
{
public:
    const char* what() const noexcept override;
};
class DatasetNotCompatibleLabelsError : public ProjectError
{
public:
    const char* what() const noexcept override;
};

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
