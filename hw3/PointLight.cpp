#include "PointLight.h"

Ray PointLight::GenerateRay(const vec3 &HitPoint, float *t){
	vec3 direction = vec3(position - HitPoint);
	*t = length(direction);
	return Ray(normalize(direction), HitPoint, 0.0f, *t);
}