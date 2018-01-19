#include "api.h"
#include "huestate.h"
#include "mainwindow.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>
#include <memory>
#include <algorithm>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

HueState::HueState()
    : QObject(),
      lights_(),
      hueGroups_(),
      myGroups_(),
      ambiLights_()
{
    nam_ = new QNetworkAccessManager(this);
}

void HueState::fetchLights(){
    startFetchingLights();
    fetchLights("lights");
    myGroups_.clear();
}

void HueState::fetchGroups(){
    startFetchingGroups();
    fetchLights("groups");
}

void HueState::fetchLights(const QString& path) {
    std::shared_ptr<API> api = API::get().lock();
    if(!api) return;
    QNetworkRequest *request = new QNetworkRequest( QUrl(api->url().append("/").append(path)));
    QNetworkReply *reply = nam_->get(*request);
    connect(
        reply,
        &QNetworkReply::finished,
        [this, reply, path]{
            if(path.contains("groups")){
                parseHueGroup(reply);
            } else {
                parseLight(reply);
            }
        }
    );
}

void HueState::updateLightState(int index, const Light& newLight){
    std::shared_ptr<Light> ptr = lights_.at(index);
    if(ptr->appendNameChange(newLight)) perfomBridgeUpdateLightName(newLight, "lights");
    if(ptr->appendStateChanges(newLight)) performBridgeUpdateLightState(newLight, "lights", "state");
    setLight(index);
}

void HueState::updateMyGroupState(int index, const Light& newLight){
    std::shared_ptr<Group> ptr = myGroups_.at(index);
    ptr->appendNameChange(newLight);
    ptr->appendStateChanges(newLight);
    std::vector<std::weak_ptr<Light>> lights = ptr->lights();
    for(auto it = lights.begin(); it != lights.end(); it++){
        auto itL = (*it).lock();
        if(!itL) return;
        auto itFind = find_if(lights_.begin(), lights_.end(), [itL](std::shared_ptr<Light> cur) { return cur->id() == itL->id(); });
        auto index = std::distance(lights_.begin(), itFind);
        setLight(index);
        performBridgeUpdateLightState(*itL,"lights", "state");
    }
}

void HueState::updateGroupState(int index, const Light& newLight){
    std::shared_ptr<Light> ptr = hueGroups_.at(index);
    if(ptr->appendNameChange(newLight)) perfomBridgeUpdateLightName(newLight, "groups");
    if(ptr->appendStateChanges(newLight)) performBridgeUpdateLightState(newLight, "groups", "action");
}

void HueState::perfomBridgeUpdateLightName(const Light& newLight, QString path){
    std::shared_ptr<API> api = API::get().lock();
    if(!api) return;

    QVariantMap jsonMapData;

    jsonMapData["name"] = newLight.name();
    QJsonDocument jsonData = QJsonDocument::fromVariant(jsonMapData);


    QNetworkRequest *request = new QNetworkRequest(
        QUrl(
            api->url()
            .append("/")
            .append(path)
            .append("/%1")
            .arg((int) newLight.id())
        )
    );
    request->setHeader(QNetworkRequest::ContentTypeHeader, QString("text/raw"));
    QNetworkReply *reply = nam_->put(*request, jsonData.toJson());
    connect(
        reply,
        &QNetworkReply::finished,
        [reply](){
            reply->deleteLater();
        }
    );
}

void HueState::performBridgeUpdateLightState(const Light& newLight, QString path, QString statePos){
    std::shared_ptr<API> api = API::get().lock();
    if(!api) return;

    QVariantMap jsonMapData;
    jsonMapData["on"] = newLight.on();
    jsonMapData["bri"] = (int) newLight.bri();
    jsonMapData["sat"] = (int) newLight.sat();
    jsonMapData["hue"] = (int) newLight.pHue();
    jsonMapData["transitiontime"] = MainWindow::setting->transistion();
    QJsonDocument jsonData = QJsonDocument::fromVariant(jsonMapData);

    QNetworkRequest *request = new QNetworkRequest(
        QUrl(
            api->url()
            .append("/")
            .append(path)
            .append("/%1/")
            .append(statePos)
            .arg((int) newLight.id())
        )
    );
    request->setHeader(QNetworkRequest::ContentTypeHeader, QString("text/raw"));
    QNetworkReply *reply = nam_->put(*request, jsonData.toJson());

    connect(
        reply,
        &QNetworkReply::finished,
        [reply]{
            reply->deleteLater();
        }
    );
}

void HueState::parseLight(QNetworkReply *reply) {
    lights_ = parse(reply, "state");
    fetchedLights();
    reply->deleteLater();
}

void HueState::parseHueGroup(QNetworkReply *reply) {
    hueGroups_ = parse(reply, "action", true);
    fetchedGroups();
    reply->deleteLater();
}

Light HueState::qVariantMapToLight(QString id, QString statePos, const QVariantMap& variantMap, bool isGroup) {
    auto vals = variantMap[id].toMap();
    auto state = variantMap[id].toMap()[statePos].toMap();
    QString name = vals["name"].toString();
    bool on = state["on"].toBool();
    double bri = state["bri"].toDouble();
    auto hue = state["hue"].toDouble();
    int sat = state["sat"].toInt();
    return Light(id.toInt(), name, on, bri, hue, sat, false, isGroup);
}

std::vector<std::shared_ptr<Light>> HueState::parse(QNetworkReply *reply, QString statePos, bool group){
    std::vector<std::shared_ptr<Light>> results;
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();
    auto variantMap = obj.toVariantMap();
    auto keys = variantMap.keys();
    for(auto i = keys.begin(); i != keys.end(); i++) {
        results.push_back(std::make_shared<Light>(qVariantMapToLight(*i, statePos, variantMap, group)));
    }
    return results;
}

void HueState::addAsAmbilight(std::shared_ptr<Light> ambilight)
{
    ambilight->setIsAmbi(true);
    ambiLights_.push_back(std::weak_ptr<Light>(ambilight));
}

void HueState::removeFromAmbilight(int row)
{
    std::shared_ptr<Light> l = lights_.at(row);
    l->setIsAmbi(false);
    auto to_be_erased = remove_if(ambiLights_.begin(), ambiLights_.end(),
        [=](std::weak_ptr<Light> curW){
            std::shared_ptr<Light> cur = curW.lock();
            if(!cur) true;
            return cur->id() == l->id();
        }
    );
    ambiLights_.erase(to_be_erased, ambiLights_.end());
}

void HueState::setAmbiState(const Light& lightState)
{
    for(auto i = ambiLights_.begin(); i!= ambiLights_.end(); i++) {
        std::shared_ptr<Light> l = (*i).lock();
        if(!l) continue;
        l->appendStateChanges(lightState);
        performBridgeUpdateLightState(*l, "lights", "state");
    }
}
