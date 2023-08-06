#include "profile.h"
#include "../utils/tools.h"
#include "../utils/errors.h"

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
        throw error::name::ProfileNameError();
    }

    const QJsonObject& jsonFrameworks = tools::getJsonObject("/etc/" + QCoreApplication::applicationName() + "/config/frameworks.json");

    if (!jsonFrameworks.contains(framework))
    {
        throw error::existence::NoSuchFrameworkError();
    }

    qDebug() << "\033[90m[DEBUG]: Scope is:" << scope << "\033[0m";

    const QJsonObject& jsonScopes = jsonFrameworks[framework].toObject();

    qDebug() << "\033[90m[DEBUG]: Json-scopes is:" << jsonScopes << "\033[0m";

    if (!jsonScopes.contains(scope))
    {
        throw error::existence::NoSuchScopeError();
    }

    const QJsonObject& jsonScope = jsonScopes[scope].toObject();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString profilePath = env.value("PROFILE_PATH");

    if (profilePath.isEmpty())
    {
        error::environment::SA_PROFILE_Error error;

        profilePath = appConfigPath + "/profiles";

        qInfo() << error.what() << "\033[36m"
                << "Default:" << profilePath
                << "\033[0m";

        // set the $SA_PROFILE_PATH for debian
        qDebug() << "\033[90m[DEBUG]: Script executed with output:"
                 << tools::installProcess("/etc/" + QCoreApplication::applicationName() + "/scripts/set_debian_env.sh PROFILE_PATH " + profilePath)
                 << "\033[0m";
    }

    const QString& thisProfilePath = profilePath + "/" + name;

    qInfo() << "\033[32m[INFO]: Your profile will be stored in:\033[35m" << thisProfilePath << "\033[0m";

    const QString& apiPath = thisProfilePath + "/api";

    QMap<QString, QString> replacements;
    replacements.insert("$NAME", name);
    replacements.insert("$API_PATH", apiPath);

    // const QString& pythonPath = tools::interpretPath(jsonScopes["interpreter"].toString(), replacements);

    QJsonObject newProfile;

    newProfile["scope"] = scope;
    newProfile["framework"] = framework;
    newProfile["profile_path"] = thisProfilePath;
    newProfile["api_path"] = apiPath;
    // newProfile["interpreter"] = pythonPath;

    const QJsonObject& jsonProfile = jsonScope["profile"].toObject();

    const QString& script = tools::interpretPath(jsonProfile["install_script"].toString(), replacements);

    qDebug() << "\033[32m[INFO]: Install Finished with output: " << tools::installProcess(script, QStringList() << QString("PROFILE_PATH=") + profilePath) << "\033[0m";

    jsonProfiles[name] = newProfile;

    tools::writeJson(appConfigPath + "/config/profiles.json", jsonProfiles);
}

void profile::list()
{
    const QJsonObject& jsonProfiles = tools::getJsonObject(QDir::homePath() + "/." + QCoreApplication::applicationName() + "/config/profiles.json");

    qInfo().noquote() << tools::list(jsonProfiles).toUtf8();
}


