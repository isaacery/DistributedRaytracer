/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{
	RayType raytype;
	Vec3 o;
	Vec3 d;
};


struct Hit{
	bool itsct; // true if intersection has occured
	float t; // t value associated with intersection
	Vec3f point; // point where ray hits a shape
	Material mat; // material at point where ray hits a shape
};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
