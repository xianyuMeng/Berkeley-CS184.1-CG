#include "Sphere.h"
#include "glm\gtc\matrix_inverse.hpp"

Sphere::Sphere(const vec3 &center,
	const float radius,
	const mat4 &transformobj,
	const object &obj) :center(center), radius(radius), transformobj(transformobj), obj(obj) {
		inversetransform = inverse(transformobj);
}

inline vec3 applyMatrix(const mat4 &trans, const vec3 &v) {
	vec4 temp = vec4(v, 1.0f);
	temp = trans * temp;
	temp = temp / temp[3];
	return vec3(temp);
}

intersectP Sphere::intersection(const Ray &ray)const{
	/*Ray - Scene Intersection
	1. Apply inverse transform M^(-1) to ray
	ray directions have homogeneous crood set to 0
	2. Ray surface intersection
	3. transform intersection back to actual coords
	intersection point p transform as Mp
	Normals n transform as M^(-1)n*/
	/*
	ray-sphere intersection Geometry
	see http://www.vis.uky.edu/~ryang/teaching/cs535-2012spr/Lectures/13-RayTracing-II.pdf
	for futher information
	*/
	//vec4 InvDirection = inversetransform * vec4(ray.direction, 0);
	//vec4 InvPos = inversetransform * vec4(ray.pos, 1);
	
	vec3 InvPos = vec4_to_vec3(inversetransform * vec4(ray.pos, 1));
	vec3 InvDirection = normalize(applyMatrix(inversetransform, ray.pos + ray.direction) - InvPos);
	InvDirection = normalize(InvDirection);
	intersectP ret;
	ret.obj = obj;
	ret.tHit = FarFarAway;
	vec3 OC = center - InvPos;
	bool inside = false;
	float OC_square = Transform::dot(OC, OC);
	if (OC_square < radius)
		inside = true;
	//distance from ray_origin to the point closet to sphere_center
	float t_ca = Transform::dot(InvDirection, OC);
	if (t_ca < NEAR && inside == false){
		//the ray does not intersect the sphere
		return ret;
	}
	else {
		//the diatance from the closet point to the sphere's point
		float t_hc_square = pow(radius, 2) - OC_square + pow(t_ca, 2);
		if (t_hc_square < NEAR)
			//no intersection
			return ret;
		else {
			float t_hc = sqrt(t_hc_square);
			if (inside == false){
				//ray_origin is outside the sphere
				float t = t_ca - t_hc;
				vec3 HitPoint = InvPos + t * InvDirection;
				vec3 normal = HitPoint - center;
				ret.intersectPoint = applyMatrix(transformobj, HitPoint);
				ret.tHit = length(ret.intersectPoint - ray.pos);
				ret.normal = inverseTranspose(mat3(transformobj)) * normal;
				ret.normal = normalize(ret.normal);
				return ret;
			}
			else{
				//ray_origin is inside the sphere
				//inside == true
				float t = t_ca + t_hc;
				vec3 HitPoint = InvPos + t * InvDirection;
				vec3 normal = HitPoint - center;
				ret.intersectPoint = applyMatrix(transformobj, HitPoint);
				ret.tHit = length(ret.intersectPoint - ray.pos);
				ret.normal = inverseTranspose(mat3(transformobj)) * normal;
				ret.normal = normalize(ret.normal);
				return ret;
			}
		}
	}

	
	//vec4 InvDirection = inversetransform * vec4(ray.direction, 0);
	//vec4 InvPos = inversetransform * vec4(ray.pos, 1);
	//InvDirection = normalize(InvDirection);
	//intersectP ret;
	//ret.obj = obj;
	//ret.tHit = FarFarAway;
	//vec3 poscen = vec4_to_vec3(InvPos) - center;
	////solve quadratic equation for t.
	//double a = Transform::dot(vec4_to_vec3(InvDirection), vec4_to_vec3(InvDirection));
	//double b = 2 * Transform::dot(vec4_to_vec3(InvDirection), poscen);
	//double c = Transform::dot(poscen, poscen) - radius * radius;
	//double delta = b * b - 4 * a * c;
	//
	//if (abs(delta) <= NEAR){
	//	float t = -b / (2 * a);
	//	vec4 HitP = InvPos + t * InvDirection;
	//	ret.intersectPoint = vec4_to_vec3(transformobj * HitP);
	//	ret.tHit = distance(ret.intersectPoint, ray.pos);
	//	ret.normal = normalize(vec4_to_vec3(inversetransform * vec4(vec4_to_vec3(HitP) - center, 0)));
	//	return ret;
	//}

	//else if (delta < 0.0f){
	//	//two complex roots: no intersection.
	//	return ret;
	//}
	//else{
	//	if (abs(Transform::dot(poscen, poscen)) <= radius){
	//		//ray origin inside the Sphere: one positive root and one negetive root.
	//		float t = (-b + sqrt(delta)) / (2 * a);
	//		/*if (t < NEAR)
	//			return ret;
	//		else {*/
	//		vec4 HitP = InvPos + t * InvDirection;
	//		ret.intersectPoint = vec4_to_vec3(transformobj * HitP);
	//		ret.tHit = distance(ret.intersectPoint, ray.pos);
	//		ret.normal = normalize(vec4_to_vec3(inversetransform * vec4(vec4_to_vec3(HitP) - center, 0)));
	//		return ret;
	//		//}
	//	}
	//	else{
	//		//two real positive roots:pick smaller one.
	//		float t = (-b - sqrt(delta)) / (2 * a);
	//		/*if (t < NEAR){
	//			return ret;
	//		}
	//		else {*/
	//		vec4 HitP = InvPos + t * InvDirection;
	//		ret.intersectPoint = vec4_to_vec3(transformobj * HitP);
	//		ret.tHit = distance(ret.intersectPoint, ray.pos);
	//		ret.normal = normalize(vec4_to_vec3(inversetransform * vec4(vec4_to_vec3(HitP) - center, 0)));
	//		return ret;
	//		/*}*/
	//			
	//	}
	//}

/*
	mat3 normal_mat = inverseTranspose(mat3(transformobj));

	vec3 o = applyMatrix(inversetransform, ray.pos);
	vec3 d = normalize(applyMatrix(inversetransform, ray.pos + ray.direction) - o);

	intersectP ret;
	ret.tHit = FarFarAway;
	ret.obj = obj;

	float r2 = radius * radius;
	vec3 toSphere = center - o;
	float l2 = dot(toSphere, toSphere);

	if (l2 > r2) {
		float d2 = dot(toSphere, d);
		if (d2 <= 0.0f) {
			return ret;
		}

		float thc = r2 - l2 + d2 * d2;
		if (thc <= 0.0f) {
			return ret;
		}

		float thc_sqrt = sqrtf(thc);
		float t_temp = d2 - thc_sqrt;
		if (t_temp > FarFarAway) {
			vec3 hitpoint = o + t_temp * d;
			vec3 normal = normalize(hitpoint - center);
			ret.intersectPoint = applyMatrix(transformobj, hitpoint);
			ret.tHit = length(ret.intersectPoint - ray.pos);
			ret.normal = normalize(normal_mat * normal);
		}
		else {
			t_temp = d2 + thc_sqrt;
			if (t_temp > FarFarAway) {
				vec3 hitpoint = o + t_temp * d;
				vec3 normal = normalize(hitpoint - center);
				ret.intersectPoint = applyMatrix(transformobj, hitpoint);
				ret.tHit = length(ret.intersectPoint - ray.pos);
				ret.normal = normalize(normal_mat * normal);
			}
		}
		return ret;
	}
	else {
		float d2 = dot(toSphere, d);
		float thc = r2 - l2 + d2 * d2;
		float t_temp = sqrtf(thc) + d2;
		if (t_temp > FarFarAway) {
			vec3 hitpoint = o + t_temp * d;
			vec3 normal = normalize(hitpoint - center);
			ret.intersectPoint = applyMatrix(transformobj, hitpoint);
			ret.tHit = length(ret.intersectPoint - ray.pos);
			ret.normal = normalize(normal_mat * normal);
		}
		return ret;
	}
	*/
}