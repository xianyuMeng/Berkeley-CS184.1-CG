
#ifndef _INCLUDERAYHEADER
#define _INCLUDERAYHEADER
#include "glm/glm.hpp"
class Ray{
public:
	Ray(const glm::vec3 &direction, const glm::vec3 &position, float t_min, float t_max) :
		direction(direction), pos(position), t_min(t_min), t_max(t_max){};
	~ Ray() {};
	const glm::vec3 direction;
	const glm::vec3 pos;
	float t_min;
	float t_max;
};

#endif