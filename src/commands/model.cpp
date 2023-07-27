#include <Python.h>

#include "model.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <QProcess>
#include <exception>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


const char* model::ModelNameError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: Model has the same name as an other one!\033[0m";
}

const char* model::NoSuchModelError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: here is no such Model available!\033[0m";
}

const char* model::NoSuchProjectError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: There is no such Project available!\033[0m";
}


void model::createModel
    (
    const QString& name,
    const QString& project,
    const QString& model
    )
{
    using namespace::std;

    QJsonObject jsonProjects = tools::getJsonObject("./config/projects");

    if (!jsonProjects.contains(project))
    {
        throw model::NoSuchProjectError();
    }

    QJsonObject jsonProject = jsonProjects[project].toObject();

    QJsonObject jsonUserModels = jsonProject["models"].toObject();

    if (!jsonUserModels.contains(model))
    {
        throw model::ModelNameError();
    }

    const QString& profile = jsonProject["profile"].toString();
    const QJsonObject& jsonProfiles = tools::getJsonObject("../../config/profiles");
    const QJsonObject& jsonProfile = jsonProfiles[profile].toObject();

    const QString& scope = jsonProfile["scope"].toString();
    const QString& framework = jsonProfile["framework"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject("../../config/framework");
    const QJsonObject& jsonScope = jsonFrameworks[framework][scope].toObject();
    const QJsonObject& jsonModels = jsonScope["models"].toObject();

    if (!jsonModels.contains(model))
    {
        throw model::NoSuchModelError();
    }
    
    const QJsonObject& jsonModel = jsonModels[model].toObject();

    QMap<QString, QString> replacements;
    replacements.insert("$NAME", name);

    const QString& script = tools::interpretPath(jsonModel["install_script"].toString(), replacements);

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(script) << "\033[0m";

    QJsonObject newModel;

    newModel["model"] = model;
    jsonProjects[project].toObject()["models"].toObject()[name].toObject() = newModel;
    tools::writeJson("../../config/projects", jsonProjects);
}

void model::trainModel
    (
    const QString& name,
    const QString& project
    )
{
    QJsonObject jsonProjects = tools::getJsonObject("../../config/projects");

    if (!jsonProjects.contains(project))
    {
        throw model::NoSuchProjectError();
    }

    QJsonObject jsonProject = jsonProjects[project].toObject();

    if (!jsonProjects["models"].toObject().contains(name))
    {
        throw model::NoSuchModelError();
    }
    const QString& profile = jsonProject["profile"].toString();
    const QJsonObject& jsonProfiles = tools::getJsonObject("../../config/profiles");
    const QJsonObject& jsonProfile = jsonProfiles[profile].toObject();

    const QString& scope = jsonProfile["scope"].toString();
    const QString& framework = jsonProfile["framework"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject("../../config/framework");
    const QJsonObject& jsonScope = jsonFrameworks[framework][scope].toObject();

    Py_Initialize();

    Py_SetPythonHome(jsonProfile["python_path"].toString().toStdWString().c_str());

    const char* scriptPath = jsonScope["training_script"].toString().toUtf8().constData();
    FILE* scriptFile = fopen(scriptPath, "r");
    if (scriptFile) {
        PyRun_SimpleFile(scriptFile, scriptPath);
        fclose(scriptFile);
    } else {
        qFatal() << "No script.. is it deleted?";
    }

    Py_Finalize();

}
