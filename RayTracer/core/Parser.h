#include <string>
#include <map>

//#include "core/Material.h"
#include "materials/BlinnPhong.h"

#include "core/Scene.h"

//#include "core/Camera.h"
#include "cameras/Pinhole.h"

#include "lights/PointLight.h"

// #include "core/Shape.h"
#include "shapes/Plane.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"

using namespace rapidjson;
using std::string;

namespace rt{

class Parser{

public:

    static void parseMaterials(Value& mats, std::map<string,Material*>& materials) {
        Material* m;
        //Value& mats = d["materials"];
        //std::map<string,Material*> materials;
        if (mats.IsArray()) {
    		std::cout<<"Parsing "<<mats.Size()<<" materials\n";
    		for (SizeType i = 0; i < mats.Size(); i++) {
    			Value materialSpecs = mats[i].GetObject();
    			string materialType = materialSpecs["type"].GetString();
    			if (materialType.compare("blinnphong") == 0) {
    				BlinnPhong* o = new BlinnPhong();
    				o->createBlinnPhong(materialSpecs);
    				m = o;
    			}
    			materials.insert(std::pair<string,Material*>(materialSpecs["name"].GetString(),m));
    		}
    	}
    }

    static void parseShapes(Value& shps, std::vector<Shape*>& shapes, std::map<string,Material*>& materials) {
        Shape* s;
    	//Value& shps = d["shapes"];
    	//std::vector<Shape*> shapes;
    	if (shps.IsArray()) {
    		std::cout<<"Parsing "<<shps.Size()<<" shapes\n";
    		for (SizeType i = 0; i < shps.Size(); i++) {
    			Value shapeSpecs = shps[i].GetObject();
    			string shapeType = shapeSpecs["type"].GetString();
    			if (shapeType.compare("sphere") == 0) {
    				Sphere* o = new Sphere();
    				o->createSphere(shapeSpecs);
    				s = o;
    			} else if (shapeType.compare("plane") == 0) {
    				Plane* o = new Plane();
    				o->createPlane(shapeSpecs);
    				s = o;
    			} else if (shapeType.compare("triangle") == 0) {
    				Triangle* o = new Triangle();
    				o->createTriangle(shapeSpecs);
    				s = o;
    			} else if (shapeType.compare("trianglemesh") == 0) {
    				TriMesh* o = new TriMesh();
    				o->createTriMesh(shapeSpecs);
                    o->setMaterial(materials[shapeSpecs["material"].GetString()]); // TODO: inelegant
    				s = o;
    			}
                s->setMaterial(materials[shapeSpecs["material"].GetString()]);
    			shapes.push_back(s);
    		}
    	}
    }

    static void parseLights(Value& lts, std::vector<LightSource*>& lights) {
        LightSource* l;
        if (lts.IsArray()) {
            std::cout<<"Parsing "<<lts.Size()<<" lights\n";
            for (SizeType i = 0; i < lts.Size(); i++) {
                Value lightSpecs = lts[i].GetObject();
                string lightType = lightSpecs["type"].GetString();
                if (lightType.compare("pointlight") == 0) {
                    PointLight* o = new PointLight();
                    o->createPointLight(lightSpecs);
                    l = o;
                } /*else if (lightType.compare("arealight") == 0) {
                    AreaLight* o = new AreaLight();
                    o->createPlane(lightSpecs);
                    l = o;
                } */
                lights.push_back(l);
            }
        }
    }

    /* parse scene information from raytracer input file */
    static Scene* parseScene(Value& d) {
        std::map<string,Material*> materials;
        std::vector<Shape*> shapes;
    	std::vector<LightSource*> lights;
        parseMaterials(d["materials"], materials); // parse materials
        parseShapes(d["shapes"], shapes, materials); // parse shapes
        parseLights(d["lightsources"], lights); // parse lights
    	float r = d["backgroundcolour"][0].GetFloat(); // parse background colour
    	float g = d["backgroundcolour"][1].GetFloat();
    	float b = d["backgroundcolour"][2].GetFloat();
    	Vec3f backgroundColour = Vec3f(r,g,b);
    	float ambient = d["ambient"].GetFloat(); // parse ambient intensity

        return new Scene(lights, shapes, backgroundColour, ambient);
    }

};

} //namespace rt
