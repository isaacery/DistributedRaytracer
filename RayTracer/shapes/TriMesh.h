/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"
#include "core/Material.h"

using namespace rapidjson;

namespace rt{

// TODO: NAIVE APPROACH

class Material;
struct Hit;
struct Ray;

<<<<<<< HEAD
class TriMesh:public Shape{
public:
    // constructors
    TriMesh();
=======
using namespace rapidjson;

class TriMesh:public Shape{
public:
    // constructors
    TriMesh():Shape(){};
>>>>>>> tmp
    TriMesh(std::vector<Triangle*> triangles, Material* material):
        Shape(material) {
            // update material of every triangle to material of mesh
            for (Triangle* tri : triangles) {
                tri->setMaterial(material);
            }
            this->triangles = triangles;
        }

<<<<<<< HEAD
=======
    void setMaterial(Material* mat) {
        material = mat;
        for (Triangle* tri : triangles) {
            tri->setMaterial(material);
        }
    }

>>>>>>> tmp
    void createTriMesh(Value& shapeSpecs);

    Hit intersect(Ray ray);

private:
    //std::vector<Vec3f> tInd; // triangle index, each entry point to three vertices
    std::vector<Triangle*> triangles;

};



} //namespace rt




#endif /* TRIMESH_H_ */
