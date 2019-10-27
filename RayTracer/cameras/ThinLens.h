/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include <random>
#include <math.h>

#include "core/Camera.h"


namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens():Camera(){};
	ThinLens(int width, int height, int fov, Matrix44f cameraToWorld, float focus, float radius):
		Camera(width, height, fov, cameraToWorld) {
			this->focus = focus;
			this->radius = radius;
		}

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

	float getFocus() {
		return focus;
	}

	Vec3f getPosition() { // return sample of position of lens in camera space
		float r = ((float) rand() / (RAND_MAX)) * radius; // randomly generate r in [0,radius]
		float theta = ((float) rand() / (RAND_MAX)) * 2 * M_PI; // randomly generate theta in [0, 2pi]
		return Vec3f(r*cos(theta),r*sin(theta),0); // return random point on lens
	}

	Vec3f getPosition(float g_min, float g_max) { // jittered grid sampling
		float x = g_min + ((double) rand() / (RAND_MAX/(g_max-g_min)));
        float y = g_min + ((double) rand() / (RAND_MAX/(g_max-g_min)));
		float r = x * radius; // randomly generate r in [0,radius]
		float theta = y * 2 * M_PI; // randomly generate theta in [0, 2pi]
		return Vec3f(r*cos(theta),r*sin(theta),0); // return random point on lens
	}

	bool distributed() {
		return true;
	}

private:
	float focus; // focal depth
	float radius; // radius of lens

};



} //namespace rt




#endif /* THINLENS_H_ */
