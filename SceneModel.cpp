#include "SceneModel.h"

#include <QStringList>
#include <QTreeView>

SceneModel::SceneModel(Scene *root, QObject *parent) : QAbstractItemModel(parent)
{
    rootItem = root;
}

SceneModel::~SceneModel()
{
    delete rootItem;
}

int SceneModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<Scene*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant SceneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    Scene *item = static_cast<Scene*>(index.internalPointer());

    return QVariant::fromValue(item->data(index.column()));
}

Qt::ItemFlags SceneModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant SceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(section == Scene::ID)
            return QVariant(QString("ID"));
        if(section == Scene::Name)
            return QVariant(QString("Nom"));
        if(section == Scene::InText)
            return QVariant(QString("Texte"));
    }

    return QVariant();
}

QModelIndex SceneModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Scene *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Scene*>(parent.internalPointer());

//    if(!parentItem->isAlias())
//    {
        Scene *childItem = parentItem->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
//    }
    return QModelIndex();
}

QModelIndex SceneModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Scene *childItem = static_cast<Scene*>(index.internalPointer());
    Scene *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int SceneModel::rowCount(const QModelIndex &parent) const
{
    Scene *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Scene*>(parent.internalPointer());

    return parentItem->childCount();
}

void SceneModel::setupModelData(Scene *parent)
{
    rootItem = parent;
}
