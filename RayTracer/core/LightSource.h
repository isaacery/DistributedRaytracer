/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "math/geometry.h"
#include "rapidjson/document.h"

namespace rt{

class LightSource{
public:
    // constructors
    LightSource(){};

    LightSource(float intensity): intensity(intensity){};

    float getIntersity() const {
        return intensity;
    }

    void setIntensity(float intensity) {
        this->intensity = intensity;
    }

    /* returns direction from point to light */
    virtual Vec3f vFrom(Vec3f point) = 0;

    virtual Vec3f vFrom(Vec3f point, Vec2f x_bounds, Vec2f y_bounds) = 0; // for grid

    virtual void print() = 0;

    /* true if LightSource uses sampling */
    virtual bool distributed() = 0;

protected:
    float intensity;
};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
