#ifndef DATASET_H
#define DATASET_H

#include <QString>

namespace dataset
{
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
