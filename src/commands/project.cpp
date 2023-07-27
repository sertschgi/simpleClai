#include "project.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <cstdlib> // for linux system variable
#include <exception>

#include <QCoreApplication>
#include <QDir>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>

const char* project::ProjectNameError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: Project has the same name as an other one!\033[0m";
}

const char* project::NoSuchModelError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: There is no such Model available!\033[0m";
}

const char* project::NoSuchDatasetError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: There is no such Dataset available!\033[0m";
}

const char* project::DatasetNotCompatibleLabelsError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: The labels of the dataset provided are not compatible with the labels required for the profile given.\033[0m";
}

void project::createProject
    (
    const QString& name,
    const QString& profile,
    const QString& dataset
    )
{
    using namespace::std;

    const QJsonObject& jsonProfiles = tools::getJsonObject("./config/projects.json");

    if (!jsonProfiles.contains(profile))
    {
        throw tools::NoSuchProfileError();
    }

    QJsonObject jsonProfile = jsonProfiles[profile].toObject();


    QJsonObject jsonProjects = tools::getJsonObject("./config/projects.json");

    if (jsonProjects.contains(name))
    {
        throw project::ProjectNameError();
    }

    const QJsonObject& jsonDatasets = tools::getJsonObject("./config/datasets.json");

    if (!jsonDatasets.contains(dataset))
    {
        throw project::NoSuchDatasetError();
    }

    QJsonObject newProject;

    newProject["profile"] = profile;
    newProject["dataset"] = dataset;

    const QString& framework = jsonProfile["framework"].toString();
    const QString& scope = jsonProfile["scope"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject("./config/frameworks.json");
    const QJsonObject& jsonProject = jsonFrameworks[framework][scope]["project"].toObject();

    QMap<QString, QString> replacements;
    replacements.insert("$NAME", name);

    const QString& script = tools::interpretPath(jsonProject["install_script"].toString(), replacements);

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(script) << "\033[0m";

    jsonProjects[name] = newProject;

    tools::writeJson("./config/projects.json", jsonProjects);
}

void project::list()
{
    QJsonObject jsonProjects = tools::getJsonObject(QDir::homePath() + "/." + QCoreApplication::applicationName() + "/config/projects.json");

    qInfo().noquote() << tools::list(jsonProjects).toUtf8();
}
