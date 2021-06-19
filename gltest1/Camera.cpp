#include <iostream>
#include<GL/glut.h>
#include <math.h>
#include "Camera.h"


Camera::Camera()
{
	mMoveLeft = false;
	mMoveRight = false;
	mForward = false;
	mBackward = false;

}
void Camera::Set(const Vector3 &p, const Vector3 &c, const Vector3 &u) {
	mPosition = p;
	mCenter = c;
	mUp = u;
}

void Camera::Update(float delta_time) {
	//update camera
	float speed = 50.0f;
	Vector3 forward_direction = mCenter - mPosition;
	forward_direction.Normalize();
	Vector3 right_direction = Cross(forward_direction, mUp);
	right_direction.Normalize();
	if (mMoveLeft) {
		Vector3 delta = right_direction * speed*delta_time;
		mPosition = mPosition - delta;
		mCenter = mCenter - delta;
		mMoveLeft = false;
	}
	if (mMoveRight) {
		Vector3 delta = right_direction * speed*delta_time;
		mPosition = mPosition + delta;
		mCenter = mCenter + delta;
		mMoveRight = false;
	}
	if (mForward) {
		//std::cout << "ǰ��";
		Vector3 delta = forward_direction * speed*delta_time;
		mPosition = mPosition + delta;
		mCenter = mCenter + delta;
		mForward = false;
	}
	if (mBackward) {
		Vector3 delta = forward_direction * speed*delta_time;
		mPosition = mPosition - delta;
		mCenter = mCenter - delta;
		mBackward = false;
	}

	//������׶���Χ��
	float obb_zlen = (far - near) / 2.0f;//half_width
	this->obb.c = mPosition + forward_direction * (obb_zlen);
	float obb_ylen = (far - near)*tan((fovy / 360.0f)*3.14);
	float obb_xlen = (mViewportWidth / mViewportHeight)*obb_ylen;
	this->obb.u[0] = forward_direction;
	this->obb.u[1] = this->mUp;
	this->obb.u[2] = right_direction;
	this->obb.e = Vector3(obb_xlen, obb_ylen, obb_zlen);



	//�Ƚ�ģ���ӿھ����Ϊ��λ���ٰڷ������
	glLoadIdentity();
	//std::cout << mPosition.z;
	gluLookAt(mPosition.x, mPosition.y, mPosition.z,
		mCenter.x, mCenter.y, mCenter.z,
		mUp.x, mUp.y, mUp.z);//ǰ��������������ڷ�λ�ã���3�������ӵ�����λ�ã����3��ͷ��
}

void Camera::Pitch(float angle) {
	Vector3 view_direction = mCenter - mPosition;
	view_direction.Normalize();
	Vector3 right_direction = Cross(view_direction, mUp);//y'��z'��˳�x��
	right_direction.Normalize();
	RotateView(angle, right_direction.x, right_direction.y, right_direction.z);//����x'����ת
}
void Camera::Yaw(float angle) {
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}
void Camera::RotateView(float angle, float x, float y, float z) {
	Vector3 view_direction = mCenter - mPosition;
	Vector3 new_view_direction(0.0f, 0.0f, 0.0f);
	float C = cosf(angle);
	float S = sinf(angle);
	Vector3 tempX(C + x * x*(1 - C), x*y*(1 - C) - z * S, x*z*(1 - C) + y * S);//�����һ��
	new_view_direction.x = Dot(tempX, view_direction);
	Vector3 tempY(x*y*(1 - C) + z * S, C + y * y*(1 - C), y*z*(1 - C) - x * S);//����ڶ���
	new_view_direction.y = Dot(tempY, view_direction);
	Vector3 tempZ(x*z*(1 - C) - y * S, y*z*(1 - C) + x * S, C + z * z*(1 - C));//���������
	new_view_direction.z = Dot(tempZ, view_direction);
	mCenter = mPosition + new_view_direction;//�µ��ӵ�
}

void Camera::SwitchTo2D()
{
	glMatrixMode(GL_PROJECTION);//ѡ�и�ͶӰ����
	glLoadIdentity();//��Ҫ©�������һֱ��������ľ���
	gluOrtho2D(-mViewportWidth / 2.0f, mViewportWidth / 2.0f, -mViewportHeight / 2.0f, mViewportHeight / 2.0f);//Ҫ����2
	gluPerspective(45.0f, mViewportWidth / mViewportHeight, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Camera::SwitchTo3D()
{
	glMatrixMode(GL_PROJECTION);//ѡ�и�ͶӰ����
	glLoadIdentity();//��Ҫ©�������һֱ��������ľ���
	gluPerspective(fovy, mViewportWidth / mViewportHeight, near, far);//���д������ڶ�����׶����ֱ�ӽǣ���߱ȣ�zNear��ʾ���ü��浽�۾��ľ��룬zFar��ʾԶ�ü��浽�۾��ľ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//Ҳ����˵��������ǰ�����˶��ٴξ���任���ڸ�����ִ�к󣬵�ǰ������ָ���һ����λ���󣬼��൱��û�н����κξ���任״̬��
}
