/********
Create a ray starting from the Camera that passes through the
corresponding pixel on the image plane.
Camera parameters as in gluLookAt
*********/
#ifndef _INCLUDECameraHEADER
#define _INCLUDECameraHEADER

#include "glm/glm.hpp"
#include "Ray.h"
//const float pi = 3.14159265;
using namespace glm;
class Camera{
public:
	Camera(const vec3 &eye, const vec3 &center, const vec3 &up, 
		float fovy, int height, int width);
	~Camera(){};
	Ray GenerateRay(int i, int j);
private:
	float theta;
	int height, width;
	float t_max, t_min;
	vec3 u, v, w;
	vec3 eye;
};

#endif

