#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace profile
{
class ProfileError : public std::exception
{
public:
    virtual const char* what() const noexcept = 0;
};
class ProfileNameError : public ProfileError
{
public:
    const char* what() const noexcept override;
};
class NoSuchScopeError : public ProfileError
{
public:
    const char* what() const noexcept override;
};
class NoSuchFrameworkError : public ProfileError
{
public:
    const char* what() const noexcept override;
};
class NoSuchModelError : public ProfileError
{
public:
    const char* what() const noexcept override;
};
class SA_PROFILE_ERROR : public ProfileError
{
public:
    const char* what() const noexcept override;
};

void createProfile
    (
    const QString& name,
    const QString& framework,
    const QString& scope
    );

void list();
}


#endif // PROFILE_H
