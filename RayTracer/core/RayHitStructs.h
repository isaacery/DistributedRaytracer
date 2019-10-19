/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include "core/Material.h"

namespace rt{

class Material;
/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{
	RayType raytype = PRIMARY;
	Vec3f o = Vec3f(0); // origin
	Vec3f d = Vec3f(0); // direction
};


struct Hit{
	bool itsct = false; // true if intersection occurred
	float t = 0; // t value associated with intersection
	Ray ray_in; // ray in to intersection
	Vec3f n = Vec3f(0); // normal vector at point of intersection
	Vec3f point = Vec3f(0); // point of intersection
	Material* mat; // material at point where ray hits a shape
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
