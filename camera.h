#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include "random.h"

class camera {
public:
    camera() {
        ll_corner = vec3(-2.0, -1.0, 1.0);
        horiz = vec3(4.0, 0.0, 0.0);
        vert = vec3(0.0, 2.0, 0.0);
        orig = vec3(0.0, 0.0, 0.0);
    }

    vec3 orig;
    vec3 ll_corner;
    vec3 horiz, vert;
    vec3 u, v, w;  
    float lens_rad;
    
    ray get_ray(float s, float t) {
        
        vec3 rd = lens_rad * rand_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        
        vec3 A = orig + offset;
        vec3 B = ll_corner + s*horiz + t*vert - orig - offset;
        
        return ray(A, B);
    }

};

#endif