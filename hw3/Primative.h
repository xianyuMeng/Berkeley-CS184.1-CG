#ifndef _INCLUDEPRIMATIVEHEADER
#define _INCLUDEPRIMATIVEHEADER
#include "Ray.h"
#include "Variable.h"
#include "Transform.h"
class primative{
public:
	primative(){}
	~primative(){}

	virtual intersectP intersection(const Ray &ray) const = 0;
};

#endif