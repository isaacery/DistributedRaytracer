/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"


namespace rt{

class PointLight: public LightSource{

public:
    // constructor
    PointLight(Vec3f position, float intensity):
        LightSource(intensity) {
            this->position = position;
        }

    Vec3f vFrom(Vec3f point) {
        return (position - point); //TODO: normalize?
    }

private:
    Vec3f position;


};



} //namespace rt




#endif /* POINTLIGHT_H_ */
