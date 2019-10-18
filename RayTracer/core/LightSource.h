/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_


namespace rt{

class LightSource{
public:
    float getIntersity() const {
        return intensity;
    }

    void setIntensity(float intensity) {
        this->intensity = intensity;
    }

    /* returns normalised direction from point to light */
    virtual Vec3f vFrom(Vec3f point) = 0;

private:
    float intensity;
};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
