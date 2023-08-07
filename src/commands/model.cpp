#include <Python.h>

#include "model.h"
#include "../utils/tools.h"
#include "../utils/errors.h"

#include <iostream>
#include <cstdint>
#include <QProcess>
#include <exception>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

void model::createModel
    (
    const QString& name,
    const QString& project,
    const QString& model
    )
{
    using namespace::std;

    QString appConfigPath = QDir::homePath() + "/." + QCoreApplication::applicationName();

    QJsonObject jsonProjects = tools::getJsonObject(appConfigPath + "/config/projects.json");

    if (!jsonProjects.contains(project))
    {
        throw error::existence::NoSuchProjectError();
    }

    QJsonObject jsonProject = jsonProjects[project].toObject();

    QJsonObject jsonUserModels = jsonProject["models"].toObject();

    if (jsonUserModels.contains(model))
    {
        throw error::name::ModelNameError();
    }

    const QString& profile = jsonProject["profile"].toString();
    const QJsonObject& jsonProfiles = tools::getJsonObject(appConfigPath + "/config/profiles.json");
    const QJsonObject& jsonProfile = jsonProfiles[profile].toObject();

    const QString& scope = jsonProfile["scope"].toString();
    const QString& framework = jsonProfile["framework"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");
    const QJsonObject& jsonScope = jsonFrameworks[framework].toObject()[scope].toObject();
    const QJsonObject& jsonModels = jsonScope["models"].toObject();

    if (!jsonModels.contains(model))
    {
        throw error::existence::NoSuchModelError();
    }
    
    const QJsonObject& jsonModel = jsonModels[model].toObject();

    const QString& projectPath = jsonProject["project_path"].toString();
    const QString& modelPath = projectPath + "/models/" + name;

    QMap<QString, QString> replacements;
    replacements.insert("$NAME", name);
    replacements.insert("$MODEL_PATH", modelPath);

    const QString& script = tools::interpretPath(jsonModel["install_script"].toString(), replacements);

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(script) << "\033[0m";

    QJsonObject newModel;

    newModel["model"] = model;
    newModel["model_path"] = modelPath;

    jsonProjects[project].toObject()["models"].toObject()[name].toObject() = newModel;
    tools::writeJson(appConfigPath + "/config/projects.json", jsonProjects);
}



void model::trainModel
    (
    const QString& name,
    const QString& project
    )
{
    QString appConfigPath = QDir::homePath() + "/." + QCoreApplication::applicationName();

    QJsonObject jsonProjects = tools::getJsonObject(appConfigPath + "/config/projects.json");

    if (!jsonProjects.contains(project))
    {
        throw error::existence::NoSuchProjectError();
    }

    QJsonObject jsonProject = jsonProjects[project].toObject();

    if (!jsonProjects["models"].toObject().contains(name))
    {
        throw error::existence::NoSuchModelError();
    }
    const QString& profile = jsonProject["profile"].toString();
    QJsonObject jsonProfiles = tools::getJsonObject(appConfigPath + "/config/profiles.json");
    const QJsonObject& jsonProfile = jsonProfiles[profile].toObject();

    const QString& scope = jsonProfile["scope"].toString();
    const QString& framework = jsonProfile["framework"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");
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
