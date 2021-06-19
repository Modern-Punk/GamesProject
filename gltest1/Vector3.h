#pragma once
#include <stdio.h>
class Vector3
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vector3() { x = 0.0f; y = 0.0f; z = 0.0f; }
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const Vector3&v)//拷贝构造函数
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 operator*(float f)const;//与浮点数相乘
	Vector3 operator/(float f)const;
	Vector3 operator*=(float f);//末尾不要加const,因为会改变数据成员的内容
	Vector3 operator/=(float f);
	void operator=(const Vector3 &v);
	float operator[](int index) const { return v[index]; }
	float Magnitude();//向量的长度
	void Normalize();//归一化
};
Vector3 operator+(const Vector3&l, const Vector3&r);
Vector3 operator-(const Vector3&l, const Vector3&r);
float Dot(const Vector3&l, const Vector3&r);//点积点出来的是浮点型
Vector3 Cross(const Vector3&l, const Vector3&r);//叉积出来的是向量
Vector3 RotateVector(const Vector3 &origin, float angle, float x, float y, float z);





