/*
 * Scene.h
 *
 */
#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "core/Shape.h"

using namespace rapidjson;

namespace rt{

class Shape;

class Scene {
public:

	Scene(){};

	Scene(std::vector<LightSource*> lightSources, std::vector<Shape*> shapes, Vec3f backgroundColour, float ambientLight):
		lightSources(lightSources), shapes(shapes), backgroundColour(backgroundColour), ambientLight(ambientLight){};

	void print() {
		printf("Shapes:\n");
		for (Shape* s : shapes) {
			printf("shape\n");
		}
		printf("Lights:\n");
		for (LightSource* l : lightSources) {
			printf("light\n");
		}
	}

	// getters
	std::vector<Shape*> getShapes() const {
	    return shapes;
	}

	std::vector<LightSource*> getLightSources() const {
	    return lightSources;
	}

	float getAmbientLight() const {
		return ambientLight;
	}

	Vec3f getBackgroundColour() const {
		return backgroundColour;
	}


private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;

	float ambientLight;

	Vec3f backgroundColour;

};

} //namespace rt



#endif /* SCENE_H_ */
