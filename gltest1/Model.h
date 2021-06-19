#pragma once
#include <stdio.h>
#include "light.h"
struct VertexData {
	float mPosition[3];//����û���������
	float mTexcoord[2];
	float mNormal[3];
};


class Model {
public:
	VertexData* mVertexes;//��Ӧ����face�еĵ�

	unsigned int* mIndexes;//ÿ3����֯��һ��������
	int mIndexCount;//mIndexes�Ĵ�С
	Material* mMaterial;//����
	void Init(const char* path);
	void Draw();
	void SetMaterial(Material*mat) { mMaterial = mat; }
};
