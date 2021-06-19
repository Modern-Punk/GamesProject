#pragma once
#include <stdio.h>
#include "Vector3.h"
#include "OBB.h"


class Camera
{
public:
	Vector3 mPosition, mCenter, mUp;//位置，视点中心（世界坐标系下的位置？），摄像头顶端朝向
	Vector3 mUp2;
	float mViewportWidth, mViewportHeight;
	float far = 1000.0f;
	float near = 0.1f;
	float fovy = 45.0f;
	OBB obb;//视锥体包围盒
	bool mMoveLeft, mMoveRight, mForward, mBackward;
	Camera();
	void Set(const Vector3 &p, const Vector3 &center, const Vector3 &u);
	void Pitch(float angle);
	void Yaw(float angle);
	void RotateView(float angle, float x, float y, float z);
	void Update(float delta_time);
	void SwitchTo2D();
	void SwitchTo3D();



};


