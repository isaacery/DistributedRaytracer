/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "cmath"

namespace rt{

class Scene;

/*
 * Raytracer class declaration
 */
class RayTracer {
public:

	RayTracer();

	static Vec3f* render(Camera* camera, Scene* scene, int nbounces, int nsamples);
	static Hit getIntersection(Scene* scene, Ray ray);
	static Vec3f rayTrace(Scene* scene, Ray ray, int nbounces, int nsamples);
	static Vec3f* tonemap(Vec3f* pixelbuffer, int len);


private:


};




} //namespace rt



#endif /* RAYTRACER_H_ */
