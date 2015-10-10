#include "Triangle.h"

Triangle::Triangle(const vec3 &A, const vec3 &B, const vec3 &C, const object &obj) :A(A), B(B), C(C), obj(obj) {
	normal = normalize(cross(B - A, C - A));
}


intersectP Triangle::intersection(const Ray &ray) const {
	/***************************************************************
	 * http://stackoverflow.com/questions/13655457/raytracing-ray-Triangle-intersection 
	 * see the link above to check if point is inside the Triangle 
	 * it may have bugs in this piece of code
	 *
	 ****************************************************************/

	float t = (Transform::dot(A, normal) - Transform::dot(ray.pos, normal)) / (Transform::dot(ray.direction, normal));
	intersectP ret;
	ret.tHit = FarFarAway;

	vec3 vec1 = B - A;
	vec3 vec2 = C - A;
	vec3 p = cross(ray.direction, vec2);
	float a = Transform::dot(vec1, p);
	if (t < 0.0000001f){
		return ret;
	}
	float f = 1.0f / a;
	vec3 s = ray.pos - A;
	float u = f * (Transform::dot(s, p));
	if (u <= 0.0f || u >= 1.0f)
		return ret;
	vec3 q = cross(s, vec1);
	float v = f * Transform::dot(ray.direction, q);
	if (v < 0.0f || u + v > 1.0f)
		return ret;
	float tHit = f * Transform::dot(vec2, q);

	ret.tHit = tHit;
	ret.obj = obj;
	ret.normal = normal;
	ret.intersectPoint = ray.pos + ray.direction * ret.tHit;
	return ret;
}