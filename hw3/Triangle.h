#ifndef _INCLUDETriangleHEADER
#define _INCLUDETriangleHEADER
#include "Primitive.h"
class Triangle : public Primitive{
public:
	Triangle(const vec3 &A, const vec3 &B, const vec3 &C, const object &obj);
	virtual ~Triangle(){};

	virtual intersectP intersection(const Ray &ray) const;
private:
	vec3 A, B, C;
	vec3 normal;
	float t;
	object obj;
};

#endif