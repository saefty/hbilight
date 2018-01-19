/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef FORMSINGLELIGHT_H
#define FORMSINGLELIGHT_H

#include "light.h"

#include <QWidget>
#include <QModelIndex>
#include <memory>

/**
 * Handels the form for an Light object which also can be a Group
 */
namespace Ui {
class FormSingleLight;
}

class FormSingleLight : public QWidget
{
    Q_OBJECT

public:
    explicit FormSingleLight(QWidget *parent = 0);
    ~FormSingleLight();

    /**
     * @brief setLight sets the light object of the current form
     * @param l the light to set.
     * @param index the index where the light object came from.
     */
    void setLight(Light l, QModelIndex index);

    /**
     * @brief refreshUI refrehes the UI according to the light object.
     */
    void refreshUI();
signals:

    /**
     * @brief changed is triggered when the form was changed and the emitTimer triggers an update
     * @param l the changed light.
     * @param index the changed index.
     */
    void changed(Light l, const QModelIndex& index);

    /**
     * @brief addAsAmbi is triggered when the light should be added t o the ambilights
     */
    void addAsAmbi(bool arg, const QModelIndex& index);
private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_briSlider_valueChanged(int value);

    void on_hueDial_valueChanged(int value);

    void on_satDial_valueChanged(int value);

    void on_onOffButton_toggled(bool checked);

    void on_checkBox_toggled(bool checked);

private:
    static constexpr const double TIMER = 400;
    Ui::FormSingleLight *ui;
    QTimer *emitTimer_;
    Light l_;
    QModelIndex index_;
    bool dirty_;
    void change();
};

#endif // FORMSINGLELIGHT_H
