/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef SETTINGS_H
#define SETTINGS_H

#include "setting.h"

#include <QWidget>
#include <memory>
namespace Ui {
class Settings;
}
/**
 * @brief The Settings class is the UI representation of the setting.
 */
class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void setSetting(std::shared_ptr<Setting> setting);
signals:
    void opacityChanged();
private slots:
    void on_transistionSlider_valueChanged(int value);

    void on_opacitySlider_valueChanged(int value);

    void on_brightnessSlider_valueChanged(int value);

    void on_satFacSlider_valueChanged(int value);

private:
    Ui::Settings *ui;
    std::shared_ptr<Setting> setting_;
};

#endif // SETTINGS_H
