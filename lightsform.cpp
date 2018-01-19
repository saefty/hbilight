#include "lightlistmodel.h"
#include "lightsform.h"
#include "ui_lightsform.h"
#include "mainwindow.h"
#include "grouplistmodel.h"
#include <QDialog>
#include <iostream>
#include <QListView>
#include <QWindow>
#include <QColorDialog>
#include <QScreen>
#include <QRgb>
#include <memory>
#include <stdlib.h>

LightsForm::LightsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightsForm)
{
    ui->setupUi(this);
    formSingleLight_ = static_cast<FormSingleLight*> (ui->form);
    ui->form->hide();
}

void LightsForm::setModel(LightListModel* model){
    auto *lightsListModel = model;
    lightListModel_ = lightsListModel;
    connect(
        formSingleLight_,
        &FormSingleLight::changed,
        [=](Light l, QModelIndex index){
            lightListModel_->setLight(index, l);
        }
    );
    connect(MainWindow::HUESTATE.get(), &HueState::setLight, [=](){
        ui->form->refreshUI();
    });
    connect(formSingleLight_, &FormSingleLight::addAsAmbi, [=](bool arg, QModelIndex index){
        if(arg) lightListModel_->addAsAmbilight(index);
        else lightListModel_->removeFromAmbilight(index);
    });
    ui->listView->setModel(lightsListModel);
}

LightsForm::~LightsForm()
{
    delete ui;
}

QColor LightsForm::avgScreenColor(){
    QScreen *screen = QGuiApplication::primaryScreen();
    QImage img = screen->grabWindow(0).toImage();
    double r = 0;
    double g = 0;
    double b = 0;
    int ratio = 0;
    for(auto i = 0; i < img.width(); i+=4){
        for(auto j = 0; j < img.height(); j+=4){
            QColor color(img.pixel(i, j));
            ratio++;
            r += color.red();
            g += color.green();
            b += color.blue();
        }
    }
    r /= ratio;
    g /= ratio;
    b /= ratio;
    return QColor::fromRgb(r, g, b);
}

void LightsForm::ambilight() {
    QColor color = avgScreenColor();
    Light l;
    l.setHue(std::max(color.hsvHue(), 0));
    l.setSat(std::min(color.toHsv().saturation()*MainWindow::setting->ambiSatFactor()/100.0, 255.0));
    l.setBri(MainWindow::setting->ambiBrightness()/100.0*255);
    l.setOn(true);
    lightListModel_->setAmbiState(l);
}

void LightsForm::showForm(Light curLight_, QModelIndex index) {
    formSingleLight_->setLight(curLight_, index);
    ui->form->show();
}

void LightsForm::on_listView_clicked(const QModelIndex &index)
{
   std::weak_ptr<Light> l = lightListModel_->lightAt(index);
   QModelIndex curIndex = index;
   auto light = l.lock();
   showForm(*light, curIndex);
}
