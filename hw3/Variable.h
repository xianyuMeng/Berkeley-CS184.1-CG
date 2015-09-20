#ifndef	_INCLUDEVARIABLEHEADER
#define _INCLUDEVARIABLEHEADER

#include "glm\glm.hpp"
using namespace glm;

struct object{
	vec4 diffuse;
	vec4 emission;
	vec4 specular;
	vec4 ambient;
	float shininess;
	mat4 transform;
};

struct intersectP{
	vec4 normal;
	float tHit;
	//to calculate color for each pixel, we need to return the material.
	object obj;
	vec4 intersectPoint;
};



#endif