#ifndef _INCLUDEPOINTLIGHTHEADER
#define _INCLUDEPOINTLIGHTHEADER
#include "Light.h"
class PointLight : public light{
	//maintian access levels for the related members.
	using light::color;
	/*the attenuation model applies only to point lights, not directional lights
	c0, c1, c2 are the constant, linear and quadratic attenuation terms
	physical point light (0,0,1), while default (1,0,0)*/
	PointLight(const vec3 &color, const vec3 &position, const vec3 &attenuation) :
		light(color), position(position), attenuation(attenuation){};
	virtual ~ PointLight(){};
	virtual Ray GenerateRay(const vec3 &HitPoint, float *t);

private:
	vec3 position;
	vec3 attenuation;
};

#endif