#ifndef _INCLUDESPHEREHEADER
#define _INCLUDESPHEREHEADER

#include "Primative.h"


//using namespace glm;

class sphere : public primative{
public:
	//A sphere is defined by its center and radius
	sphere::sphere(const vec3 &center, const float radius, const mat4 &transformobj, const object &obj);

	virtual ~sphere(){};
	/*Ray - Scene Intersection
	1. Apply inverse transform M^(-1) to ray
		ray directions have homogeneous crood set to 0
	2. Ray surface intersection
	3. transform intersection back to actual coords
		intersection point p transform as Mp
		Normals n transform as M^(-1)n*/
	virtual intersectP intersection(const Ray &ray) const;

private:
	vec3 center;
	float radius;
	mat4 transformobj;
	mat4 inversetransform;
	vec4 transformnormal;
	object obj;
};

#endif