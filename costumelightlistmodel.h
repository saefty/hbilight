/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef COSTUMELIGHTLISTMODEL_H
#define COSTUMELIGHTLISTMODEL_H

#include "lightlistmodel.h"
#include <QAbstractListModel>
#include <memory>
#include <vector>
#include "light.h"

/**
 * @brief Allows to add lights to an not persistent vector and handels displaying.
 */
class CostumeLightListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CostumeLightListModel(QObject *parent = nullptr);
    /* basic functions */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief lightAt allows to access a specific light object given by an index
     * @param index index of the item.
     * @return weak pointer to light object
     */
    virtual std::weak_ptr<Light> lightAt(const QModelIndex &index);

    /**
     * @brief lightAt allows to access the data of a Light object by copying it from heap.
     * @param index the index of the item.
     * @return copy of the object.
     */
    virtual Light lightAt(const QModelIndex &index) const;

    /**
     * @brief addLight adds the param to the vector.
     * @param light the light to add.
     */
    void addLight(std::shared_ptr<Light> light);

    /**
     * @brief removeLight removes the light by a given index
     * @param index index of the light in the vector
     */
    void removeLight(const QModelIndex &index);
    /**
     * @brief resetList resets the list by reseting the vecotr
     * @param lights new vector
     */
    void resetList(const std::vector<std::weak_ptr<Light> > &lights);
private:
    std::vector<std::weak_ptr<Light>> lights_;
};

#endif // COSTUMELIGHTLISTMODEL_H
