#include "Triangle.h"

triangle::triangle(const vec3 &A, const vec3 &B, const vec3 &C, const object &obj) :A(A), B(B), C(C), obj(obj) {
	vec3 normal = normalize(cross(C - A, B - A));
}


intersectP triangle::intersection(const Ray &ray) const {
	/***************************************************************
	 * http://stackoverflow.com/questions/13655457/raytracing-ray-triangle-intersection 
	 * see the link above to check if point is inside the triangle 
	 * it may have bugs in this piece of code
	 *
	 ****************************************************************/

	float t = (Transform::dot(A, normal) - Transform::dot(ray.pos, normal)) / (Transform::dot(ray.direction, normal));
	intersectP ret;
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
	ret.normal = vec4(normal, 0);
	ret.intersectPoint = vec4(ray.pos + ray.direction * ret.tHit, 0);
	return ret;
}