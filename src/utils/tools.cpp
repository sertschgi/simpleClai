#include "tools.h"

#include <string>
#include <iostream>
#include <exception>

#include <QString>
#include <QSaveFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QProcess>
#include <QMap>
#include <QStandardPaths>
#include <QResource>


QJsonObject tools::getJsonObject
    (
    const QString& filename
    )
{
    QFile jsonFile(filename);

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "\033[36m[ALERT]: Could not find resource file:" << filename << "Creating a new one.\033[0m";

        return QJsonObject();
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError parsingError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parsingError);

    if (parsingError.error != QJsonParseError::NoError) {
        qCritical() << "\033[33m[ERROR] <CRITICAL>: File Syntax wrong or uncompleted! Is the file corrupted?\033[0m";
    }

    QJsonObject jsonObject = jsonDoc.object();

    return jsonObject;
}

void tools::writeJson
    (
    const QString& filename,
    QJsonObject jsonObject
    )
{
    QSaveFile jsonFile(filename);

    QDir().mkpath(QFileInfo(filename).absolutePath());

    // qDebug() << "\033[90m[DEBUG]: Json file properties:" << jsonFile.fileName() << "\033[0m";

    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qCritical() << "\033[33m[ERROR] <CRITICAL>: Could not create new File!:\033[35m" << filename << "\033[0m";
    }

    QJsonDocument jsonDoc(jsonObject);
    jsonFile.write(jsonDoc.toJson());

    if (!jsonFile.commit())
    {
        qFatal() << "\033[31m[ERROR] <FATAL>: Could not save the file! Try again!?\033[0m";
    }

    qInfo() << "\033[32m[INFO]: Successfully saved file!\033[35m" << filename << "\033[0m";
}

void tools::updateProgressBar
    (
    int progress,
    int total
    )
{
    const int barWidth = 40;
    int completedWidth = barWidth * progress / total;

    QString progressBar;

    if (progress > 0)
    {
        progressBar += "\033[1A\033[K\033[s";
    }

    progressBar += "\033[34m[PROGRESS]:";
    progressBar += (QString("[%1%2] %3\%").arg(QString(completedWidth, '#'),
                                           QString(barWidth - completedWidth, '.'),
                                           QString::number(100 * progress / total)
                                               )).toLocal8Bit().data();
    progressBar += "\033[0m";

    qInfo().noquote() << progressBar;
}

void tools::createPath
    (
    const QString& path
    )
{
    QDir destination(path);

    if (!destination.exists())
    {
        qCritical() << "\033[36m[ALERT]: Could not find the" << path << "directory. Creating a new one.\033[0m";

        if (destination.mkpath(path))
        {
            qInfo() << "\033[32m[INFO]: Successfully created directory!\033[0m";
        } else
        {
            qFatal() << "\033[31m[ERROR] <FATAL>: Failed to create directory!\033[0m";
        }
    }
}

int tools::copyFilesWithExtention
    (
    const QString& sourceDir,
    const QString& destDir,
    const QStringList& extensions
    )
{
    tools::createPath(destDir);

    QDir directory(sourceDir);

    QStringList filters;

    for (QString ext : extensions)
    {
        filters.append("*." + ext);
    }

    qDebug() << "\033[90m[DEBUG]: Filters are:" << filters << "\033[0m";

    QStringList files = directory.entryList(filters, QDir::Files | QDir::NoDotAndDotDot);

    qInfo() << "\033[32m[INFO]:"
            << files.size() << "files will be copied from\033[35m"
            << directory.absolutePath() << "\033[32mto\033[35m"
            << destDir;
    qInfo() << "\033[90m[DEBUG]: Files:" << files.join(", ") << "\033[0m";


    qInfo().noquote() << "\033[32m[INFO]: Only" << extensions.size() << "supported formats:" << extensions.join(", ") << "\033[0m";


    for (int i = 0; i < files.length(); i++)
    {
        QString sourcePath = directory.filePath(files[i]);
        QString destPath = QDir(destDir).filePath(files[i]);

        if (QFile::copy(sourcePath, destPath))
        {
            tools::updateProgressBar(i+1, files.length());
        }
        else
        {
            qCritical() << "\033[33m[ERROR] <CRITICAL>: Failed to move file:\033[35m" << files[i] << "\033[0m";
        }
    }

    return files.length();
}

