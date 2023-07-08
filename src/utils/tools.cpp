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
        qCritical() << "Could not find resource file! Is it deleted?";
    }

    QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError parsingError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parsingError);

    if (parsingError.error != QJsonParseError::NoError) {
        qCritical() << "File Syntax wrong or uncompleted! Is the file corrupted?";
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
        qCritical() << "Could not find resource file! Is it deleted?";
    }

    QJsonDocument jsonDoc(jsonObject);
    jsonFile.write(jsonDoc.toJson());

    if (!jsonFile.commit())
    {
        qCritical() << "Could not save the file! Try again!?";
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

    QString progressBar = QString("[%1%2%3]").arg(QString(completedWidth, '#'),
                                                  QString(barWidth - completedWidth, ' '),
                                                  QString::number(progress * 100 / total));
    qDebug() << progressBar;
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
        if (destination.mkdir(destDir)) //potential bug destination is technicly already destDir?.
        {
            qDebug() << "created Directory";
        } else
        {
            qCritical() << "Failed to create Directory!";
        }
    }

    QDir directory(sourceDir);
    QStringList files = directory.entryList(extensions, QDir::Files | QDir::NoDotAndDotDot);

    for (int i = 0; i < files.length(); i++)
    {
        QString sourcePath = directory.filePath(files[i]);
        QString destPath = QDir(destDir).filePath(files[i]);

        if (QFile::copy(sourcePath, destPath))
        {
            tools::updateProgressBar(i, files.length());
        }
        else
        {
            qDebug() << "Failed to move file:" << files[i];
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


