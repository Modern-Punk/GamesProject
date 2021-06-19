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
	Vector3(const Vector3&v)//�������캯��
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 operator*(float f)const;//�븡�������
	Vector3 operator/(float f)const;
	Vector3 operator*=(float f);//ĩβ��Ҫ��const,��Ϊ��ı����ݳ�Ա������
	Vector3 operator/=(float f);
	void operator=(const Vector3 &v);
	float operator[](int index) const { return v[index]; }
	float Magnitude();//�����ĳ���
	void Normalize();//��һ��
};
Vector3 operator+(const Vector3&l, const Vector3&r);
Vector3 operator-(const Vector3&l, const Vector3&r);
float Dot(const Vector3&l, const Vector3&r);//�����������Ǹ�����
Vector3 Cross(const Vector3&l, const Vector3&r);//���������������
Vector3 RotateVector(const Vector3 &origin, float angle, float x, float y, float z);





