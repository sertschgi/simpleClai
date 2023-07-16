#include "project.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <cstdlib> // for linux system variable
#include <exception>

#include <QDir>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>


class project::ProjectNameError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Project has the same name as an other one!";
    }
};

class project::NoSuchModelError : public std::exception {
public:
    const char* what() const noexcept override {
        return "There is no such Model available!";
    }
};

class project::NoSuchDatasetError : public std::exception {
public:
    const char* what() const noexcept override {
        return "There is no such Dataset available!";
    }
};

class project::DatasetNotCompatibleLabelsError : public std::exception {
public:
    const char* what() const noexcept override {
        return "The labels of the dataset provided are not compatible with the labels required for the profile given.";
    }
};

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

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(jsonProject) << "\033[0m";

    jsonProjects[name] = newProject;

    tools::writeJson("./config/projects.json", jsonProjects);
}

void project::list()
{
    QJsonObject jsonProjects = tools::getJsonObject("./config/projects.json");

    qInfo() << tools::list(jsonProjects);
}
