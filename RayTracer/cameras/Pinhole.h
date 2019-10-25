/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"

namespace rt{

class Pinhole:public Camera{
public:
	//
	// Constructors
	//
	Pinhole();
	Pinhole(int width, int height, int fov, Matrix44f cameraToWorld):
		Camera(width, height, fov, cameraToWorld){};

	//
	//Destructor
	//
	~Pinhole(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

	float getFocus() {
		return -1;
	}

	Vec3f getPosition() { // return position of camera in camera space 
		return Vec3f(0);
	}
};



} //namespace rt




#endif /* PINHOLE_H_ */
