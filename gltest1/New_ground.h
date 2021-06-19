#pragma once
#include <vector>
#include "Noise.h"
#include "Vector3.h"
#include "block.h"
#include "Light.h"

#define MAX_GROUND_LEN 300
#define LOW_HEIGHT 4

extern void add_block2scene(Block &b);

class New_ground
{
public:
	Block* ground_block=new Block[MAX_GROUND_LEN*MAX_GROUND_LEN+1];//��������
	int index = 0;//���÷���ָ��
	double ground_height[MAX_GROUND_LEN][MAX_GROUND_LEN];//������Ϣ
	Perlin noise;//��������
	Vector3 position_start;//���½���ʼλ��(��������)
	float block_len;
	int edge_len;//�߳�����������
	Material* material;
	void Init(const Vector3&position_start,const float &block_len,const int&edge_len ,Material* material);
	void Draw();
	

};