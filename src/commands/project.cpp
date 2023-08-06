#include "project.h"
#include "../utils/tools.h"
#include "../utils/errors.h"

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


void project::createProject
    (
    const QString& name,
    const QString& profile,
    const QString& dataset
    )
{
    using namespace::std;

    QString appConfigPath = QDir::homePath() + "/." + QCoreApplication::applicationName();

    QJsonObject jsonProfiles = tools::getJsonObject(appConfigPath + "/config/profiles.json");

    if (!jsonProfiles.contains(profile))
    {
        throw error::existence::NoSuchProfileError();
    }

    QJsonObject jsonProfile = jsonProfiles[profile].toObject();


    QJsonObject jsonProjects = tools::getJsonObject(appConfigPath + "/config/projects.json");

    if (jsonProjects.contains(name))
    {
        throw error::name::ProjectNameError();
    }

    const QJsonObject& jsonDatasets = tools::getJsonObject(appConfigPath + "/config/datasets.json");

    if (!jsonDatasets.contains(dataset))
    {
        throw error::existence::NoSuchDatasetError();
    }

    const QString& profilePath = jsonProfile["profile_path"].toString();
    const QString& projectPath = profilePath + "/projects/" + name;

    QJsonObject newProject;

    newProject["profile"] = profile;
    newProject["dataset"] = dataset;
    newProject["project_path"] = projectPath;

    const QString& framework = jsonProfile["framework"].toString();
    const QString& scope = jsonProfile["scope"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");
    const QJsonObject& jsonProject = jsonFrameworks[framework][scope]["project"].toObject();

    QMap<QString, QString> replacements;
    replacements.insert("$NAME", name);
    replacements.insert("$PROFILE_PATH", profilePath);

    const QString& script = tools::interpretPath(jsonProject["install_script"].toString(), replacements);

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(script) << "\033[0m";

    jsonProjects[name] = newProject;

    tools::writeJson(appConfigPath + "/config/projects.json", jsonProjects);
}

void project::list()
{
    QJsonObject jsonProjects = tools::getJsonObject(QDir::homePath() + "/." + QCoreApplication::applicationName() + "/config/projects.json");

    qInfo().noquote() << tools::list(jsonProjects).toUtf8();
}
