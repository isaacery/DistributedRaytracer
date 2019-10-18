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
	RayType raytype;
	Vec3f o;
	Vec3f d;
};


struct Hit{
	float t; // t value associated with intersection
	Ray ray_in;
	Vec3f n; // normal vector at point of intersection
	Vec3f point; // point of intersection
	Material* mat; // material at point where ray hits a shape
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
