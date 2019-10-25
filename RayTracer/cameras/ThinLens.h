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

	Vec3f getPosition() { // return sample of position of camera in camera space
		// randomly generate radius
		float r = ((float) rand() / (RAND_MAX));
		// randomly generate theta
		float theta = ((float) rand() / (RAND_MAX)) * 2 * M_PI;
		return Vec3f(r*cos(theta),r*sin(theta),0);
	}

private:
	float focus; // focal distance
	float radius; // radius of lens TODO: how do I use this?

};



} //namespace rt




#endif /* THINLENS_H_ */
