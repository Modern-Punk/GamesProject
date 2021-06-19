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
		//std::cout << "前进";
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

	//更新视锥体包围盒
	float obb_zlen = (far - near) / 2.0f;//half_width
	this->obb.c = mPosition + forward_direction * (obb_zlen);
	float obb_ylen = (far - near)*tan((fovy / 360.0f)*3.14);
	float obb_xlen = (mViewportWidth / mViewportHeight)*obb_ylen;
	this->obb.u[0] = forward_direction;
	this->obb.u[1] = this->mUp;
	this->obb.u[2] = right_direction;
	this->obb.e = Vector3(obb_xlen, obb_ylen, obb_zlen);



	//先将模型视口矩阵变为单位阵，再摆放摄像机
	glLoadIdentity();
	//std::cout << mPosition.z;
	gluLookAt(mPosition.x, mPosition.y, mPosition.z,
		mCenter.x, mCenter.y, mCenter.z,
		mUp.x, mUp.y, mUp.z);//前三个设置摄像机摆放位置，再3个设置视点中心位置，最后3个头顶
}

void Camera::Pitch(float angle) {
	Vector3 view_direction = mCenter - mPosition;
	view_direction.Normalize();
	Vector3 right_direction = Cross(view_direction, mUp);//y'和z'叉乘出x’
	right_direction.Normalize();
	RotateView(angle, right_direction.x, right_direction.y, right_direction.z);//沿着x'轴旋转
}
void Camera::Yaw(float angle) {
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}
void Camera::RotateView(float angle, float x, float y, float z) {
	Vector3 view_direction = mCenter - mPosition;
	Vector3 new_view_direction(0.0f, 0.0f, 0.0f);
	float C = cosf(angle);
	float S = sinf(angle);
	Vector3 tempX(C + x * x*(1 - C), x*y*(1 - C) - z * S, x*z*(1 - C) + y * S);//矩阵第一行
	new_view_direction.x = Dot(tempX, view_direction);
	Vector3 tempY(x*y*(1 - C) + z * S, C + y * y*(1 - C), y*z*(1 - C) - x * S);//矩阵第二行
	new_view_direction.y = Dot(tempY, view_direction);
	Vector3 tempZ(x*z*(1 - C) - y * S, y*z*(1 - C) + x * S, C + z * z*(1 - C));//矩阵第三行
	new_view_direction.z = Dot(tempZ, view_direction);
	mCenter = mPosition + new_view_direction;//新的视点
}

void Camera::SwitchTo2D()
{
	glMatrixMode(GL_PROJECTION);//选中该投影矩阵
	glLoadIdentity();//不要漏，否则会一直乘以下面的矩阵
	gluOrtho2D(-mViewportWidth / 2.0f, mViewportWidth / 2.0f, -mViewportHeight / 2.0f, mViewportHeight / 2.0f);//要除以2
	gluPerspective(45.0f, mViewportWidth / mViewportHeight, near, far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Camera::SwitchTo3D()
{
	glMatrixMode(GL_PROJECTION);//选中该投影矩阵
	glLoadIdentity();//不要漏，否则会一直乘以下面的矩阵
	gluPerspective(fovy, mViewportWidth / mViewportHeight, near, far);//本行代码用于定义视锥。垂直视角，宽高比，zNear表示近裁剪面到眼睛的距离，zFar表示远裁剪面到眼睛的距离
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//也就是说，无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，即相当于没有进行任何矩阵变换状态。
}
