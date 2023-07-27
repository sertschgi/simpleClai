#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace dataset
{
class DatasetError : public std::exception
{
public:
    virtual const char* what() const noexcept = 0;
};
class SA_DATASET_ERROR : public DatasetError
{
public:
    const char* what() const noexcept override;
};
class ImageExtentionError : public DatasetError
{
public:
    const char* what() const noexcept override;
};
class LabelExtentionError : public DatasetError
{
public:
    const char* what() const noexcept override;
};
class DatasetNameError : public DatasetError
{
public:
    const char* what() const noexcept override;
};
void createDataset
    (
    const QString& name,
    const QString& labelmapPath,
    const QString& imagesPath,
    const QString& labelsPath
    );
void list
    (
    );
}

#endif // DATASET_H
