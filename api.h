/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef API_H
#define API_H

#include <QString>
#include <memory>
#include <QObject>

/**
 * @brief The API class is a contianer for the API url and API KEY
 */
class API
{
public:
    /**
     * @brief adress_ contains the url of the hue API.
     *
     * Example: http://localhost:80
     * Atention no backslash at the end!
     *
     */
    QString adress_;
    /**
     * @brief api_key_ contains the API key to access the hue Bridge.
     *
     * This will not be detected by the App itself and must be set!
     */
    QString api_key_;
    /**
     * @brief url
     * @return concatenation of adress and api key to an valid url ending with /api.
     */
    QString url();
    /**
     * @brief isAvailable check if the url retruns anything on a simple GET Request.
     * @return true if the resources retruned something which is not an empty String
     *
     * This sends a synchronous Request to the url and may take some time to complete.
     */
    bool isAvailable() const;
    /**
     * @brief get allows access to the current api object.
     * @return weak ptr to the current api object. If there is none it will be a nullptr
     */
    static std::weak_ptr<API> get();
    /**
     * @brief api allows to set the current api object.
     * @param adress url of the API.
     * @param api_key API key to hue bridge.
     * @return returns the weak ptr to the current object simmilar to get().
     */
    static std::weak_ptr<API> api(QString adress, QString api_key);

    friend std::ostream& operator<< (std::ostream& stream, const std::weak_ptr<API>& m);

private:
    API(QString adress, QString api_key);
    static std::shared_ptr<API> api_;

};

#endif // API_H
