#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "rapidjson/document.h"
#include "math/geometry.h"

namespace rt {

class Texture {
public:
    virtual Vec3f value(float u, float v, Vec3f point) const = 0;
};

} // namespace rt

#endif /* TEXTURE_H_ */
