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

	void createScene(Value& scenespecs);

	// getters
	std::vector<Shape*> getShapes() const {
	    return shapes;
	}

	std::vector<LightSource*> getLightSources() const {
	    return lightSources;
	}

	float getAmbient() const {
		return ambient;
	}


private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;

	float ambient;

};

} //namespace rt



#endif /* SCENE_H_ */
