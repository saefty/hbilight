#include "lightlistmodel.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <qeventloop.h>
#include "api.h"
#include <iostream>
#include <vector>
#include "light.h"
#include <memory>
#include <algorithm>

#include "mainwindow.h"
#include <QCoreApplication>
#include <QVariantMap>
#include <tuple>
#include <QFileIconProvider>
using namespace std;

LightListModel::LightListModel(QObject *parent)
{
    connect(MainWindow::HUESTATE.get(), &HueState::setLight,
    [this](int row){
        emit dataChanged(index(row), index(row));
    });
    setFetchConnection();
}

void LightListModel::setFetchConnection(){
    connect(MainWindow::HUESTATE.get(), &HueState::startFetchingLights, [this](){ beginResetModel(); });
    connect(MainWindow::HUESTATE.get(), &HueState::fetchedLights, [this](){ endResetModel(); });
}

int LightListModel::rowCount(const QModelIndex &parent) const
{
    return MainWindow::HUESTATE->lights_.size();
}

QVariant LightListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(100, 40); // set row height
    if(MainWindow::HUESTATE->lights_.size() > index.row() && index.row() >= 0){
        Light l = lightAt(index);
        QColor color = QColor::fromHsv(l.hue(), l.sat(), l.bri()).toRgb();
        if(role == Qt::DisplayRole){
            QString name = l.name();
            return name;
        }
        else if(role == Qt::BackgroundRole){
          if(color.lightness() <= 20){
              color = QColor::fromRgb(100,100,100);
          }
          return QBrush(color);
        }
        else if(role == Qt::ForegroundRole){
            if(color.lightness() <= 20){
               return QColor(255,255,255);
            }
            else return QVariant();
        }
        else if(role == Qt::DecorationRole){
           if(l.on()) return QIcon(":/e27_on_waca.svg");
           else return QIcon(":/e27_off_waca.svg");
        }
    }

    return QVariant();
}



std::weak_ptr<Light> LightListModel::lightAt(const QModelIndex &index){
    return MainWindow::HUESTATE->lights_.at(index.row());
}

Light LightListModel::lightAt(const QModelIndex &index) const{
    return *MainWindow::HUESTATE->lights_.at(index.row());
}


void LightListModel::setLight(const QModelIndex &index, Light newLight)
{
    MainWindow::HUESTATE->updateLightState(index.row(), newLight);
    emit dataChanged(index, index);
}

void LightListModel::addAsAmbilight(const QModelIndex& index)
{

   std::shared_ptr<Light> l = MainWindow::HUESTATE->lights_.at(index.row());
   MainWindow::HUESTATE->addAsAmbilight(l);
   l->setIsAmbi(true);
}

void LightListModel::removeFromAmbilight(const QModelIndex& index)
{
    MainWindow::HUESTATE->removeFromAmbilight(index.row());
}

void LightListModel::setAmbiState(const Light& lightState)
{
    MainWindow::HUESTATE->setAmbiState(lightState);
}





