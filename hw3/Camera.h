/********
Create a ray starting from the camera that passes through the
corresponding pixel on the image plane.
Camera parameters as in gluLookAt
*********/
#include "glm/glm.hpp"
#include "Ray.h"
//const float pi = 3.14159265;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
#ifndef _INCLUDECAMERAHEADER
#define _INCLUDECAMERAHEADER

class camera{
public:
	camera(const vec3 &eye, const vec3 &center, const vec3 &up, 
		float fovy, int height, int width);
	~camera(){};
	Ray GenerateRay(int i, int j);
private:
	float theta;
	int height, width;
	float t_max, t_min;
	vec3 u, v, w;
	vec3 eye;
};

#endif

