#ifndef SPHEREH
#define SPHEREH
#include "surface.h"

class sphere: public surface {
public:
    sphere() {}
    sphere(vec3 cen, float rad, material *mat) : center(cen), radius(rad), mat_ptr(mat) {};
    
    vec3 center;
    float radius;
    material *mat_ptr;

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        vec3 AC = r.origin() - center;
        vec3 B = r.direction();
        
        float a = dot(B, B);
        float b = dot(AC, B);
        float c = dot(AC, AC) - pow(radius, 2.0);
        float discriminant = pow(b, 2.0) - a*c;

        if (discriminant > 0) {
            float t = (-b - sqrt(discriminant)) / a;
            if (t > t_min && t < t_max ) {
                rec.t = t;
                rec.p = r.point_at_param(t);
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;

                return true; 
            } 

            t = (-b + sqrt(discriminant)) / a;
            if (t > t_min && t < t_max) {
                rec.t = t;
                rec.p = r.point_at_param(t);
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;

                return true;
            }

        }
        return false; 
    }

};

#endif