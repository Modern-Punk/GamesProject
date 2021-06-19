#pragma once
#ifndef _OBB_H
#include <math.h>
#include "Vector3.h"
#define EPSILON 1e-4f
typedef struct
{
	Vector3 c;
	Vector3 u[3];//3个轴的方向向量
	Vector3 e;//3个轴的长度,halfwidth
}OBB;

int TestOBBOBB(OBB &a, OBB &b);
#endif // !_OBB_H

