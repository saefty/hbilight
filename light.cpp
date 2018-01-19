#include "light.h"
#include <math.h>
#include <tuple>
#include <algorithm>
#include <QDebug>

Light::Light(int id, QString name, bool on, double bri, double hue, double sat, bool isAmbi, bool isGroup)
    : id_(id), name_(name), on_(on), bri_(bri), hue_(hue), sat_(sat), isAmbi_(isAmbi), isGroup_(isGroup)
{
}

bool Light::on() const
{
    return on_;
}

void Light::setOn(bool on)
{
    on_ = on;
}

double Light::bri() const
{
    return bri_;
}

void Light::setBri(double bri)
{
    bri_ = bri;
}


double Light::sat() const
{
    return sat_;
}

void Light::setSat(double sat)
{
    sat_ = sat;
}

QString Light::name() const
{
    return name_;
}

void Light::setName(QString name)
{
    name_ = name;
}

int Light::id() const
{
    return id_;
}

void Light::setId(int id)
{
    id_ = id;
}

double Light::hue() const
{
    return hue_/182.0;
}
double Light::pHue() const {
    return hue_;
}

void Light::setHue(double hue)
{
    hue_ = hue*182;
}

bool Light::operator==(const Light& l){
    return l.bri_ == bri_ && l.hue_ == hue_ && l.sat_ == sat_ && l.id_ == id_ && l.on_ == on_;
}

bool Light::isAmbi() const
{
    return isAmbi_;
}

void Light::setIsAmbi(bool isAmbi)
{
    isAmbi_ = isAmbi;
}

bool Light::appendStateChanges(const Light& other)
{
    bool dirty = false;
    if(isAmbi_ != other.isAmbi_) { setIsAmbi(other.isAmbi()); dirty = true; }
    if(hue_    != other.hue_)    { setHue(other.hue());   dirty = true; }
    if(sat_    != other.sat_)    { setSat(other.sat());    dirty = true; }
    if(bri_    != other.bri_)    { setBri(other.bri());    dirty = true; }
    if(on_     != other.on_)     { setOn(other.on());     dirty = true; }
    return dirty;
}

bool Light::appendNameChange(const Light& other){
    if(!other.name_.trimmed().isEmpty() && name_ != other.name_){
        name_ = other.name_;
        return true;
    }
    return false;
}

bool Light::isGroup() const
{
    return isGroup_;
}

std::weak_ptr<Group> Light::parentGroup() const
{
    return parentGroup_;
}

void Light::setParentGroup(const std::weak_ptr<Group> &parentGroup)
{
    parentGroup_ = parentGroup;
}
