/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef HUESTATE_H
#define HUESTATE_H
#include "group.h"
#include "light.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <memory>
#include <vector>
#include <tuple>

/**
 * @brief The HueState class is the only source where data is stored and influencing objects lifecylce.
 */
class HueState : public QObject
{
    Q_OBJECT
public:
    HueState();
    QNetworkAccessManager *nam_;
    std::vector<std::shared_ptr<Light>> lights_; // Hue lights
    std::vector<std::shared_ptr<Light>> hueGroups_; // Groups according to hue Bridge
    std::vector<std::shared_ptr<Group>> myGroups_; // custom groups
    std::vector<std::weak_ptr<Light>> ambiLights_; // Contains pointers to objects of lights_

    /**
     * @brief setAmbiState sets the light state of
     * @param lightState light objcect containing a specific light state
     */
    void setAmbiState(const Light &lightState);

    /**
     * @brief updateGroupState updates the group state (hue bridge)
     */
    void updateGroupState(int index, const Light &newLight);

    /**
     * @brief addAsAmbilight adds a reference to the lights.
     * @param ambilight
     */
    void addAsAmbilight(std::shared_ptr<Light> ambilight);
    /**
     * @brief removeFromAmbilight removes an item from the ambilights.
     * @param row index of the item
     */
    void removeFromAmbilight(int row);
    /**
     * @brief updateMyGroupState updates the state of groups (custom groups)
     * @param index index to update
     * @param newLight containting the new state.
     */
    void updateMyGroupState(int index, const Light &newLight);
signals:
    /**
     * @brief startFetchingLights triggerd when light fetching is started.
     */
    void startFetchingLights();

    /**
     * @brief startFetchingGroups triggered when group fetching is started.
     */
    void startFetchingGroups();

    /**
     * @brief fetchedGroups triggered when group fetching is done.
     */
    void fetchedGroups();

    /**
     * @brief fetchedLights triggered when light fetching is done.
     */
    void fetchedLights();
    /**
     * @brief setLight triggered when an light is updated.
     * @param row the row where the update happend
     */
    void setLight(int row);
public slots:
    /**
     * @brief fetchLights starts light fetching.
     * results are written directly to the lights_ vector.
     */
    void fetchLights();

    /**
     * @brief fetchGroups starts group fetching.
     * results are written directly to the hueGroups_ vector.
     */
    void fetchGroups();

    /**
     * @brief updateLightState triggers light state update.
     * @param index index to update
     * @param newLight new light
     */
    void updateLightState(int index, const Light &newLight);
private:
    void fetchLights(const QString &path);
    void parseLight(QNetworkReply *reply);
    void parseHueGroup(QNetworkReply *reply);
    void perfomBridgeUpdateLightName(const Light &newLight, QString path);
    void performBridgeUpdateLightState(const Light &newLight, QString path, QString statePos);
    std::vector<std::shared_ptr<Light> > parse(QNetworkReply *reply, QString statePos, bool group = false);
    Light qVariantMapToLight(QString id, QString statePos, const QVariantMap &variantMap, bool isGroup);
};

#endif // HUESTATE_H
