/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"

namespace rt{

void TriMesh::createTriMesh(Value& shapeSpecs) {
    Triangle* triangle;
    Material* mat;
    Vec3f v0, v1, v2;
    Matrix44f objectToWorld;
    if (shapeSpecs.HasMember("objectToWorld")) {
        float a = shapeSpecs["objectToWorld"][0].GetFloat();
        float b = shapeSpecs["objectToWorld"][1].GetFloat();
        float c = shapeSpecs["objectToWorld"][2].GetFloat();
        float d = shapeSpecs["objectToWorld"][3].GetFloat();
        float e = shapeSpecs["objectToWorld"][4].GetFloat();
        float f = shapeSpecs["objectToWorld"][5].GetFloat();
        float g = shapeSpecs["objectToWorld"][6].GetFloat();
        float h = shapeSpecs["objectToWorld"][7].GetFloat();
        float i = shapeSpecs["objectToWorld"][8].GetFloat();
        float j = shapeSpecs["objectToWorld"][9].GetFloat();
        float k = shapeSpecs["objectToWorld"][10].GetFloat();
        float l = shapeSpecs["objectToWorld"][11].GetFloat();
        float m = shapeSpecs["objectToWorld"][12].GetFloat();
        float n = shapeSpecs["objectToWorld"][13].GetFloat();
        float o = shapeSpecs["objectToWorld"][14].GetFloat();
        float p = shapeSpecs["objectToWorld"][15].GetFloat();
        objectToWorld = Matrix44f(a, b, c, d,
                                  e, f, g, h,
                                  i, j, k, l,
                                  m, n, o, p).transpose();
    }
    if (shapeSpecs.HasMember("ply")) { // parse ply
        happly::PLYData ply(shapeSpecs["ply"].GetString());
        std::vector<std::array<double,3>> vs = ply.getVertexPositions();
        std::vector<std::vector<int>> face_idxs = ply.getFaceIndices<int>();
        Vec3f* vertices = (Vec3f*)malloc(vs.size()*sizeof(Vec3f));
        for (int i = 0; i < vs.size(); i++) { // parse vertices
            vertices[i] = Vec3f(vs[i][0],vs[i][1],vs[i][2]);
            if (shapeSpecs.HasMember("objectToWorld")) {
                // transform vertex to world space
                objectToWorld.multVecMatrix(vertices[i],vertices[i]);
            }
        }
        for (int i = 0; i < face_idxs.size(); i++) { // add triangles to mesh
            v0 = vertices[face_idxs[i][0]];
            v1 = vertices[face_idxs[i][1]];
            v2 = vertices[face_idxs[i][2]];
            triangle = new Triangle(v0,v1,v2,mat);
            triangles.push_back(triangle);
        }
    } else if (shapeSpecs["triangles"].IsArray()) { // parse explicit
        for (SizeType i = 0; i < shapeSpecs["triangles"].Size(); i++) {
            triangle = new Triangle();
            Value triangleSpecs = shapeSpecs["triangles"][i].GetObject();
            triangle->createTriangle(triangleSpecs);
            triangles.push_back(triangle);
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
