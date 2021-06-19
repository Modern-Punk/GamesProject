#include "OBB.h"

int TestOBBOBB(OBB &a, OBB &b)
{
	float ra, rb;
	float R[3][3];
	float AbsR[3][3];


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = Dot(a.u[i], b.u[j]);//R[i][j]为缓存，代表a的第i条轴与b的第j条轴的点积
		}
	}

	Vector3 t = b.c - a.c;
	t = Vector3(Dot(t, a.u[0]), Dot(t, a.u[1]), Dot(t, a.u[2]));//T向量在a的坐标系下的投影，t[0]代表的是在x轴下的投影的长度...

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
		}
	}

	//Test axes L=A0,L=A1,L=A2
	for (int i = 0; i < 3; i++)
	{
		ra = a.e[i];//ra
		rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2];//rb
		if (fabsf(t[i]) > ra + rb)
		{
			return 0;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[i][2];
		rb = b.e[i];
		if (fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb)
		{
			return 0;
		}
	}

	ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0];
	rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1];
	if (fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[1] * AbsR[2][1] + a.e[2] * AbsR[1][1];
	rb = b.e[0] * AbsR[0][2] + b.e[2] * AbsR[0][0];
	if (fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2];
	rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0];
	if (fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
	rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
	if (fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1];
	rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0];
	if (fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2];
	rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0];
	if (fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0];
	rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1];
	if (fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1];
	rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0];
	if (fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb)
	{
		return 0;
	}

	ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2];
	rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0];
	if (fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb)
	{
		return 0;
	}

	return 1;
}