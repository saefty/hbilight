/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef LIGHTSFORM_H
#define LIGHTSFORM_H

#include "formsinglelight.h"
#include "light.h"
#include "lightlistmodel.h"
#include <memory>
#include <QWidget>

namespace Ui {
class LightsForm;
}
/**
 * @brief The LightsForm class handels updating lights
 */
class LightsForm : public QWidget
{
    Q_OBJECT

public:
    explicit LightsForm(QWidget *parent = 0);
    ~LightsForm();
    /**
     * @brief setModel sets the model to use on the listView
     * @param model the LightListModel which should be used.
     */
    void setModel(LightListModel *model);
public slots:
    /**
     * @brief ambilight triggers ambilight calculation and update
     */
    void ambilight();
private slots:
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::LightsForm *ui;
    LightListModel *lightListModel_;
    FormSingleLight* formSingleLight_;
    void showForm(Light curLight_, QModelIndex index);
    QColor avgScreenColor();

};

#endif // LIGHTSFORM_H
