#ifndef _INCLUDELIGHTHEADER
#define _INCLUDELIGHTHEADER
#include "Ray.h"
using namespace glm;
class light{
public:
	light(const glm::vec3 &color, const glm::vec3 &a) :color(color), attenuation(a) {};
	virtual ~light(){};
	virtual Ray GenerateRay(const glm::vec3 &HitPoint, float *t) = 0;
	glm::vec3 color;
	glm::vec3 attenuation;
};

#endif