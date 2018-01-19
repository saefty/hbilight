#include "settings.h"
#include "ui_settings.h"
#include <memory>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}


Settings::~Settings()
{
    delete ui;
}


void Settings::setSetting(std::shared_ptr<Setting> setting){
    setting_ = setting;
    ui->brightnessSlider->setValue(setting->ambiBrightness());
    ui->satFacSlider->setValue(setting->ambiSatFactor());
    ui->opacitySlider->setValue(setting->opacity());
    ui->transistionSlider->setValue(setting->transistion());
}


void Settings::on_transistionSlider_valueChanged(int value)
{
    setting_->setTransistion(value);
}

void Settings::on_opacitySlider_valueChanged(int value)
{
    setting_->setOpacity(value);
    opacityChanged();
}

void Settings::on_brightnessSlider_valueChanged(int value)
{
    setting_->setAmbiBrightness(value);
}

void Settings::on_satFacSlider_valueChanged(int value)
{
    setting_->setAmbiSatFactor(value);

}
