/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef MYGROUPSFORM_H
#define MYGROUPSFORM_H

#include "costumelightlistmodel.h"
#include "mygrouplistmodel.h"

#include <QWidget>

namespace Ui {
class MyGroupsForm;
}
/**
 * @brief The MyGroupsForm class handels updating the grouplistmodel connected with the form
 */
class MyGroupsForm : public QWidget
{
    Q_OBJECT

public:
    explicit MyGroupsForm(QWidget *parent = 0);
    ~MyGroupsForm();


    bool allready_contained(std::shared_ptr<Light> l);
private slots:
    void on_addGroup_clicked();

    void on_removeGroup_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_pushToMy_clicked();

    void on_removeFromMy_clicked();

private:
    Ui::MyGroupsForm *ui;
    MyGroupListModel *myGroupModel_;
    std::weak_ptr<Group> group_;
    QModelIndex index_;
    CostumeLightListModel *llMY_;
    LightListModel *llAll_;
    void checkForEmptyList();
    void showForm();
    void removeLight();
    void addLight();
};

#endif // MYGROUPSFORM_H
