#pragma once
#include "Vector3.h"
#include "Light.h"
#include "texture.h"
//#include "Scene_Manager.h"

class Block
{
public:
	long long id;
	float len;
	bool speed_enable = false;//������ײ
	float speed=0;
	float a;//���ٶ�
	float k;//����ϵ��

	Vector3 center_position;
	Vector3 x_direction;
	Vector3 z_direction;
	Vector3 y_direction;
	Vector3 point[8];//�㼯,��������ϵ
	int flat[6][4] = {
		{0,1,2,3},{3,4,5,2},{1,6,5,2},{7,6,5,4},{0,7,4,3},{0,7,6,1}	
	};//�漯�����ϣ����ң�ǰ����
	float normal_dir[6][3];
	Material *material;
	Texture texture[6];
	void Init(const Vector3 &center_position, const Vector3 &x_direction, const Vector3 &z_direction, const float &len, Material* material);
	void Init_2(const Vector3 &center_position, const Vector3 &x_direction, const Vector3 &z_direction, const float &len, Material* material);

	void Update();//Init֮��Ϳ���Ӧ��
	void Draw();
	void set_pos_dir(Vector3 center_position, Vector3 x_direction, Vector3 z_direction);
	void operator=(const Block &b);

	void gravity()
	{
		
	}



};