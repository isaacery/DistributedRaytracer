/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"


namespace rt{

class ThinLens:public Camera{
public:

	//
	// Constructors
	//
	ThinLens():Camera(){};
	ThinLens(int width, int height, int fov, Matrix44f cameraToWorld):
		Camera(width, height, fov, cameraToWorld) {
			this->focus = focus;
			this->radius = radius;
		}
	Camera(width, height, fov, cameraToWorld){}

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();

private:
	float focus; // focal distance
	float radius; // radius of lens TODO: how do I use this?

};



} //namespace rt




#endif /* THINLENS_H_ */
