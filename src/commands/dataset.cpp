#include "dataset.h"
#include "../utils/tools.h"
#include "../utils/errors.h"

#include <iostream>
#include <cstdint>
#include <cstdlib> // for linux system variable
#include <exception>

#include <QCoreApplication>
#include <QString>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>

void dataset::createDataset
    (
        const QString& name,
        const QString& labelmapPath,
        const QString& imagesPath,
        const QString& labelsPath
        )
{
    using namespace::std;

    QString appConfigPath = QDir::homePath() + "/." + QCoreApplication::applicationName();

    QJsonObject jsonDatasets = tools::getJsonObject(appConfigPath + "/config/datasets.json");
    QJsonObject newDataset;

    if (jsonDatasets.contains(name))
    {
        throw error::name::DatasetNameError();
    }


    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString datasetPath = env.value("SA_DATASET_PATH");

    if (datasetPath.isEmpty())
    {
        error::environment::SA_DATASET_Error error;

        /* QString username = qgetenv("USER");
        if (username.isEmpty())
        {
            username = qgetenv("USERNAME");
        }

        if (username == "root")
        {
            qCritical() << "\033[33m[ERROR] <CRITICAL>: Running as root!\033[0m";
            datasetPath = "./datasets";
        }
        else
        {
            datasetPath = "/home/" + username + "/.simpleCLai/datasets";
        } */

        datasetPath = appConfigPath + "/datasets";

        qInfo() << error.what() << "\033[36m"
                << "Default:" << datasetPath
                << "\033[0m";
    }

    datasetPath = datasetPath + "/" + name;

    qInfo() << "\033[32m[INFO]: Your dataset will be stored in:\033[35m" << datasetPath << "\033[0m";

    const QString newImagesPath = datasetPath + "/images";
    const QString newLabelsPath = datasetPath + "/labels";

    QSettings settings("/etc/" + QCoreApplication::applicationName() + "/config/config.ini", QSettings::IniFormat);

    QStringList label_formats = settings.value("dataset/supported_labeling_formats").toStringList();

    if (tools::copyFilesWithExtention(labelsPath,newLabelsPath,label_formats) == 0)
    {
        throw error::compatibility::LabelExtentionError();
    }

    QStringList img_formats = settings.value("dataset/supported_img_formats").toStringList();

    if (tools::copyFilesWithExtention(imagesPath,newImagesPath,img_formats) == 0)
    {
        throw error::compatibility::ImageExtentionError();
    }

    const QString& newLabelmapPath = datasetPath + "/annotations/labelmap.pbtxt";

    QFile::copy(labelmapPath, newLabelmapPath);

    newDataset["images"] = newImagesPath;
    newDataset["labels"] = newLabelsPath;
    newDataset["labelmap"] = newLabelmapPath;

    jsonDatasets[name] = newDataset;

    tools::writeJson(appConfigPath + "/config/datasets.json", jsonDatasets);

    qInfo() << "\033[32m[INFO]: Successfully created dataset!\033[0m";
}

void dataset::list()
{
    const QJsonObject& jsonDatasets = tools::getJsonObject(QDir::homePath() + "/." + QCoreApplication::applicationName() + "/config/datasets.json");

    qInfo().noquote() << tools::list(jsonDatasets).toUtf8();
}
