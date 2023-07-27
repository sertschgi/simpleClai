#ifndef MODEL_H
#define MODEL_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace model
{
class ModelError : public std::exception
{
public:
    virtual const char* what() const noexcept = 0;
};
class ModelNameError : public ModelError
{
public:
    const char* what() const noexcept override;
};
class NoSuchProjectError : public ModelError
{
public:
    const char* what() const noexcept override;
};
class NoSuchModelError : public ModelError
{
public:
    const char* what() const noexcept override;
};

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
