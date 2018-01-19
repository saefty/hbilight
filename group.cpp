#include "group.h"
#include <memory>

Group::Group()
    : Light(-1, "", true, 200, 0, 0, false, true)
{

}

void Group::setOn(bool on)
{
    Light::setOn(on);
    for(auto i = lights_.begin(); i != lights_.end(); i++){
       auto l = (*i).lock();
       if(!l) continue;
       l->setOn(on);
    }
}

void Group::setBri(double bri)
{
    Light::setBri(bri);
    for(auto i = lights_.begin(); i != lights_.end(); i++){
        auto l = (*i).lock();
        if(!l) continue;
        l->setBri(bri);
    }
}

void Group::setSat(double sat)
{
    Light::setSat(sat);
    for(auto i = lights_.begin(); i != lights_.end(); i++){
        auto l = (*i).lock();
        if(!l) continue;
        l->setSat(sat);
    }
}

void Group::setHue(double hue)
{
    Light::setHue(hue);
    for(auto i = lights_.begin(); i != lights_.end(); i++){
        auto l = (*i).lock();
        if(!l) continue;
        l->setHue(hue);
    }
}

void Group::setIsAmbi(bool isAmbi)
{
    Light::setIsAmbi(isAmbi);
    for(auto i = lights_.begin(); i != lights_.end(); i++){
        auto l = (*i).lock();
        if(!l) continue;
        l->setIsAmbi(isAmbi);
    }
}

void Group::addLight(std::shared_ptr<Group> group, std::shared_ptr<Light> light){
    group->lights().push_back(light);
    light->setParentGroup(std::weak_ptr<Group>(group));
}


void Group::removeLight(int index) {
    auto l = lights_.at(index).lock();
    if(!l) return;
    l->setParentGroup(std::weak_ptr<Group>());
    lights_.erase(lights_.begin()+index);
}

std::vector<std::weak_ptr<Light> > Group::lights() const
{
    return lights_;
}

std::vector<std::weak_ptr<Light> > &Group::lights()
{
    return lights_;
}


