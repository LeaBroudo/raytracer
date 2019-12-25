#ifndef RECTANGLEH
#define RECTANGLEH
#include "vec3.h"
#include "ray.h"
#include "surface.h"

class rect_xy: public surface {
public:
    rect_xy() {}
    rect_xy(float left, float right, float bottom, float top, float z, material *mat) {
        x0 = left;
        x1 = right; 
        y0 = bottom;
        y1 = top;
        k = z;
        mat_pt = mat; 
    }

    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const {
        float t = (k-r.origin().z() / r.direction().z());
        if (t < t0 || t > t1) return false; 

        float x = r.origin().x() + t*r.direction().x(); 
        float y = r.origin().y() + t*r.direction().y(); 
        if (x < x0 || x > x1 || y < y0 || y > y1) return false; 

        rec.u = (x-x0) / (x1-x0); 
        rec.v = (y-y0) / (y1-y0); 
        rec.t = t; 
        rec.mat_ptr = mat_pt; 
        rec.p = r.point_at_param(t); 
        rec.normal = vec3(0,0,1); 
        
        return true; 
    }

    virtual bool bounding_box(float t0, float t1, bound& box) const {
        box = bound(vec3(x0, y0, k-0.0001), vec3(x1, y1, k+0.0001));
        return true;
    }

    material *mat_pt;
    float x0, x1, y0, y1, k; 

};

#endif