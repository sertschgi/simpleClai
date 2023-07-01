#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace profile
{
class ProfileNameError;
class NoSuchScopeError;
class NoSuchFrameworkError;
class NoSuchModelError;

void createProfile
    (
    const QString& name,
    const QString& scope,
    const QString& framework
    );
}


#endif // PROFILE_H
