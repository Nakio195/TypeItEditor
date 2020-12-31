#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QAbstractItemModel>
#include "../TypeIt/TypeIt/Scene.h"

class SceneModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SceneModel(Scene *root, QObject *parent);
    ~SceneModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void setupModelData(Scene *parent);

    Scene *rootItem;
};

#endif // SCENEMODEL_H
