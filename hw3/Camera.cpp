#include "Camera.h"
#include "Transform.h"

camera::camera(const vec3 &eye,
	const vec3 &center,
	const vec3 &up,
	float fovy,
	int height,
	int width) : theta(fovy / 2.0f *pi / 180.0f), height(height), width(width){
	//creat a coordinate frame for the camera
	w = glm::normalize(eye - center);
	u = glm::normalize(Transform::cross(up, w));
	v = Transform::cross(w, u);
}

Ray camera::GenerateRay(int i, int j){
	float alpha = tan(theta) * (j - (width / 2)) / (width / 2);
	float beta = tan(theta) * (i - (height / 2)) / (height / 2);
	vec3 direction = normalize(alpha * u + beta * v - w);
	return Ray(direction, eye, t_min, t_max);
}