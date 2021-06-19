#pragma once
#include <stdio.h>
#include "light.h"
struct VertexData {
	float mPosition[3];//这里没给齐次坐标
	float mTexcoord[2];
	float mNormal[3];
};


class Model {
public:
	VertexData* mVertexes;//对应的是face中的点

	unsigned int* mIndexes;//每3个组织成一个三角形
	int mIndexCount;//mIndexes的大小
	Material* mMaterial;//材质
	void Init(const char* path);
	void Draw();
	void SetMaterial(Material*mat) { mMaterial = mat; }
};
