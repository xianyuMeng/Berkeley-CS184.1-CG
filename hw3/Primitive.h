#ifndef _INCLUDEPrimitiveHEADER
#define _INCLUDEPrimitiveHEADER
#include "Ray.h"
#include "Variable.h"
#include "Transform.h"
class Primitive{
public:
	Primitive(){}
	~Primitive(){}

	virtual intersectP intersection(const Ray &ray) const = 0;
};

#endif