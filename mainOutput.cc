#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "surfaceList.h"
#include "sphere.h"
#include "camera.h"
#include "materials.h"
#include "random.h"

vec3 color(const ray& r, surface *world, int depth);
//float hit_sphere(const vec3& center, float radius, const ray& r);

int main() {
	int xPos = 400;
	int yPos = 200;
    int sPos = 100;

	std::cout << "P3\n" << xPos << " " << yPos << "\n255\n";
    
    //Spheres
    surface *list[2];
    list[0] = new sphere(vec3(0,0,1), 0.5, new lambert(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new metal(vec3(0.8, 0.6, 0.2)));
    surface *world = new surfaceList(list, 2);

    //Camera
    camera cam;
    
    for (int i = yPos-1; i >= 0; i--) {
		for (int j = 0; j < xPos; j++) {

            vec3 vector(0.0, 0.0, 0.0);
            for (int s = 0; s < sPos; s++) {
                float u = float(j + get_rand()) / float(xPos);
                float v = float(i + get_rand()) / float(yPos);
                ray r = cam.get_ray(u, v);
                vector += color(r, world, 0);
            }
            vector /= float(sPos);
            vector = vec3(sqrt(vector[0]), sqrt(vector[1]), sqrt(vector[2]));
            
            //Get individual colors
			int intRed = int(255.99 * vector[0]);
			int intGreen = int(255.99 * vector[1]);
			int intBlue = int(255.99 * vector[2]);

			std::cout << intRed << " " << intGreen << " " << intBlue << "\n";

		}
	}
}

vec3 color(const ray& r, surface *world, int depth) {
    
    hit_record rec;
    if (world -> hit(r, 0.001, MAXFLOAT, rec)) {
        
        ray scattered;
        vec3 attenuation;
        int maxDepth = 50;

        if (depth < maxDepth && rec.mat_ptr -> scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth+1);
        } 

        return vec3(0.0, 0.0, 0.0);
    }
    
    //blended value = (1-t)*startValue +  t*endValue
    vec3 direction = unit_vector(r.direction());
    float t = 0.5 * (direction.y() + 1.0);
    vec3 startValue = (1.0-t)*vec3(1.0,1.0,1.0);
    vec3 endValue = t*vec3(0.5,0.7,1.0);

    return startValue + endValue;
    
}

/*
float hit_sphere(const vec3& center, float radius, const ray& r) {
    
    vec3 AC = r.origin() - center;
    vec3 B = r.direction();

    // (t^2)*dot(B,B) + 2t*dot(B, A-C) + dot(A-C, A-C) - R^2 = 0
    //positive: two solutions, negative: no real solutions, zero:one real solution
    float a = dot(B, B);
    float b = 2.0 * dot(B, AC);
    float c = dot(AC, AC) - pow(radius, 2.0);
    float discriminant = pow(b, 2.0) - 4*a*c;
    
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}
*/
