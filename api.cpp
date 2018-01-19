#include "api.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QString>
#include <QEventLoop>
#include <memory>
#include <iostream>
#include "mainwindow.h"


using namespace std;


shared_ptr<API> API::api_ = std::shared_ptr<API>();

std::ostream& operator<< (ostream& os, const std::weak_ptr<API>& m) {
    auto access = m.lock();
    if(access){
        return os << "adr: " << access->adress_.toStdString() << " key: " << access->api_key_.toStdString() << " available: " << access->isAvailable();
    }
    return os;
}

API::API(QString adress, QString api_key)
    : adress_(adress), api_key_(api_key)
{

}

QString API::url()
{
    return QString(adress_+ "/api/" + api_key_);
}

bool API::isAvailable() const
{
    QEventLoop loop;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    bool success = false;
    MainWindow::connect(
        manager,
        &QNetworkAccessManager::finished,
        [&success, &loop](QNetworkReply* reply) mutable {
            success = !reply->readAll().trimmed().isEmpty();
            loop.quit();
        }
    );
    manager->get(QNetworkRequest(QUrl(adress_+ "/api/" + api_key_)));
    loop.exec();
    manager->deleteLater();
    return success;
}

weak_ptr<API> API::get() {
    if(API::api_) return weak_ptr<API> (API::api_);
    return weak_ptr<API>();
}

weak_ptr<API> API::api(QString adress, QString api_key) {
    API::api_ = make_shared<API>(API(adress, api_key));
    if(!API::api_->isAvailable()){
        API::api_ = shared_ptr<API> ();
    }
    return weak_ptr<API> (API::api_);
}
