#include "profile.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <exception>

#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>



class profile::ProfileNameError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Profile has the same name as an other one!";
    }
};

class profile::NoSuchScopeError : public std::exception {
public:
    const char* what() const noexcept override {
        return "There is no such scope available!";
    }
};

class profile::NoSuchFrameworkError : public std::exception {
public:
    const char* what() const noexcept override {
        return "There is no such Framework available!";
    }
};

class profile::NoSuchModelError : public std::exception {
public:
    const char* what() const noexcept override {
        return "There is no such Model available!";
    }
};


void profile::createProfile
    (
    const QString& name,
    const QString& scope,
    const QString& framework
    )
{
    using namespace::std;

    QJsonObject jsonProfiles = tools::getJsonObject("../../config/profiles.json");

    if (jsonProfiles.contains(name))
    {
        throw profile::ProfileNameError();
    }

    const QJsonObject& jsonFrameworks = tools::getJsonObject("../../config/frameworks.json");

    if (!jsonFrameworks.contains(framework))
    {
        throw profile::NoSuchFrameworkError();
    }

    const QJsonObject& jsonScopes = jsonFrameworks[framework][scope].toObject();

    if (!jsonProfiles.contains(scope))
    {
        throw profile::NoSuchScopeError();
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    const QString& profilePath = env.value("$SA_PROFILE_PATH") + name;

    const QString& apiPath = profilePath + "api";

    QMap<QString, QString> replacements;
    replacements.insert("$NAME", name);
    replacements.insert("$API_PATH", apiPath);

    const QString& pythonPath = tools::interpretPath(jsonScopes["interpreter"].toString(), replacements);

    QJsonObject newProfile;

    newProfile["scope"] = scope;
    newProfile["framework"] = framework;
    newProfile["profile_path"] = profilePath;
    newProfile["api_path"] = apiPath;
    newProfile["interpreter"] = pythonPath;

    const QJsonObject& jsonProfile = jsonScopes["profile"].toObject();

    qDebug() << "Install Finished with output: " << tools::installProcess(jsonProfile);

    jsonProfiles[name] = newProfile;

    tools::writeJson(":/user_data/profiles.json", jsonProfiles);
}

void profile::list()
{
    const QJsonObject& jsonProfiles = tools::getJsonObject("../../config/profiles.json");

    qInfo() << tools::list(jsonProfiles);
}


