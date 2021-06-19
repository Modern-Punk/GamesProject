#include <math.h>
#include "Vector3.h"
Vector3 Vector3::operator*(float f)const {
	return Vector3(x*f, y*f, z*f);
}
Vector3 Vector3::operator/(float f)const {
	return Vector3(x / f, y / f, z / f);
}
Vector3 Vector3::operator*=(float f) {
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
Vector3 Vector3::operator/=(float f) {
	x /= f;
	y /= f;
	z /= f;
	return *this;
}


void Vector3::operator=(const Vector3 &v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 operator+(const Vector3&l, const Vector3&r) {
	return Vector3(l.x + r.x, l.y + r.y, l.z + r.z);
}

Vector3 operator-(const Vector3&l, const Vector3&r) {
	return Vector3(l.x - r.x, l.y - r.y, l.z - r.z);
}

float Dot(const Vector3& l, const Vector3 &r) {
	return l.x*r.x + l.y*r.y + l.z*r.z;
}

Vector3 Cross(const Vector3 &l, const Vector3 &r) {
	return Vector3(l.y*r.z - l.z*r.y, l.z*r.x - l.x*r.z, l.x*r.y - l.y*r.x);
}

float Vector3::Magnitude() {
	return sqrtf(Dot(*this, *this));
}

void Vector3::Normalize() {
	float len = Magnitude();
	*this /= len;
}
Vector3 RotateVector(const Vector3 &origin,float angle, float x, float y, float z) {
	Vector3 new_direction(0.0f, 0.0f, 0.0f);
	float C = cosf(angle);
	float S = sinf(angle);
	Vector3 tempX(C + x * x*(1 - C), x*y*(1 - C) - z * S, x*z*(1 - C) + y * S);//矩阵第一行
	new_direction.x = Dot(tempX, origin);
	Vector3 tempY(x*y*(1 - C) + z * S, C + y * y*(1 - C), y*z*(1 - C) - x * S);//矩阵第二行
	new_direction.y = Dot(tempY, origin);
	Vector3 tempZ(x*z*(1 - C) - y * S, y*z*(1 - C) + x * S, C + z * z*(1 - C));//矩阵第三行
	new_direction.z = Dot(tempZ, origin);
	return new_direction;
}


