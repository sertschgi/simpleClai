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
const char* profile::SA_PROFILE_ERROR::what() const noexcept
{
    return "\033[36m[ALERT]: Could not find SA_DATASET_PATH. Is it deleted? Please set it to a Path where your DATASET will be stored.\033[0m";
}

void profile::createProfile
    (
    const QString& name,
    const QString& framework,
    const QString& scope
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

    qDebug() << "\033[90m[DEBUG]: Scope is:" << scope << "\033[0m";

    const QJsonObject& jsonScopes = jsonFrameworks[framework].toObject();

    qDebug() << "\033[90m[DEBUG]: Json-scopes is:" << jsonScopes << "\033[0m";

    if (!jsonScopes.contains(scope))
    {
        throw profile::NoSuchScopeError();
    }

    const QJsonObject& jsonScope = jsonScopes[scope].toObject();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString profilePath = env.value("$SA_PROFILE_PATH");

    if (profilePath.isEmpty())
    {
        profile::SA_PROFILE_ERROR error;

        profilePath = appConfigPath + "/profiles";

        qInfo() << error.what() << "\033[36m"
                << "Default:" << profilePath
                << "\033[0m";
    }

    profilePath = profilePath + "/" + name;

    qInfo() << "\033[32m[INFO]: Your profile will be stored in:\033[35m" << profilePath << "\033[0m";

    const QString& apiPath = profilePath + "/api";

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

    const QJsonObject& jsonProfile = jsonScope["profile"].toObject();

    const QString& script = tools::interpretPath(jsonProfile["install_script"].toString(), replacements);

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(script) << "\033[0m";

    jsonProfiles[name] = newProfile;

    tools::writeJson(appConfigPath + "/config/profiles.json", jsonProfiles);
}

void profile::list()
{
    const QJsonObject& jsonProfiles = tools::getJsonObject(QDir::homePath() + "/." + QCoreApplication::applicationName() + "/config/profiles.json");

    qInfo().noquote() << tools::list(jsonProfiles).toUtf8();
}


