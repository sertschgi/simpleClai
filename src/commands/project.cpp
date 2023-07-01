#include "project.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <cstdlib> // for linux system variable
#include <exception>

#include <QDir>
#include <QString>
#include <QFile>
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

    const QJsonObject& jsonProfiles = tools::getJsonObject(":/user_data/profiles.json");

    if (!jsonProfiles.contains(profile))
    {
        throw tools::NoSuchProfileError();
    }

    QJsonObject jsonProfile = jsonProfiles[profile].toObject();


    QJsonObject jsonProjects = tools::getJsonObject(":/user_data/projects.json");

    if (jsonProjects.contains(name))
    {
        throw project::ProjectNameError();
    }

    const QJsonObject& jsonDatasets = tools::getJsonObject(":/user_data/datasets.json");

    if (!jsonDatasets.contains(dataset))
    {
        throw project::NoSuchDatasetError();
    }

    QJsonObject newProject;

    newProject["profile"] = profile;
    newProject["dataset"] = dataset;

    const QString& framework = jsonProfile["framework"].toString();
    const QString& scope = jsonProfile["scope"].toString();

    const QJsonObject& jsonFrameworks = tools::getJsonObject(":/config/framework");
    const QJsonObject& jsonProject = jsonFrameworks[framework][scope]["project"].toObject();

    qDebug() << "Install Finished with output: " << tools::installProcess(jsonProject);

    jsonProjects[name] = newProject;

    tools::writeJson(":/user_data/profile.json", jsonProjects);
}
