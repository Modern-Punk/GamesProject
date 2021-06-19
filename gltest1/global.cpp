#include <map>
#include <vector>
#include "Block.h"
#define MAX_ID 0X3f3f3f




//每一个要绘制的物体对应一个id，对应未分配的id
long long obj_id=0;

bool draw_once[MAX_ID] = {false};//因为可能多个AABB包含着同一个物体，避免重复绘制一个物体

void clear_draw_once()
{
	for (long long i = 0; i < obj_id; i++)
	{
		draw_once[i] = false;
	}
}




/************不同类型的物体与id的映射************/
//BLOCK映射
std::map<long long, Block> id2block;


/************操作id与映射，将物体加入到八叉树管理器中************/
//BLOCK管理
void add_block2scene(Block &b)
{
	b.id = obj_id;
	id2block[obj_id] = b;
	obj_id++;
}

float tran_angle(float angle)//角度转弧度
{
	return (angle / 180.0f)*3.14;
}

/************碰撞相关************/
//需要碰撞检测的Block类物体
std::vector<Block> collision_Block_list;

int frame = 0, time = 0, timebase = 0;
void ShowFrameRate()
{
	char s[100] = { 0 };
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f",
			frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
		printf("帧率为：%s\n", s);
	}
}




