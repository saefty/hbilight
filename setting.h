/**
  * @author Saef Taher
  * @date 14/01/2018
  */

#ifndef SETTING_H
#define SETTING_H

/**
 * @brief The Setting class is a basic cotainer for some settings.
 */
class Setting
{
public:
    Setting(double opacity = 100, double transistion = 10, double ambiBrightness = 100, double ambiSatFactor = 100);
    double opacity() const;
    void setOpacity(double opacity);

    double transistion() const;
    void setTransistion(double transistion);

    double ambiBrightness() const;
    void setAmbiBrightness(double ambiBrightness);

    double ambiSatFactor() const;
    void setAmbiSatFactor(double ambiSatFactor);

private:
    double opacity_;
    double transistion_;
    double ambiBrightness_;
    double ambiSatFactor_;
};

#endif // SETTING_H
