#ifndef DATASET_H
#define DATASET_H

#include <QString>

namespace dataset
{
void createDataset
    (
    const QString& name,
    const QString& dataPath,
    const QString& labelsPath
    );
void deleteDataset
    (
    const QString& name,
    bool confirmationDialog = true
    );
void list
    (
    );
}

#endif // DATASET_H
