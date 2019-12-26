#ifndef RECTANGLEH
#define RECTANGLEH
#include "vec3.h"
#include "ray.h"
#include "surface.h"
#include "surfaceList.h"
#include "bound.h"

class rect_xy: public surface {
public:
    rect_xy() {}
    rect_xy(float left, float right, float bottom, float top, float K, material *mat) {
        x0 = left;
        x1 = right; 
        y0 = bottom;
        y1 = top;
        k = K;
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

class rect_xz: public surface {
public:
    rect_xz() {}
    rect_xz(float left, float right, float back, float front, float K, material *mat) {
        x0 = left;
        x1 = right; 
        z0 = back ;
        z1 = front;
        k = K;
        mat_pt = mat; 
    }

    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const {
        float t = (k-r.origin().y() / r.direction().y());
        if (t < t0 || t > t1) return false; 

        float x = r.origin().x() + t*r.direction().x(); 
        float z = r.origin().z() + t*r.direction().z(); 
        if (x < x0 || x > x1 || z < z0 || z > z1) return false; 

        rec.u = (x-x0) / (x1-x0); 
        rec.v = (z-z0) / (z1-z0); 
        rec.t = t; 
        rec.mat_ptr = mat_pt; 
        rec.p = r.point_at_param(t); 
        rec.normal = vec3(0,1,0); 
        
        return true; 
    }

    virtual bool bounding_box(float t0, float t1, bound& box) const {
        box = bound(vec3(x0, k-0.0001, z0), vec3(x1, k+0.0001, z1));
        return true;
    }

    material *mat_pt;
    float x0, x1, z0, z1, k; 

};

class rect_yz: public surface {
public:
    rect_yz() {}
    rect_yz(float bottom, float top, float back, float front, float K, material *mat) {
        y0 = bottom;
        y1 = top; 
        z0 = back ;
        z1 = front;
        k = K;
        mat_pt = mat; 
    }

    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const {
        float t = (k-r.origin().x() / r.direction().x());
        if (t < t0 || t > t1) return false; 

        float y = r.origin().y() + t*r.direction().y(); 
        float z = r.origin().z() + t*r.direction().z(); 
        if (y < y0 || y > y1 || z < z0 || z > z1) return false; 

        rec.u = (y-y0) / (y1-y0); 
        rec.v = (z-z0) / (z1-z0); 
        rec.t = t; 
        rec.mat_ptr = mat_pt; 
        rec.p = r.point_at_param(t); 
        rec.normal = vec3(1,0,0); 
        
        return true; 
    }

    virtual bool bounding_box(float t0, float t1, bound& box) const {
        box = bound(vec3(k-0.0001, y0, z0), vec3(k+0.0001, y1, z1));
        return true;
    }

    material *mat_pt;
    float y0, y1, z0, z1, k; 

};

class flip_normal : public surface {
public:
    flip_normal(surface *ptr) : p(ptr) {}

    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const {
        if (p -> hit(r, t0, t1, rec)) {
            rec.normal *= -1; 
            return true; 
        }
        return false; 
    }

    virtual bool bounding_box(float t0, float t1, bound& box) const {
        return p -> bounding_box(t0, t1, box); 
    }

    surface *p; 
    
};

class box: public surface {
    public:
        box() {}
        box(const vec3& p0, const vec3& p1, material *p) {
            pmin = p0;
            pmax = p1;
            surface **list = new surface*[6];
            list[0] = new rect_xy(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), p);
            list[1] = new flip_normal(new rect_xy(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), p));
            list[2] = new rect_xz(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), p);
            list[3] = new flip_normal(new rect_xz(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), p));
            list[4] = new rect_yz(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), p);
            list[5] = new flip_normal(new rect_yz(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), p));
            list_ptr = new surfaceList(list,6);
        }
        
        virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const {
            return list_ptr->hit(r, t0, t1, rec);
        }
        
        virtual bool bounding_box(float t0, float t1, bound& box) const {
            box =  bound(pmin, pmax);
            return true;
        }
        
        vec3 pmin, pmax;
        surface *list_ptr;
};

#endif