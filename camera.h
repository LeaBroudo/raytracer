#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include "random.h"

class camera {
public:
    camera(vec3 og, vec3 dest, vec3 up, float fov, float aspect, float aperture, float focus) {
        
        //Get ratios
        float angle = fov*M_PI/180;
        float height_mid = tan(angle/2);
        float width_mid = aspect * height_mid; 
        radius = aperture/2;

        //Get vectors
        orig = og;
        vec3 w = unit_vector(og-dest);
        vec3 u = unit_vector(cross(up, w));
        vec3 v = cross(w,u);
        
        //Get dimensions
        horiz = 2*focus*width_mid*u;
        vert = 2*focus*height_mid*v;
        ll_corner = orig - horiz/2 - vert/2 - focus*w; 
        
    }

    vec3 orig;
    vec3 ll_corner;
    vec3 horiz, vert;
    vec3 u, v, w;  
    float radius;
    
    ray get_ray(float u2, float v2) {
        
        vec3 rd = radius * rand_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        
        vec3 A = orig + offset;
        vec3 B = ll_corner + u2*horiz + v2*vert - orig - offset;
        
        return ray(A, B);
    }

};

#endif