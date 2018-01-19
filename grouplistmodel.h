/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef GROUPLISTMODEL_H
#define GROUPLISTMODEL_H

#include "lightlistmodel.h"

/**
 * @brief The GroupListModel class represents groups (hue bridge) on the UI
 */
class GroupListModel : public LightListModel
{
public:
    GroupListModel();
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    std::weak_ptr<Light> lightAt(const QModelIndex &index) override;
    Light lightAt(const QModelIndex &index) const override;
    void setLight(const QModelIndex &index, Light newLight);
protected:
    void setFetchConnection() override;
};

#endif // GROUPLISTMODEL_H
