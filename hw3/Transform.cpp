// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	mat3 ret;
	// YOUR CODE FOR HW2 HERE
	// Please implement this.  Likely the same as in HW 1.
	const double theta = degrees*pi / 180.0;
	glm::mat3 I(cos(theta));
	glm::mat3 Astar = glm::transpose(mat3(0.0, -axis.z, axis.y,
		axis.z, 0.0, -axis.x,
		-axis.y, axis.x, 0.0));
	for (size_t i = 0; i != 3; ++i){
		for (size_t j = 0; j != 3; ++j){
			ret[i][j] = I[i][j] + sin(theta) * Astar[i][j] + (1 - cos(theta)) * axis[i] * axis[j];
		}
	}
	return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.
	glm::mat3 Rotation = Transform::rotate(degrees, up);
	eye = Rotation * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE 
	// Likely the same as in HW 1.
	glm::vec3 orthogonal = glm::normalize(glm::cross(eye, up));
	glm::mat3 Rotation = Transform::rotate(degrees, orthogonal);
	up = Rotation * up;
	eye = Rotation * eye;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.
	glm::mat4 ret;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 look;
	glm::vec3 u, v;
	glm::vec3 w = glm::normalize(eye - center);
	glm::vec3 b = glm::normalize(up);
	u = glm::normalize(glm::cross(b, w));
	v = glm::cross(w, u);
	rotation = mat4(u.x, u.y, u.z, 0,
		v.x, v.y, v.z, 0,
		w.x, w.y, w.z, 0,
		0, 0, 0, 1);
	translation = mat4(1, 0, 0, -eye.x,
		0, 1, 0, -eye.y,
		0, 0, 1, -eye.z,
		0, 0, 0, 1);
	rotation = glm::transpose(rotation);
	translation = glm::transpose(translation);
	ret = rotation * translation;
	return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well
	const float theta = fovy / 2 * pi / 180.0;
	const float d = cos(theta) / sin(theta);
	glm::mat4 ret(0.0);
	ret[0][0] = d / aspect;
	ret[1][1] = d;
	ret[2][2] = -(zFar + zNear) / (zFar - zNear);
	ret[2][3] = -2 * zFar * zNear / (zFar - zNear);
	ret[3][2] = -1;
	return glm::transpose(ret);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// Implement scaling
	ret[0][0] = sx;
	ret[1][1] = sy;
	ret[2][2] = sz;
	ret[3][3] = 1;
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	//mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	glm::mat4 ret(1.0);
	ret[3][0] = tx;
	ret[3][1] = ty;
	ret[3][2] = tz;
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}

vec3 Transform::cross(const vec3 &vec1, const vec3 &vec2){
	vec3 ret = vec3(vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z  * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x);
	return ret;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
