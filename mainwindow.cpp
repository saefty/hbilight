#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QPushButton>
#include <iostream>
#include <QTableView>
#include <QTimer>
#include <QScreen>
#include <QDesktopWidget>
#include <QBitmap>

#include "api.h"
#include "grouplistmodel.h"
#include "setting.h"
#include "settings.h"
#include <QDialog>
#include <memory>

std::shared_ptr<Setting> MainWindow::setting = std::make_shared<Setting>();
std::unique_ptr<HueState> MainWindow::HUESTATE = std::make_unique<HueState>();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settingsDialog_(nullptr)
{
    ui->setupUi(this);

    auto connectButton = ui->connectButton;

    auto lightTab = static_cast<LightsForm*>(ui->lightsTab);
    lightTab->setModel(new LightListModel());
    auto groupTab = static_cast<LightsForm*>(ui->groupTab);
    groupTab->setModel(new GroupListModel());

    connect(connectButton, &QPushButton::pressed, this, &MainWindow::setConnection);

    timer_ = new QTimer(this);
    timerAmbilight_ = new QTimer(this);
    connect(timerAmbilight_, &QTimer::timeout, lightTab, &LightsForm::ambilight);
    connect(timer_, &QTimer::timeout, [=](){
        MainWindow::HUESTATE->fetchLights();
        MainWindow::HUESTATE->fetchGroups();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConnection(){
    auto tmp = API::get().lock();
    if(tmp.get() != nullptr && (tmp->adress_ == ui->adressLineEdit->text() && tmp->api_key_ == ui->apiLineEdit->text())) {
        return;
    }
    std::weak_ptr<API> apiPtr = API::api(ui->adressLineEdit->text(), ui->apiLineEdit->text());
    auto api = apiPtr.lock();
    if  (api && api->isAvailable()){
        ui->connectButton->setText("Connected");
        HUESTATE->fetchGroups();
        HUESTATE->fetchLights();
        connected();
    }

}


void MainWindow::on_actionRefresh_triggered()
{
    connected();
}

void MainWindow::on_actionAutofetch_toggled(bool checked)
{
    if(checked) timer_->start(800); //time specified in ms
    else timer_->stop();
}

void MainWindow::on_actionAmbilight_toggled(bool checked)
{
    if(checked) timerAmbilight_->start(300); //time specified in ms
    else timerAmbilight_->stop();
}

void MainWindow::on_actionSettings_triggered()
{
    settingsDialog_ = new QDialog(this);
    Settings *s = new Settings(settingsDialog_);
    s->setSetting(setting);
    connect(s, &Settings::opacityChanged, [=]{ this->setWindowOpacity(setting->opacity()/100.0); });
    settingsDialog_->setLayout(s->layout());
    settingsDialog_->setFixedSize(650, 300);
    settingsDialog_->show();
}
