#include "formsinglelight.h"
#include "ui_formsinglelight.h"
#include <QDebug>
#include <QTimer>
#include "group.h"

FormSingleLight::FormSingleLight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSingleLight),
    dirty_(false)
{
    emitTimer_ = new QTimer(this);
    connect(emitTimer_, &QTimer::timeout, [this]{
        if(dirty_){
            changed(l_, index_);
            dirty_ = false;
        }
    });
    emitTimer_->start(TIMER);
    ui->setupUi(this);
}

void FormSingleLight::setLight(Light l, QModelIndex index)
{
    l_ = l;
    index_ = index;
    refreshUI();
}

void FormSingleLight::refreshUI(){
    ui->lineEdit->setText(l_.name());
    ui->briSlider->setValue(l_.bri()/255.0*100);
    ui->hueDial->setValue(l_.hue()/255.0*100);
    ui->satDial->setValue(l_.sat()/255.0*100);
    ui->onOffButton->setChecked(l_.on());
    if(l_.isGroup()){
        ui->checkBox->hide();
        ui->groups->hide();
    } else {
        ui->checkBox->show();
        ui->checkBox->setChecked(l_.isAmbi());
        auto group = l_.parentGroup().lock();
        if(group){
            ui->groups->show();
            ui->groupsLabel->setText(group->name());
        }
        else ui->groups->hide();
    }
}


FormSingleLight::~FormSingleLight()
{
    delete ui;
}

void FormSingleLight::on_lineEdit_textChanged(const QString &arg1)
{
    if(l_.name() != arg1){
        l_.setName(arg1);
        change();
    }
}

void FormSingleLight::change()
{
    dirty_ = true;
}

void FormSingleLight::on_briSlider_valueChanged(int value)
{
    if(l_.bri() != value){
        l_.setBri(value*2.55);
        change();
    }
}

void FormSingleLight::on_hueDial_valueChanged(int value)
{
    if(l_.hue() != value){
        l_.setHue(value*2.55);
        change();
    }
}

void FormSingleLight::on_satDial_valueChanged(int value)
{
    if(l_.sat() != value){
        l_.setSat(value*2.55);
        change();
    }
}

void FormSingleLight::on_onOffButton_toggled(bool checked)
{
    if(l_.on() != checked){
        l_.setOn(checked);
        change();
    }
}

void FormSingleLight::on_checkBox_toggled(bool checked)
{
    if(l_.isAmbi() != checked){
        addAsAmbi(checked, index_);
    }
}
