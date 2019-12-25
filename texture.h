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

class image : public texture {
public:
    image() {}
    image(unsigned char *pixels, int a, int b) : img(pixels), nx(a), ny(b) {}

    virtual vec3 value(float u, float v, const vec3& p) const {
        int i = u * nx;
        int j = (1-v) * ny - 0.001; 

        if (i < 0) i = 0;
        if (i > nx-1) i = nx-1; 

        if (j < 0) j = 0;
        if (j > ny-1) j = ny-1;  

        int idx = 3*i + 3*nx*j; 
        return vec3(int(img[idx])/255.0, int(img[idx+1])/255.0, int(img[idx+2])/255.0);
    }

    unsigned char *img; 
    int nx, ny; 
}; 


#endif