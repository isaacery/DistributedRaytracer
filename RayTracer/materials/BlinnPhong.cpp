/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"



namespace rt{

Vec3f BlinnPhong::shade(Scene* scene, Hit h, int nbounces) {
    float k_a = ambient;
    float k_d = diffuse;
    float k_s = specular;
    float r = reflectance;
    Vec3f n = h.n;
    Vec3f dir = h.ray_in.d;

    printf("shading point: %f, %f, %f\n", h.point.x, h.point.y, h.point.z);
    printf("ray origin: %f, %f, %f\n", h.ray_in.o.x, h.ray_in.o.y, h.ray_in.o.z);
    // total intensity, initialized to ambient light contribution
    float i_p = k_a * scene->getAmbientLight();
    /* shade using phong shading */
    for (LightSource* l : scene->getLightSources()) {
        Vec3f light_v = l->vFrom(h.point);
        Vec3f light_dir = light_v.normalize(); // get direction from intersection point to light
        float d_m = 1/(light_v.length() * light_v.length()); // inverse distance squared
        // reflect light_dir about normal
        Vec3f light_reflection_dir = (-light_dir) - 2 * n * (-light_dir).dotProduct(n);
        /* check for shadow */
        Ray shadow_ray = {SHADOW,h.point+(0.001*light_dir),light_dir}; // ray to cast toward light
        Hit s = RayTracer::getIntersection(scene, shadow_ray);
        // if there's a shape between point and light, skip to next light
        if (s.itsct) {
            printf("SHADOW!\n");
            printf("%f, %f, %f\n", light_dir.x, light_dir.y, light_dir.z);
            printf("%f, %f, %f\n", s.point.x, s.point.y, s.point.z);
            continue; // TODO: need to avoid the case where shapes are behind lights
        }
        /* calculate diffuse and specular shading */
        i_p += (l->getIntersity() * k_d * std::max(0.f,(light_dir).dotProduct(n))) * d_m; // diffuse
        //printf("i_p2: %f\n", i_p);
        i_p += l->getIntersity() * k_s * std::pow(std::max(0.f,
                light_reflection_dir.dotProduct(-dir)), alpha) * d_m; // specular
        //printf("i_p3: %f\n", i_p);
    }

    Vec3f out = i_p * colour;

    /* recursively trace ray for reflection */
    if (nbounces > 1) {
        Vec3f reflect_dir = dir - 2 * dir.dotProduct(n) * n;
        Ray ray_out = {SECONDARY,h.point,reflect_dir}; // cast reflection ray
        // interpolate between phong shaded intensity and reflection
        out = r * out  + (1-r) * RayTracer::rayTrace(scene,ray_out,nbounces-1);
    }

    return out;
}

void BlinnPhong::print() {
    printf("Material of type BlinnPhong\n\tSpecular: %f\n\tDiffuse: %f\n\tAmbient: %f\n",
            this->specular, this->diffuse, this->ambient);
}


} //namespace rt
