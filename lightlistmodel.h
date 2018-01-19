/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef LIGHTLISTMODEL_H
#define LIGHTLISTMODEL_H

#include "light.h"
#include <vector>
#include <memory>
#include <QAbstractListModel>
#include <QNetworkReply>

class LightListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LightListModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual std::weak_ptr<Light> lightAt(const QModelIndex &index);
    virtual Light lightAt(const QModelIndex &index) const;
    virtual void setLight(const QModelIndex &index, Light newLight);
    void addAsAmbilight(const QModelIndex &index);
    void removeFromAmbilight(const QModelIndex &index);
    void setAmbiState(const Light &lightState);
    void emitDataChanged(int row);
public slots:

signals:
    void fetched();

protected:
    virtual void setFetchConnection();
};

#endif // LIGHTLISTMODEL_H
