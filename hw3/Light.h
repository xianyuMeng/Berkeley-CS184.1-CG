#ifndef _INCLUDELIGHTHEADER
#define _INCLUDELIGHTHEADER
#include "Ray.h"
using namespace glm;
class light{
public:
	light(const glm::vec3 &color) :color(color){};
	virtual ~light(){};
	virtual Ray GenerateRay(const glm::vec3 &HitPoint, float *t) = 0;
	glm::vec3 color;
};

#endif