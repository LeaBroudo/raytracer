#ifndef SPHEREH
#define SPHEREH
#include "surface.h"
#include "bound.h"
#include <float.h>

void sphere_uv(const vec3& p, float& u, float& v) {
    float phi = atan2(p.z(), p.x()); 
    float theta = asin(p.y());

    u = 1 - (phi + M_PI)/(2 * M_PI); 
    v = (theta + M_PI/2)/M_PI; 
}

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
                sphere_uv((rec.p-center)/radius, rec.u, rec.v); 
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;

                return true; 
            } 

            t = (-b + sqrt(discriminant)) / a;
            if (t > t_min && t < t_max) {
                rec.t = t;
                rec.p = r.point_at_param(t);
                sphere_uv((rec.p-center)/radius, rec.u, rec.v); 
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;

                return true;
            }

        }
        return false; 
    }

    virtual bool bounding_box(float t0, float t1, bound& box) const {
        vec3 min = center - vec3(radius, radius, radius); 
        vec3 max = center + vec3(radius, radius, radius); 

        box = bound(min, max); 
        return true; 
    }

};

class fast_sphere: public surface {
public:
    fast_sphere() {}
    fast_sphere(vec3 cen_0, vec3 cen_1, float t_0, float t_1, float rad, material *mat) {
        cen0 = cen_0; 
        cen1 = cen_1; 

        t0 = t_0;
        t1 = t_1; 

        radius = rad; 
        mat_ptr = mat; 
    };
    
    vec3 cen0, cen1;
    float t0, t1;
    float radius;
    material *mat_ptr;

    vec3 center(float t) const {
        return cen0 + (cen1-cen0) * ((t-t0) / (t1-t0));
    }
    
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        
        vec3 cen = center(r.time());
        
        vec3 AC = r.origin() - cen;
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
                rec.normal = (rec.p - cen) / radius;
                rec.mat_ptr = mat_ptr;

                return true; 
            } 

            t = (-b + sqrt(discriminant)) / a;
            if (t > t_min && t < t_max) {
                rec.t = t;
                rec.p = r.point_at_param(t);
                rec.normal = (rec.p - cen) / radius;
                rec.mat_ptr = mat_ptr;

                return true;
            }

        }
        return false; 
    }

    virtual bool bounding_box(float t0, float t1, bound& box) const {
        
        vec3 min_0 = center(t0) - vec3(radius, radius, radius); 
        vec3 max_0 = center(t0) + vec3(radius, radius, radius); 
        bound box_0(min_0, max_0);

        vec3 min_1 = center(t1) - vec3(radius, radius, radius); 
        vec3 max_1 = center(t1) + vec3(radius, radius, radius); 
        bound box_1(min_1, max_1);

        box = parent_bound(box_0, box_1); 
        return true; 
    }

};


#endif