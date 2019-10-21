/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"


using namespace rapidjson;

namespace rt{

class Camera{
public:

	// constructors
	Camera() {};
	Camera(int height, int width, int fov, Matrix44f cameraToWorld):
		height(height), width(width), fov(fov), cameraToWorld(cameraToWorld) {};

	// destructor
	virtual ~Camera();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;

	//
	// other camera functions (to complete)
	//

	//
	// Getters and Setters
	//
	int getHeight() const {
		return height;
	}

	void setHeicToWght(int height) {
		this->height = height;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	int getFov() const {
		return fov;
	}

	void setFov(int fov) {
		this->fov = fov;
	}

	Matrix44f getCameraToWorld() const {
		return cameraToWorld;
	}

	void setCameraToWorld(Matrix44f cameraToWorld) {
		this->cameraToWorld = cameraToWorld;
	}



protected:
	int height;
	int width;
	int fov;
	Matrix44f cameraToWorld;
};

} //namespace rt



#endif /* CAMERA_H_ */
