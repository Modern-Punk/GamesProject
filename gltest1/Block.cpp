#include <iostream>
#include <map>
#include "Block.h"
void Block::Init(const Vector3 &center_position,const Vector3 &x_direction,const Vector3 &z_direction,const float &len,Material* material)
{
	this->center_position = center_position;
	this->x_direction = x_direction;
	this->z_direction = z_direction;

	this->len = len;
	this->material = material;

	//面集，左，上，后，右，前，下
	texture[0].Init("my_texture/soil.bmp");
	texture[1].Init("my_texture/grass.bmp");
	texture[2].Init("my_texture/soil.bmp");
	texture[3].Init("my_texture/soil.bmp");
	texture[4].Init("my_texture/soil.bmp");
	texture[5].Init("my_texture/soil.bmp");



}

void Block::Init_2(const Vector3 &center_position, const Vector3 &x_direction, const Vector3 &z_direction, const float &len, Material* material)
{
	this->center_position = center_position;
	this->x_direction = x_direction;
	this->z_direction = z_direction;

	this->len = len;
	this->material = material;

	//面集，左，上，后，右，前，下
	texture[0].Init("my_texture/boom.bmp");
	texture[1].Init("my_texture/boom.bmp");
	texture[2].Init("my_texture/boom.bmp");
	texture[3].Init("my_texture/boom.bmp");
	texture[4].Init("my_texture/boom.bmp");
	texture[5].Init("my_texture/boom.bmp");




}

void Block::Update()
{
	

	this->y_direction = Cross(z_direction, x_direction);
	this->x_direction.Normalize();
	this->z_direction.Normalize();
	this->y_direction.Normalize();


	float t = (this->len) / 2.0;
	point[0] = x_direction * (-t) + y_direction * (-t) + z_direction * t + center_position;
	point[1] = x_direction * (-t) + y_direction * (-t) + z_direction * (-t) + center_position;
	point[2] = x_direction * (-t) + y_direction * (t)+z_direction * (-t) + center_position;
	point[3] = x_direction * (-t) + y_direction * (t)+z_direction * (t)+center_position;
	point[4] = x_direction * (t) + y_direction * (t) + z_direction * (t)+center_position;
	point[5] = x_direction * (t)+ y_direction * (t)+z_direction * (-t) + center_position;
	point[6] = x_direction * (t)+ y_direction * (-t)+z_direction * (-t) + center_position;
	point[7] = x_direction * (t)+ y_direction * (-t)+z_direction * (t)+center_position;


	//6个面的法线
	normal_dir[0][0] = -x_direction.x;
	normal_dir[0][1] = -x_direction.y;
	normal_dir[0][2] = -x_direction.z;

	normal_dir[1][0] = y_direction.x;
	normal_dir[1][1] = y_direction.y;
	normal_dir[1][2] = y_direction.z;

	normal_dir[2][0] = -z_direction.x;
	normal_dir[2][1] = -z_direction.y;
	normal_dir[2][2] = -z_direction.z;

	normal_dir[3][0] = x_direction.x;
	normal_dir[3][1] = x_direction.y;
	normal_dir[3][2] = x_direction.z;

	normal_dir[4][0] = z_direction.x;
	normal_dir[4][1] = z_direction.y;
	normal_dir[4][2] = z_direction.z;

	normal_dir[5][0] = -y_direction.x;
	normal_dir[5][1] = -y_direction.y;
	normal_dir[5][2] = -y_direction.z;

	

	
}
void Block::Draw()
{
	material->Update();
	for (int i = 0; i < 6; i++)
	{
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[i].mTextureID);
		//glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0f,0.0f);
		glNormal3fv(normal_dir[i]);
		glVertex3f(point[flat[i][0]].x, point[flat[i][0]].y, point[flat[i][0]].z);
		glTexCoord2f(1.0f, 0.0f);
		glNormal3fv(normal_dir[i]);
		glVertex3f(point[flat[i][1]].x, point[flat[i][1]].y, point[flat[i][1]].z);
		glTexCoord2f(0.0f, 1.0f);
		glNormal3fv(normal_dir[i]);
		glVertex3f(point[flat[i][3]].x, point[flat[i][3]].y, point[flat[i][3]].z);
		glTexCoord2f(1.0f, 1.0f);
		glNormal3fv(normal_dir[i]);
		glVertex3f(point[flat[i][2]].x, point[flat[i][2]].y, point[flat[i][2]].z);	
		//std::cout <<"x:"<<normal_dir[i][0]<<"y:"<< normal_dir[i][1]<<"z:"<< normal_dir[i][2];
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnd();
	}
}
void Block::set_pos_dir(Vector3 center_position, Vector3 x_direction, Vector3 z_direction)
{
	this->center_position = center_position;
	this->x_direction = x_direction;
	this->z_direction = z_direction;
}
void Block::operator=(const Block& b)
{
	this->len = b.len;
	this->center_position = b.center_position;
	this->x_direction = b.x_direction;
	this->z_direction = b.z_direction;
	this->y_direction = b.y_direction;
	for (int i = 0; i < 8; i++)
	{
		this->point[i] = b.point[i];
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->normal_dir[i][j] = b.normal_dir[i][j];
		}
	}
	this->material = b.material;
	for (int i = 0; i < 6; i++)
	{
		this->texture[i].mTextureID = b.texture[i].mTextureID;//复制纹理GPU的ID
	}

}







