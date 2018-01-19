/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef MYGROUPLISTMODEL_H
#define MYGROUPLISTMODEL_H

#include "group.h"

#include <QAbstractListModel>
#include <memory>

/**
 * @brief The MyGroupListModel class handels updates for custom groups and the UI.
 */
class MyGroupListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MyGroupListModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief addGroup adds a new group to the list
     * @param g the new group
     */
    void addGroup(Group g);

    /**
     * @brief removeGroup removes a group by its index.
     * @param index
     */
    void removeGroup(QModelIndex index);

    /**
     * @brief getGroup gets the group by its index
     * @return weak ptr to the group
     */
    std::weak_ptr<Group> getGroup(QModelIndex);
    /**
     * @brief getGroup gets the group by its index
     * @return copy of the Group
     */
    Group getGroup(QModelIndex index) const;
    /**
     * @brief setGroup sets the lightstate of a group
     * @param index index of the group
     * @param newLight new light state
     */
    void setGroup(const QModelIndex &index, Light newLight);
private:
    std::vector<std::weak_ptr<Group>> groups_;
};

#endif // MYGROUPLISTMODEL_H
