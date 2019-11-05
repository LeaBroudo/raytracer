#ifndef VEC3H
#define VEC3H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:

    vec3() {}
    vec3(float e0, float e1, float e2) {
        e[0] = e0; 
        e[1] = e1;
        e[2] = e2;
        
    }

    //Positions
    inline float x() const {
        return e[0];
    }
    inline float y() const {
        return e[1];
    }
    inline float z() const {
        return e[2];
    }

    //Colors
    inline float r() const {
        return e[0];
    }
    inline float g() const {
        return e[1];
    }
    inline float b() const {
        return e[2];
    }

    //Operations
    inline const vec3& operator+() const {
        return *this;
    }
    inline vec3 operator-() const {
        return vec3(-e[0], -e[1], -e[2]);
    }
    inline float operator[](int val) const {
        return e[val];
    } 
    inline float& operator[](int val) {
        return e[val];
    }

    //Operator function descriptors
    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    //Common Functions
    inline float length() const {
        float val_0 = e[0]*e[0];
        float val_1 = e[1]*e[1];
        float val_2 = e[2]*e[2];

        return sqrt(val_0 + val_1 + val_2);
    }
    inline float squared_length() const {
        float val_0 = e[0]*e[0];
        float val_1 = e[1]*e[1];
        float val_2 = e[2]*e[2];

        return val_0 + val_1 + val_2;
    }
    inline void make_unit_vector();

    float e[3];

};

//Reading/writing vector
inline std::istream& operator>>(std::istream &input, vec3 &vector) {
    input >> vector.e[0] >> vector.e[1] >> vector.e[2];
    return input;
}

inline std::ostream& operator<<(std::ostream &output, const vec3 &vector) {
    output << vector.e[0] << " " << vector.e[1] << " " << vector.e[2];
    return output;
}

//Operations between two vectors
inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

//Vector/constant operations
inline vec3 operator*(float t, const vec3 &vector) {
    return vec3(t*vector.e[0], t*vector.e[1], t*vector.e[2]);
}

inline vec3 operator*(const vec3 &vector, float t) {
    return vec3(t*vector.e[0], t*vector.e[1], t*vector.e[2]);
}

inline vec3 operator/(vec3 vector, float t) {
    return vec3(vector.e[0]/t, vector.e[1]/t, vector.e[2]/t);
}

//Vector Updates
inline vec3& vec3::operator+=(const vec3 &vector) {
    e[0] += vector.e[0];
    e[1] += vector.e[1];
    e[2] += vector.e[2];
    
    return *this;
}

inline vec3& vec3::operator-=(const vec3& vector) {
    e[0] -= vector.e[0];
    e[1] -= vector.e[1];
    e[2] -= vector.e[2];
    
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &vector) {
    e[0] *= vector.e[0];
    e[1] *= vector.e[1];
    e[2] *= vector.e[2];
    
    return *this;
}

inline vec3& vec3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &vector) {
    e[0] /= vector.e[0];
    e[1] /= vector.e[1];
    e[2] /= vector.e[2];
    
    return *this;
}

inline vec3& vec3::operator/=(const float t) {
    float div = 1.0/t;
    e[0] *= div;
    e[1] *= div;
    e[2] *= div;

    return *this;
}

//Unit Vector
inline vec3 unit_vector(vec3 vector) {
    return vector / vector.length();
}

inline void vec3::make_unit_vector() {
    float val_0 = e[0]*e[0];
    float val_1 = e[1]*e[1];
    float val_2 = e[2]*e[2];

    float div = 1.0 / sqrt(val_0 + val_1 + val_2);
    e[0] *= div;
    e[1] *= div;
    e[2] *= div;
}

//Dot and Cross Product
inline float dot(const vec3 &v1, const vec3 &v2) {
    float val_0 = v1.e[0]*v2.e[0];
    float val_1 = v1.e[1]*v2.e[1];
    float val_2 = v1.e[2]*v2.e[2];

    return val_0 + val_1 + val_2;
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    float e0 = v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1];
    float e1 = v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2];
    float e2 = v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0];

    return vec3(e0, e1, e2);
}

#endif


