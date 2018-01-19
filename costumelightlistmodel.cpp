#include "costumelightlistmodel.h"
#include <QAbstractListModel>
#include <QColor>
#include <QIcon>
#include <QSize>

CostumeLightListModel::CostumeLightListModel(QObject *parent)
    : QAbstractListModel(parent),
      lights_()
{
}

int CostumeLightListModel::rowCount(const QModelIndex &parent) const
{
    return lights_.size();
}
QVariant CostumeLightListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(100, 40); // set row height
    if(lights_.size() > index.row() && index.row() >= 0){
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

std::weak_ptr<Light> CostumeLightListModel::lightAt(const QModelIndex &index)
{
    return lights_.at(index.row());
}

Light CostumeLightListModel::lightAt(const QModelIndex &index) const
{
    auto light = lights_.at(index.row()).lock();
    if(!light){
        Light l;
        l.setName("deleted");
        return l;
    }
    return *light;
}

void CostumeLightListModel::addLight(std::shared_ptr<Light> light){
    beginInsertRows(index(lights_.size()),0,0);
    lights_.push_back(light);
    endInsertRows();
}

void CostumeLightListModel::removeLight(const QModelIndex &index){
    beginRemoveRows(index,0,0);
    lights_.erase(lights_.begin()+index.row());
    endRemoveRows();
}


void CostumeLightListModel::resetList(const std::vector<std::weak_ptr<Light>>& lights){
    beginResetModel();
    lights_ = lights;
    endResetModel();
}