QString tools::installProcess
    (
    const QString& script,
    const QStringList& envVars
    )
{
    QStringList scriptParts = script.split(" ");
    QString standaloneScript = scriptParts.first();

    if (!QFile::exists(standaloneScript) || standaloneScript == "")
    {
        qFatal() << "\033[31m[ERROR] <FATAL>: Could not find script! Path:" << standaloneScript << "\033[0m";
    }

    qDebug() << "\033[90m[DEBUG]: Using standalone script:" << standaloneScript << "\033[0m";
    qDebug() << "\033[90m[DEBUG]: Using script:" << script << "\033[0m";

    QString terminal = "/bin/bash";

    QStringList arguments;
    arguments << "-i" << "-c" << "source " + script;

    qDebug() << "\033[90m[DEBUG]: Using arguments:" << arguments << "\033[0m";

    QFile::setPermissions(standaloneScript, QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner);

    QProcess installationProcess;

    installationProcess.setEnvironment(envVars);

    const QString& workDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/."+QCoreApplication::applicationName()+"/tmp";
    tools::createPath(workDir);

    installationProcess.setWorkingDirectory(workDir);

    qDebug() << "\033[90m[DEBUG]: Work dir:" << installationProcess.workingDirectory() << "\033[0m";

    installationProcess.start(terminal, arguments);

    qInfo() << "\033[32m[INFO]: Live output:\033[90m";

    // QString pattern = "\\n *\\d+ +\\d+M +([0-9]+)";
    // QString condaProgressPattern = " *([0-9]+) *\\d+M";

    int errorCount = 0;

    QObject::connect(
        &installationProcess,
        &QProcess::readyReadStandardOutput,
        [&]() {
            QByteArray outputData = installationProcess.readAllStandardOutput();
            qDebug().noquote() << "\033[35m[SCRIPT_INFO]:" << outputData.toStdString() << "\033[90m";
        });

    QObject::connect(
        &installationProcess,
        &QProcess::readyReadStandardError,
        [&]() {
            QString errorData = QString::fromUtf8(installationProcess.readAllStandardError());
            qCritical().noquote() << errorData;
            if (errorData.contains("error",Qt::CaseInsensitive))
            {
                errorCount += 1;
            }
        });

    qInfo() << "\033[0m";

    if (installationProcess.waitForFinished(-1) && errorCount == 0)
    {
        QByteArray output = installationProcess.readAllStandardOutput();
        return QString(output);
    }
    qFatal() << "\033[31m[ERROR] <FATAL>: Script errored! Count(" << errorCount << "):" << installationProcess.readAllStandardError() << "\033[0m";
}

QString tools::interpretPath
    (
    const QString& path,
    QMap<QString, QString> replacements
    )
{
    replacements.insert("$APP_SCRIPTS_PATH", QString("/etc/" + QCoreApplication::applicationName()));

    QString result = path;

    for (auto it = replacements.constBegin(); it != replacements.constEnd(); ++it)
    {
        result.replace(it.key(), it.value());
    }

    return result; // potential issue as well
}

const QString tools::list
    (
    const QJsonObject& object
    )
{
    QString outStr;

    if (!object.isEmpty())
    {
        for (const QString& objectName : object.keys())
        {
            QJsonObject childObject = object.value(objectName).toObject();

            outStr += "[" + objectName + "]\n"
                + "  |" + "\n";

            for (const QString& childObjectName : childObject.keys())
            {
                if (!childObject.value(childObjectName).isObject())
                {
                    outStr += "  |--(" + childObjectName + ")-->" + childObject.value(childObjectName).toString() + "\n";
                }
                else
                {
                    outStr += "  |--[" + childObjectName + "]-+\n";
                }
            }
            outStr += QString() + "  |" + "\n";
        }
        outStr += QString() +  "  °" + "\n";
    }
    else
    {
        qInfo() << "\033[32m[INFO]: Nothing to list.\033[0m";
    }
    return outStr;
}


