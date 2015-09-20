#include "Camera.h"
#include "Transform.h"
using namespace glm;
camera::camera(const glm::vec3 &eye,
	const glm::vec3 &center,
	const glm::vec3 &up,
	float fovy,
	int height,
	int width) : theta(fovy / 2.0f *pi / 180.0f), height(height), width(width){
	//creat a coordinate frame for the camera
	/*If P1 is normalized, then t equals the distance of the ray from origin in World Coordinates, else it is just a multiple of P1,
	so we want to normalize P1.
	Note that many of the intersection computations require the solution of the quadratic equation.*/
	w = glm::normalize(eye - center);
	u = glm::normalize(Transform::cross(up, w));
	v = glm::cross(w, u);
}

Ray camera::GenerateRay(int i, int j){
	float alpha = tan(theta) * (j - (width / 2)) / (width / 2);
	float beta = tan(theta) * (i - (height / 2)) / (height / 2);
	glm::vec3 direction = normalize(alpha * u + beta * v - w);
	return Ray(direction, eye, t_min, t_max);
}