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
    Vec3f vFrom(Vec3f point) {
        return (position - point).normalize();
    }

private:
    Vec3f position;


};



} //namespace rt




#endif /* POINTLIGHT_H_ */
