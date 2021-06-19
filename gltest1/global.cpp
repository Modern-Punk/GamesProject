#include <map>
#include <vector>
#include "Block.h"
#define MAX_ID 0X3f3f3f




//ÿһ��Ҫ���Ƶ������Ӧһ��id����Ӧδ�����id
long long obj_id=0;

bool draw_once[MAX_ID] = {false};//��Ϊ���ܶ��AABB������ͬһ�����壬�����ظ�����һ������

void clear_draw_once()
{
	for (long long i = 0; i < obj_id; i++)
	{
		draw_once[i] = false;
	}
}




/************��ͬ���͵�������id��ӳ��************/
//BLOCKӳ��
std::map<long long, Block> id2block;


/************����id��ӳ�䣬��������뵽�˲�����������************/
//BLOCK����
void add_block2scene(Block &b)
{
	b.id = obj_id;
	id2block[obj_id] = b;
	obj_id++;
}

float tran_angle(float angle)//�Ƕ�ת����
{
	return (angle / 180.0f)*3.14;
}

/************��ײ���************/
//��Ҫ��ײ����Block������
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
		printf("֡��Ϊ��%s\n", s);
	}
}




