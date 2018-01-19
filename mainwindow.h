#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#include "huestate.h"
#include "setting.h"
#include "settings.h"

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <memory>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static std::shared_ptr<Setting> setting;
    static std::unique_ptr<HueState> HUESTATE;
signals:
    void connected();

public slots:
    void setConnection();

private slots:
    void on_actionRefresh_triggered();

    void on_actionAutofetch_toggled(bool arg1);

    void on_actionAmbilight_toggled(bool arg1);

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    QString api_;
    QString ip_;
    QTimer *timer_;
    QTimer *timerAmbilight_;
    QDialog *settingsDialog_;
};

#endif // MAINWINDOW_H
