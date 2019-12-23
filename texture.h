#ifndef TEXTUREH
#define TEXTUREH
#include "vec3.h"
#include "ray.h"

class texture {
    public:
        virtual vec3 value(float u, float v, const vec3& p) const = 0; 
}; 

class constant_texture : public texture {
    public:
        constant_texture() {}
        constant_texture(vec3 c) : color(c) {}

        virtual vec3 value(float u, float v, const vec3& p) const {
            return color;
        }

        vec3 color; 
};

class checkers : public texture {
public:
    checkers() {}
    checkers(texture *t0, texture *t1) : even(t0), odd(t1) {}

    virtual vec3 value(float u, float v, const vec3& p) const {
        float check = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());

        if (check < 0) {
            return odd -> value(u,v,p); 
        } else {
            return even -> value(u,v,p); 
        }
    }

    texture *even;
    texture *odd; 
}; 

#endif