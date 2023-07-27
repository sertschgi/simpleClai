#include "profile.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <exception>

#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>

const char* profile::ProfileNameError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: Profile has the same name as an other one!\033[0m";
}

const char* profile::NoSuchScopeError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: There is no such scope available!\033[0m";
}

const char* profile::NoSuchFrameworkError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: There is no such Framework available!\033[0m";
}

const char* profile::NoSuchModelError::what() const noexcept
{
    return "\033[31m[ERROR] <FATAL>: There is no such Model available!\033[0m";
}

void profile::createProfile
    (
    const QString& name,
    const QString& scope,
    const QString& framework
    )
{
    using namespace::std;

    QString appConfigPath = QDir::homePath() + "/." + QCoreApplication::applicationName();

    QJsonObject jsonProfiles = tools::getJsonObject(appConfigPath + "/config/profiles.json");

    if (jsonProfiles.contains(name))
    {
        throw profile::ProfileNameError();
    }

    const QJsonObject& jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");

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

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(jsonProfile) << "\033[0m";

    jsonProfiles[name] = newProfile;

    tools::writeJson(appConfigPath + "/config/profiles.json", jsonProfiles);
}

void profile::list()
{
    const QJsonObject& jsonProfiles = tools::getJsonObject(QDir::homePath() + "/." + QCoreApplication::applicationName() + "/config/profiles.json");

    qInfo() << tools::list(jsonProfiles);
}


