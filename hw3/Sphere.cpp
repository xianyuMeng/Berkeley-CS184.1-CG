#include "Sphere.h"


sphere::sphere(const vec3 &center,
	const float radius,
	const mat4 &transformobj,
	const object &obj) :center(center), radius(radius), transformobj(transformobj), obj(obj) {
		mat4 inversetransform = inverse(transformobj);
	}

intersectP sphere::intersection(const Ray &ray)const{
	/*Ray - Scene Intersection
	1. Apply inverse transform M^(-1) to ray
	ray directions have homogeneous crood set to 0
	2. Ray surface intersection
	3. transform intersection back to actual coords
	intersection point p transform as Mp
	Normals n transform as M^(-1)n*/
	vec4 InvDirection = inversetransform * vec4(ray.direction, 0);
	vec4 InvPos = inversetransform * vec4(ray.pos, 0);
	InvDirection = normalize(InvDirection);
	intersectP ret;
	ret.obj = obj;
	
	vec3 PosCen = vec3(InvPos.x - center.x, InvPos.y - center.y, InvPos.z - center.z);
	//solve quadratic equation for t.
	double A = Transform::dot(vec3(InvDirection.x, InvDirection.y, InvDirection.z), vec3(InvDirection.x, InvDirection.y, InvDirection.z));
	double B = 2 * Transform::dot(vec3(InvDirection.x, InvDirection.y, InvDirection.z), PosCen);
	double C = Transform::dot(PosCen, PosCen) - radius * radius;
	double delta = B * B - 4 * A * C;
	
	
	
	if (delta <= 0.0f){
		double t = -B / (2 * A);
		vec4 HitP = InvPos + t * InvDirection;
		float product = Transform::dot(vec3(HitP.x - center.x, HitP.y - center.y, HitP.z - center.z), vec3(InvDirection.x, InvDirection.y, InvDirection.z));
		if (abs(product) <= 0.01f){
			//dot production of normal and direction is 0.
			//double root.
			ret.tHit = -B / (2 * A);
			ret.intersectPoint = transformobj * HitP;
			ret.normal = normalize(inversetransform * vec4(HitP.x - center.x, HitP.y - center.y, HitP.z - center.z, 0));
		}
		else{
			//two complex roots: no intersection.
			return ret;
		}
	}
	else{
		if (abs(Transform::dot(PosCen, PosCen)) <= radius){
			//ray origin inside the sphere: one positive root and one negetive root.
			ret.tHit = (-B + sqrt(delta)) / (2 * A);
			vec4 HitP = InvPos + ret.tHit * InvDirection;
			vec4 HittoCen = vec4(HitP.x - center.x, HitP.y - center.y, HitP.z - center.z, 0);
			ret.normal = normalize(inversetransform * HittoCen);
			ret.intersectPoint = transformobj * (HitP);
		}
		else{
			//two real positive roots:pick smaller one.
			ret.tHit = (-B - sqrt(delta)) / (2 * A);
			vec4 HitP = InvPos + ret.tHit * InvDirection;
			vec4 HittoCen = vec4(HitP.x - center.x, HitP.y - center.y, HitP.z - center.z, 0);
			ret.normal = normalize(inversetransform * HittoCen);
			ret.intersectPoint = transformobj * HitP;
		}
	}
}