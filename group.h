        /**
      * @author Saef Taher
      * @date 14/01/2018
      */

    #ifndef GROUP_H
    #define GROUP_H

    #include "light.h"

    #include <vector>
    #include <memory>

    /**
     * @brief The Group class is a container to hold a group of Lights.
     *
     * This has nothing to do with the hue Lights and the bridge. The state
     */
    class Group : public Light
    {
    public:
        Group();
        void setOn(bool on) override;
        void setBri(double bri) override;
        void setSat(double sat) override;
        void setHue(double hue) override;
        void setIsAmbi(bool isAmbi) override;
        bool operator ==(const Group &l);

        /**
         * @brief removeLight removes a light at a given index.
         * @param index index where the light should be removed.
         *
         * Atention: this removes the reversed weak ptr from the light to the group
         */
        void removeLight(int index);

        /**
         * @brief addLight adds a light to the group.
         * @param group the group where it should be added
         * @param light the actual light
         *
         * the group is needed to set a revered weak ptr for the light to the group.
         */
        static void addLight(std::shared_ptr<Group> group, std::shared_ptr<Light> light);

        /**
         * @brief lights returns the lights in this group
         * @return lights in this group.
         */
        std::vector<std::weak_ptr<Light> > lights() const;
        /**
         * @brief lights returns a reference to the vector containing the pointers to the lights
         * @return vector
         */
        std::vector<std::weak_ptr<Light> > &lights();
    private:
        std::vector<std::weak_ptr<Light>> lights_;
    };

    #endif // GROUP_H
