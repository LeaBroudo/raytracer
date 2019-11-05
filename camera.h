#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include "random.h"

class camera {
public:
    camera(vec3 og, vec3 dest, vec3 up, float fov, float aspect) {
        
        //Get ratios
        float angle = fov*M_PI/180;
        float height_mid = tan(angle/2);
        float width_mid = aspect * height_mid; 

        //Get vectors
        orig = og;
        vec3 w = unit_vector(og-dest);
        vec3 u = unit_vector(cross(up, w));
        vec3 v = cross(w,u);
        
        //Get dimensions
        //ll_corner = vec3(-1*width_mid, -1*height_mid, -1.0); 
        //horiz = vec3(2*width_mid, 0.0, 0.0);
        //vert = vec3(0.0, 2*height_mid, 0.0);
        ll_corner = orig - width_mid*u - height_mid*v - w; 
        horiz = 2*width_mid*u;
        vert = 2*height_mid*v;
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