#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "surfaceList.h"
#include "sphere.h"
#include "camera.h"
#include "materials.h"
#include "random.h"

vec3 color(const ray& r, surface *world, int depth);
surface *random_scene();

int main() {
	int xPos = 2400;
	int yPos = 2400;
    int sPos = 10;
    //int xPos = 600;
	//int yPos = 600;

	std::cout << "P3\n" << xPos << " " << yPos << "\n255\n";
    
    //Spheres
    ///*
    surface *list[4];
    list[0] = new sphere(vec3(0,0,1), .5, new lambert(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(1,0,1), .5, new metal(vec3(0.0, 0.3, 0.3), 1.0));
    list[2] = new sphere(vec3(0,-100.5,1), 100, new metal(vec3(0.8, 0.6, 0.2), 0.01));
    list[3] = new sphere(vec3(-1,0,1), .5, new dielectric(1.5));
    surface *world = new surfaceList(list, 4);
    //*/
    /*
    surface *list[3];
    list[0] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[1] = new sphere(vec3(-4, 1, 0), 1.0, new lambert(vec3(0.4, 0.2, 0.1)));
    list[2] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    surface *world = new surfaceList(list, 3);
    */
    /*
    surface *list[4];
    list[0] =  new sphere(vec3(0,-7000,0), 7000, new lambert(vec3(0.5, 0.5, 0.5)));
    list[1] = new sphere(vec3(0, 1, 1), 1.0, new dielectric(1.5));
    list[2] = new sphere(vec3(-4, 1, 1), 1.0, new lambert(vec3(0.4, 0.2, 0.1)));
    list[3] = new sphere(vec3(4, 0.2, 1), 0.2, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    surface *world = new surfaceList(list, 4);
    */
    //surface *world = random_scene();

    //Ball Row
    /*
    surface *list[10];
    list[0] =  new sphere(vec3(0,-500,0), 500, new metal(vec3(0.7, 0.6, 0.5), 0.0)); //metal!!

    list[1] = new sphere(vec3(4.8, 0.17, 1), 0.2, new lambert(vec3(.99, .13, 0.00)));
    list[2] = new sphere(vec3(4.2, 0.38, 1), 0.4, new lambert(vec3(.99, .38, 0.29)));
    list[3] = new sphere(vec3(3.2, 0.59, 1), 0.6, new lambert(vec3(.996, .58, .519)));
    list[4] = new sphere(vec3(1.8, 0.8, 1), 0.8, new lambert(vec3(.996, .71, .67)));
    list[5] = new sphere(vec3(0, 1.0, 1), 1.0, new dielectric(1.5));
    list[6] = new sphere(vec3(-1.8, 0.8, 1), 0.8, new lambert(vec3(.80, .85, .99)));
    list[7] = new sphere(vec3(-3.2, 0.59, 1), 0.6, new lambert(vec3(0.59, 0.6, .99)));
    list[8] = new sphere(vec3(-4.2, 0.38, 1), 0.4, new lambert(vec3(0.27, 0.36, 0.99)));
    list[9] = new sphere(vec3(-4.8, 0.17, 1), 0.2, new lambert(vec3(0.0, 0.12, 0.99)));
    surface *world = new surfaceList(list, 10);
    */

    //Geo thing
    /*
    surface *list[43];
    list[0] =  new sphere(vec3(0,0,0), 1.0, new metal(vec3(.99, .38, 0.29), 0.0)); //center
    int val = 1;
    for (int n=0; n<3; n++) {
        for (int p=0; p<2; p++) {
            vec3 blank(0,0,0);
            if (p==0) blank[n] = -1.5;
            else blank[n] = 1.5;
            list[val++] =  new sphere(blank, 0.5, new metal(vec3(0.78, 0.53, 0.0), 0.0));

            for (int q=0; q<3; q++) {
                blank[q] += 0.75;
                list[val++] =  new sphere(blank, 0.25, new metal(vec3(0.59, 0.99, 0.57), 0.0));
                blank[q] -= 0.75*2.0;
                list[val++] =  new sphere(blank, 0.25, new metal(vec3(0.59, 0.99, 0.57), 0.0));
                blank[q] += 0.75;
            }
        }
    }
    
    surface *world = new surfaceList(list, 43);
    */
    
    
    //Camera
    //vec3 origin(-15,4,-20); //for ball row
    vec3 origin(7,4,-20);
    vec3 dest(0,0,0); 
    float focus_dist = 10.0;
    //float focus_dist = (origin-dest).length();
    float aperture = 0.1;

    camera cam(origin, dest, vec3(0,1,0), 20, float(xPos)/float(yPos), aperture, focus_dist);

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
			int intRed = int(255.99 * vector[0]); //change so i dont have to do this?
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
    //vec3 startValue = (1.0-t)*vec3(1.0,1.0,1.0);
    //vec3 endValue = t*vec3(0.5,0.7,1.0);
    //vec3 startValue = (1-t)*vec3(.43,.56,.99);
    vec3 startValue = (1-t)*vec3(1,1,1);
    vec3 endValue = t*vec3(.16,.2,.35);

    return startValue + endValue;
    
}

surface *random_scene() {
    int n = 500;
    surface **list = new surface*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambert(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = get_rand();
            vec3 center(a+0.9*get_rand(),0.2,b+0.9*get_rand());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, 0.2,
                        new lambert(vec3(get_rand()*get_rand(),
                                            get_rand()*get_rand(),
                                            get_rand()*get_rand())
                        )
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                            new metal(vec3(0.5*(1 + get_rand()),
                                           0.5*(1 + get_rand()),
                                           0.5*(1 + get_rand())),
                                      0.5*get_rand()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambert(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new surfaceList(list,i);
}