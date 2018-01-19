/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef LIGHT_H
#define LIGHT_H

#include <QString>
#include <string>
#include <memory>
class Group;
/**
 * @brief The Light class is a container for the a light.
 */
class Light
{
public:
    Light(int id = -1, QString name = "", bool on = false, double bri = -1, double hue_ = -1, double sat = -1, bool isAmbi = false, bool isGroup = false);
    virtual bool on() const;
    virtual void setOn(bool on);

    virtual double bri() const;
    virtual void setBri(double bri);

    virtual double sat() const;
    virtual void setSat(double sat);

    QString name() const;
    void setName(QString name);

    int id() const;
    void setId(int id);

    virtual double hue() const;
    virtual void setHue(double hue);

    virtual double pHue() const;
    virtual bool operator ==(const Light &l);

    virtual bool isAmbi() const;
    virtual void setIsAmbi(bool isAmbi);

    // appends state changes
    bool appendStateChanges(const Light &other);

    // append name changes
    bool appendNameChange(const Light &other);
    bool isGroup() const;

    std::weak_ptr<Group> parentGroup() const;
    void setParentGroup(const std::weak_ptr<Group> &parentGroup);

protected:
    int id_;
    QString name_;
    bool on_;
    double bri_;
    double hue_;
    double sat_;
    bool isAmbi_;
    bool isGroup_;
    std::weak_ptr<Group> parentGroup_;
};

#endif // LIGHT_H
