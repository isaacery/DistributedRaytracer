/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{

    void TriMesh::createTriMesh(Value& shapeSpecs) {
    BlinnPhong mat = new BlinnPhong();
    mat->createBlinnPhong(shapeSpecs["material"]); // parse material
    material = mat;
    Value& triangles = shapeSpecs["triangles"];
    if triangles.IsArray() {
        Triangle* triangle;
        for (SizeType i = 0; i < triangles.Size(); i++) {
            triangle = new Triangle();
            triangle.createShape(triangles[i].GetObject());
            triangle.setMaterial(material);
        }
    }
}

Hit TriMesh::intersect(Ray ray) {
    Hit closest;
    closest.itsct = false;
    closest.t = INFINITY;
    for (Triangle* tri : triangles) {
        Hit i = tri->intersect(ray);
        if (i.itsct && i.t < closest.t) {
            closest = i;
        }
    }
    return closest;
}




} //namespace rt
