/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"



namespace rt{

const float EPSILON = 0.001; // distance above surface from which to cast ray to avoid rounding errors

Vec3f BlinnPhong::shade(Scene* scene, Hit h, int nbounces) {
    float k_a = ambient;
    float k_d = diffuse;
    float k_s = specular;
    float r = reflectance;
    Vec3f n = h.n;
    Vec3f dir = h.ray_in.d;

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
        Ray shadow_ray = {SHADOW,h.point+(EPSILON*light_dir),light_dir}; // ray to cast toward light
        Hit s = RayTracer::getIntersection(scene, shadow_ray);
        // if there's a shape between point and light, skip to next light
        if (s.itsct) continue; // TODO: need to avoid the case where shapes are behind lights

        /* calculate diffuse and specular shading */
        i_p += (l->getIntersity() * k_d * std::max(0.f,(light_dir).dotProduct(n))) * d_m; // diffuse
        i_p += l->getIntersity() * k_s * std::pow(std::max(0.f,
                light_reflection_dir.dotProduct(-dir)), alpha) * d_m; // specular
    }

    Vec3f out = i_p * colour;

    /* recursively trace ray for reflection */
    if (nbounces > 1 && r > 0) {
        Vec3f reflect_dir = (dir - 2 * dir.dotProduct(n) * n).normalize();
        Ray ray_out = {SECONDARY,h.point+EPSILON*reflect_dir,reflect_dir}; // cast reflection ray
        // interpolate between phong shaded intensity and reflection
        out = (1-r) * out  + r * RayTracer::rayTrace(scene,ray_out,nbounces-1);
    }

    return out;
}

void BlinnPhong::print() {
    printf("Material of type BlinnPhong\n\tSpecular: %f\n\tDiffuse: %f\n\tAmbient: %f\n",
            this->specular, this->diffuse, this->ambient);
}


} //namespace rt
