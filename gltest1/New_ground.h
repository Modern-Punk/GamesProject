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
	Block* ground_block=new Block[MAX_GROUND_LEN*MAX_GROUND_LEN+1];//方块数据
	int index = 0;//可用方块指针
	double ground_height[MAX_GROUND_LEN][MAX_GROUND_LEN];//地形信息
	Perlin noise;//柏林噪声
	Vector3 position_start;//左下角起始位置(方块中心)
	float block_len;
	int edge_len;//边长（方格数）
	Material* material;
	void Init(const Vector3&position_start,const float &block_len,const int&edge_len ,Material* material);
	void Draw();
	

};