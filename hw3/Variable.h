#ifndef	_INCLUDEVARIABLEHEADER
#define _INCLUDEVARIABLEHEADER

#include "glm\glm.hpp"
using namespace glm;
#define FarFarAway 10000.0f
#define NEAR 0.00001f

struct object{
	vec3 diffuse;
	vec3 emission;
	vec3 specular;
	vec3 ambient;
	float shininess;
	mat4 transform;
};

struct intersectP{
	vec3 normal;
	float tHit;
	//to calculate color for each pixel, we need to return the material.
	object obj;
	vec3 intersectPoint;
};

inline vec3 vec4_to_vec3(vec4 &in) {
	float w = abs(in.w) < NEAR ? 1.0f : in.w;
	return vec3(in.x / w, in.y / w, in.z / w);
}



#endif