#include "setting.h"

Setting::Setting(double opacity, double transistion, double ambiBrightness, double ambiSatFactor)
    : opacity_(opacity), transistion_(transistion), ambiBrightness_(ambiBrightness), ambiSatFactor_(ambiSatFactor)
{

}

double Setting::opacity() const
{
    return opacity_;
}

void Setting::setOpacity(double opacity)
{
    opacity_ = opacity;
}

double Setting::transistion() const
{
    return transistion_;
}

void Setting::setTransistion(double transistion)
{
    transistion_ = transistion;
}

double Setting::ambiBrightness() const
{
    return ambiBrightness_;
}

void Setting::setAmbiBrightness(double ambiBrightness)
{
    ambiBrightness_ = ambiBrightness;
}

double Setting::ambiSatFactor() const
{
    return ambiSatFactor_;
}

void Setting::setAmbiSatFactor(double ambiSatFactor)
{
    ambiSatFactor_ = ambiSatFactor;
}
