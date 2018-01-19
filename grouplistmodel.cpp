#include "api.h"
#include "grouplistmodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>
#include "mainwindow.h";

GroupListModel::GroupListModel()
{
    setFetchConnection();
}

void GroupListModel::setFetchConnection(){
    connect(MainWindow::HUESTATE.get(), &HueState::startFetchingGroups, [this](){ beginResetModel(); });
    connect(MainWindow::HUESTATE.get(), &HueState::fetchedGroups, [this](){ endResetModel(); });
}

int GroupListModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(MainWindow::HUESTATE->hueGroups_.size());
}

QVariant GroupListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(100, 40); // set row height
    if(MainWindow::HUESTATE->hueGroups_.size() > index.row() && index.row() >= 0){
        Light l = lightAt(index);
        if(role == Qt::DisplayRole){
            QString name = l.name();
            return name;
        }
        else if(role == Qt::DecorationRole){
           if(l.on()) return QIcon(":/e27_on_waca.svg");
           else return QIcon(":/e27_off_waca.svg");
        }
    }

    return QVariant();
}

std::weak_ptr<Light> GroupListModel::lightAt(const QModelIndex &index){
    return MainWindow::HUESTATE->hueGroups_.at(index.row());
}

Light GroupListModel::lightAt(const QModelIndex &index) const{
    return *MainWindow::HUESTATE->hueGroups_.at(index.row());
}

void GroupListModel::setLight(const QModelIndex &index, Light newLight)
{
    MainWindow::HUESTATE->updateGroupState(index.row(), newLight);
    emit dataChanged(index, index);
}
