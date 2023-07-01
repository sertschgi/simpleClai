#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace dataset
{
class ImageExtentionError;
class LabelExtentionError;
class DatasetNameError;
void createDataset
    (
    const QString& name,
    const QString& imagesPath,
    const QString& lables,
    const QString& labelsPath
    );
}

#endif // DATASET_H
