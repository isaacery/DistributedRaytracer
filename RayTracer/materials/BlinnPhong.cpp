/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"



namespace rt{


Vec3f shade(Scene* scene, Hit h, int nbounces) {
    float k_a, k_d, k_s, r = ambient, diffuse, specular, reflectance;
    Vec3f n = h.n;
    Vec3f dir = h.ray_in.d;

    float i_p = k_a * scene->getAmbient(); // total intensity, init ambient light

    /* shade using phong shading */
    for (auto l : scene->getLightSources()) { //TODO: why auto? HELP ME QAIS
        Vec3f light_dir = l.vFrom(h.point); // get direction from intersection point to light
        // reflect light_dir about normal
        Vec3f light_reflection_dir = light_dir - 2 * light_dir.dotProduct(n) * n;
        // reflect dir about normal
        /* check for shadow */
        Ray shadow_ray = {SHADOW,h.point,light_dir}; // ray to cast toward light
        Hit* h = getIntersection(scene, shadow_ray);
        // if there's a shape between point and light, skip to next light
        if (h.t >= 0) continue; // TODO: need to avoid the case where shapes are behind lights
        /* calculate diffuse and specular shading */
        i_p += l.getIntersity() * k_d * std::max(0.f,(-light_dir).dotProduct(n)); // diffuse
        i_p += l.getIntersity() * k_s * std::pow(std::max(0.f,
                light_reflection_dir.dotProduct(-dir)), alpha); // specular
    }

    /* recursively trace ray for reflection */
    if (n_bounces > 1) {
        Vec3f reflect_dir = dir - 2 * dir.dotProduct(n) * n;
        Ray ray_out = {SECONDARY,h.point,reflect_dir} // cast reflection ray
        // interpolate between phong shaded intensity and reflection
        i_p = r * i_p + (1-r) * RayTracer::rayTrace(scene,ray_out,nbounces-1);
    }
}


} //namespace rt
