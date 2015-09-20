#ifndef _INCLUDETRIANGLEHEADER
#define _INCLUDETRIANGLEHEADER
#include "Primative.h"
class triangle : public primative{
public:
	triangle(const vec3 &A, const vec3 &B, const vec3 &C, const object &obj);
	virtual ~triangle(){};

	virtual intersectP intersection(const Ray &ray) const;
private:
	vec3 A, B, C;
	vec3 normal;
	float t;
	object obj;
};

#endif