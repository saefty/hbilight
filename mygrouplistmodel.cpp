#include "mygrouplistmodel.h"
#include <QDebug>
#include "mainwindow.h"
MyGroupListModel::MyGroupListModel(QObject *parent)
    : QAbstractListModel(parent),
      groups_()
{
    connect(MainWindow::HUESTATE.get(), &HueState::startFetchingLights, [this](){ beginResetModel(); });
    connect(MainWindow::HUESTATE.get(), &HueState::fetchedLights, [this](){ endResetModel(); });
    connect(MainWindow::HUESTATE.get(), &HueState::setLight,
    [this](int row){
        emit dataChanged(index(row), index(row));
    });
}

int MyGroupListModel::rowCount(const QModelIndex &parent) const
{
    return MainWindow::HUESTATE->myGroups_.size();
}

QVariant MyGroupListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(100, 40);
    if(MainWindow::HUESTATE->myGroups_.size() > index.row() && index.row() >= 0) {
        Group group = getGroup(index);
        if(role == Qt::DisplayRole){
            QString name = group.name();
            return name;
        }
    }

    return QVariant();
}

void MyGroupListModel::addGroup(Group g){
    beginInsertRows(index(MainWindow::HUESTATE->myGroups_.size()), 0, 0);
    MainWindow::HUESTATE->myGroups_.push_back(std::make_shared<Group>(g));
    endInsertRows();
}

void MyGroupListModel::removeGroup(QModelIndex index){
    if(index.row() > MainWindow::HUESTATE->myGroups_.size() && index.row() > 0) return;
    beginRemoveRows(index,0,0);
    MainWindow::HUESTATE->myGroups_.erase(MainWindow::HUESTATE->myGroups_.begin()+index.row());
    endRemoveRows();
}

std::weak_ptr<Group> MyGroupListModel::getGroup(QModelIndex index)
{
    return MainWindow::HUESTATE->myGroups_.at(index.row());
}

Group MyGroupListModel::getGroup(QModelIndex index) const
{
    return *MainWindow::HUESTATE->myGroups_.at(index.row());
}

void MyGroupListModel::setGroup(const QModelIndex &index, Light newLight)
{
    MainWindow::HUESTATE->updateMyGroupState(index.row(), newLight);
    emit dataChanged(index, index);
}
