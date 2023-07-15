#include "dataset.h"
#include "../utils/tools.h"

#include <iostream>
#include <cstdint>
#include <cstdlib> // for linux system variable
#include <exception>

#include <QString>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcessEnvironment>


class dataset::DatasetNameError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Dataset has the same name as an other one!";
    }
};

class dataset::SA_DATASET_ERROR : public std::exception {
public:
    const char* what() const noexcept override {
        return "Could not find SA_DATASET_PATH. Is it deleted? Please set it to a Path where your DATASET will be stored.";
    }
};

class dataset::LabelExtentionError : public std::exception {
public:
    const char* what() const noexcept override {
        QSettings settings("config.ini", QSettings::IniFormat);
        QStringList formats = settings.value("dataset/supported_labeling_formats").toStringList();
        return QString("Unsupported labeling format. Currently supported formats: %1").arg(formats.join(",")).toUtf8().constData();
    }
};

class dataset::ImageExtentionError : public std::exception {
public:
    const char* what() const noexcept override {
        QSettings settings("config.ini", QSettings::IniFormat);
        QStringList formats = settings.value("dataset/supported_img_formats").toStringList();
        return QString("Unsupported Image format. Currently supported formats: %1").arg(formats.join(",")).toUtf8().constData();
    }
};


void dataset::createDataset
    (
    const QString& name,
    const QString& imagesPath,
    const QString& labelmapPath,
    const QString& labelsPath
    )
{
    using namespace::std;

    QJsonObject jsonDatasets = tools::getJsonObject("./config/datasets.json");
    QJsonObject newDataset;

    if (jsonDatasets.contains(name))
    {
        throw dataset::DatasetNameError();
    }


    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString datasetPath = env.value("SA_DATASET_PATH");

    if (datasetPath.isEmpty())
    {
        dataset::SA_DATASET_ERROR error;

        QString username = qgetenv("USER");
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
        }

        qInfo() << "\033[36m[ERROR] <NON_CRITICAL>:"
                << error.what()
                << "defaulting to" << datasetPath
                << "\033[0m";
    }

        qInfo() << "\033[32m[INFO]: Your dataset will be stored in:\033[35m" << datasetPath << "\033[0m";

    const QString newImagesPath = datasetPath + "/images";
    const QString newLabelsPath = datasetPath + "/labels";

    QSettings settings("../../config/config.ini", QSettings::IniFormat);

    QStringList label_formats = settings.value("dataset/supported_labeling_formats").toStringList();

    if (tools::copyFilesWithExtention(labelsPath,newLabelsPath,label_formats) == 0)
    {
        throw dataset::LabelExtentionError();
    }

    QStringList img_formats = settings.value("dataset/supported_img_formats").toStringList();

    if (tools::copyFilesWithExtention(imagesPath,newImagesPath,img_formats) == 0)
    {
        throw dataset::ImageExtentionError();
    }

    const QString& newLabelmapPath = datasetPath + "/annotations/labelmap.pbtxt";

    QFile::copy(labelmapPath, newLabelmapPath);

    newDataset["images"] = newImagesPath;
    newDataset["labels"] = newLabelsPath;
    newDataset["labelmap"] = newLabelmapPath;

    jsonDatasets[name] = newDataset;

    tools::writeJson("/home/rdk/simpleClai-test/datasets.json", jsonDatasets);
}

void dataset::list()
{
    const QJsonObject& jsonDatasets = tools::getJsonObject("./config/datasets.json");

    qInfo() << tools::list(jsonDatasets);
}
