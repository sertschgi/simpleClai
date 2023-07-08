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


class dataset::DatasetNameError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Dataset has the same name as an other one!";
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

    QJsonObject jsonDatasets = tools::getJsonObject("../../config/datasets");
    QJsonObject newDataset;

    if (!jsonDatasets.contains(name))
    {
        throw dataset::DatasetNameError();
    }


    QString datasetPath = getenv("SA_DATASET_PATH");

    if (datasetPath.isEmpty())
    {
        qCritical() << "Could not find SA_DATASET_PATH. Is it deleted? Please set it to a Path where your DATASET will be stored.";
    }

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

    tools::writeJson("../../config/datasets", jsonDatasets);
}

void dataset::list()
{
    const QJsonObject& jsonDatasets = tools::getJsonObject("../../config/datasets");

    qInfo() << tools::list(jsonDatasets);
}
