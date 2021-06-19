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
	bool speed_enable = false;//用于碰撞
	float speed=0;
	float a;//加速度
	float k;//弹性系数

	Vector3 center_position;
	Vector3 x_direction;
	Vector3 z_direction;
	Vector3 y_direction;
	Vector3 point[8];//点集,世界坐标系
	int flat[6][4] = {
		{0,1,2,3},{3,4,5,2},{1,6,5,2},{7,6,5,4},{0,7,4,3},{0,7,6,1}	
	};//面集，左，上，后，右，前，下
	float normal_dir[6][3];
	Material *material;
	Texture texture[6];
	void Init(const Vector3 &center_position, const Vector3 &x_direction, const Vector3 &z_direction, const float &len, Material* material);
	void Init_2(const Vector3 &center_position, const Vector3 &x_direction, const Vector3 &z_direction, const float &len, Material* material);

	void Update();//Init之后就可以应用
	void Draw();
	void set_pos_dir(Vector3 center_position, Vector3 x_direction, Vector3 z_direction);
	void operator=(const Block &b);

	void gravity()
	{
		
	}



};