#ifndef _INCLUDEDIRECTIONALLIGHT
#define _INCLUDEDIRECTIONALLIGHT
#include "Light.h"
class DirectionalLight : public light{
public:
	DirectionalLight(const vec3 &direction, const vec3 &color, const vec3 &a) : direction(direction), light(color, a){};
	virtual ~ DirectionalLight(){};
	virtual Ray GenerateRay(const vec3 &HitPoint, float *t){
		*t = 1000000.0f;
		return Ray(direction, HitPoint, 0.0f, *t);
	}

private:
	vec3 direction;
};
#endif