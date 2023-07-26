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
#include <QResource>


const char* tools::NoSuchProfileError::what() const noexcept
{
    return "There is no such Profile available!";
}

QJsonObject tools::getJsonObject
    (
    const QString& filename
    )
{
    QFile jsonFile(filename);

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "\033[36m[ALERT]: Could not find resource file. Creating a new one.\033[0m";

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

    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "\033[33m[ERROR] <CRITICAL>: Could not create new File!\033[0m";
    }

    QJsonDocument jsonDoc(jsonObject);
    jsonFile.write(jsonDoc.toJson());

    if (!jsonFile.commit())
    {
        qFatal() << "\033[31m[ERROR] <FATAL>: Could not save the file! Try again!?\033[0m";
    }
}

void tools::updateProgressBar
    (
    int progress,
    int total
    )
{
    const int barWidth = 40;
    int completedWidth = barWidth * progress / total;

    qInfo() << "\033[36m[PROGRESS]:"
             << (QString("[%1%2] %3\%").arg(QString(completedWidth, '#'),
                                           QString(barWidth - completedWidth, ' '),
                                           QString::number(100 * progress / total)
                                           )).toLocal8Bit().data()
             << "\033[0m";
}

int tools::copyFilesWithExtention
    (
    const QString& sourceDir,
    const QString& destDir,
    const QStringList& extensions
    )
{
    QDir destination(destDir);

    if (!destination.exists())
    {
        qCritical() << "\033[36m[ALERT]: Could not find the" << destDir << "directory. Creating a new one.\033[0m";

        if (destination.mkpath(destDir))
        {
            qInfo() << "\033[32m[INFO]: Successfully created directory!\033[0m";
        } else
        {
            qFatal() << "\033[31m[ERROR] <FATAL>: Failed to create directory!\033[0m";
        }
    }

    QDir directory(sourceDir);
    QStringList files = directory.entryList(extensions, QDir::Files | QDir::NoDotAndDotDot);

    qInfo() << "\033[32m[INFO]:"
            << files.size() << "files will be copied from\033[35m"
            << directory.absolutePath() << "\033[32mto\033[35m"
            << destDir;
    qInfo() << "\033[32m[INFO]: Files:\033[35m" << files.join(", ") << "\033[0m";


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
    const QJsonObject& object
    )
{
    const QString& script = object["install_script"].toString();

    QString terminal;

    if (object.contains("install_terminal"))
    {
        terminal = object["install_terminal"].toString();
    }
    else
    {
        terminal = "/bin/bash";
    }

    QProcess installationProcess;

    QStringList arguments; arguments << script;

    installationProcess.start(terminal, arguments);
    installationProcess.waitForFinished();

    QByteArray output = installationProcess.readAllStandardOutput();
    QString qoutput = QString::fromUtf8(output);
    return qoutput;
}

QString tools::interpretPath
    (
    const QString& path,
    const QMap<QString, QString>& replacements
    )
{
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

    for (const QJsonValueConstRef refChildObject : object)
    {
        if (refChildObject.isObject())
        {
            QJsonObject childObject = refChildObject.toObject();

            outStr += childObject.keys()[0] + "\n"
                + "  |" + "\n";

            for (QString key : childObject.keys())
            {
                outStr  += "  |--" + key + "-> ";

                if (childObject[key].isObject())
                {
                    outStr += tools::list(childObject[key].toObject());
                }
            }
        }

    }
    return outStr;
}


