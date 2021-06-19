#pragma once
#ifndef _OBB_H
#include <math.h>
#include "Vector3.h"
#define EPSILON 1e-4f
typedef struct
{
	Vector3 c;
	Vector3 u[3];//3����ķ�������
	Vector3 e;//3����ĳ���,halfwidth
}OBB;

int TestOBBOBB(OBB &a, OBB &b);
#endif // !_OBB_H

