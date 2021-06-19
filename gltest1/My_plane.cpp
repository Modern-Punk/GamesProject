#include "My_plane.h"
#include "iostream"
void My_plane::init()
{
	this->texture.Init("my_texture/iron.bmp");//放在构造函数会失效
}
My_plane::My_plane()
{


	index[0][0] = 1; index[0][1] = 2; index[0][2] = 0;
	index[1][0] = 2; index[1][1] = 3; index[1][2] = 0;
	index[2][0] = 2; index[2][1] = 6; index[2][2] = 5;
	index[3][0] = 5; index[3][1] = 1; index[3][2] = 2;
	index[4][0] = 4; index[4][1] = 0; index[4][2] = 3;
	index[5][0] = 3; index[5][1] = 7; index[5][2] = 4;
	index[6][0] = 1; index[6][1] = 0; index[6][2] = 4;
	index[7][0] = 4; index[7][1] = 5; index[7][2] = 1;
	index[8][0] = 2; index[8][1] = 3; index[8][2] = 7;
	index[9][0] = 7; index[9][1] = 6; index[9][2] = 2;
	index[10][0] = 5; index[10][1] = 6; index[10][2] = 9;
	index[11][0] = 6; index[11][1] = 10; index[11][2] = 9;
	index[12][0] = 5; index[12][1] = 4; index[12][2] = 9;
	index[13][0] = 4; index[13][1] = 8; index[13][2] = 9;
	index[14][0] = 4; index[14][1] = 8; index[14][2] = 11;
	index[15][0] = 11; index[15][1] = 7; index[15][2] = 4;
	index[16][0] = 6; index[16][1] = 7; index[16][2] = 10;
	index[17][0] = 10; index[17][1] = 11; index[17][2] = 7;

	index[18][0] = 5; index[18][1] = 6; index[18][2] = 12;
	index[19][0] = 4; index[19][1] = 7; index[19][2] = 13;

	




}



void My_plane::Update_with_camera()
{
	extern Camera sCamera;
	Vector3 view_direction = sCamera.mCenter - sCamera.mPosition;
	view_direction.Normalize();
	Vector3 right_direction = Cross(view_direction, sCamera.mUp);//y'和z'叉乘出x’
	right_direction.Normalize();
	
	this->forward_direction = view_direction;
	//this->up_direction = t;
	//std::cout <<"x"<< t.x<<"y"<<t.y<<"z"<<t.z;
	this->xdirection = right_direction;
	Vector3 my_up = Cross(this->forward_direction,this->xdirection);
	my_up.Normalize();
	this->up_direction = my_up * -1;

	this->position = sCamera.mPosition;


}
void My_plane::Update_luoxuan(float angle)
{
	/*luoxuanjiang[0] = forward_direction * 2.8f + xdirection * 0.3f + up_direction * 0.1f - up_direction * 0.5f;
	luoxuanjiang[1] = forward_direction * 2.8f - xdirection * 0.3f + up_direction * 0.1f - up_direction * 0.5f;
	luoxuanjiang[2] = forward_direction * 2.8f + up_direction * 0.8f + up_direction * 0.1f - up_direction * 0.5f;
	luoxuanjiang[3] = forward_direction * 2.8f - up_direction * 0.8f + up_direction * 0.1f - up_direction * 0.5f;*/
	
	Vector3 t1;
	t1=RotateVector(xdirection * 0.1f, angle,forward_direction.x, forward_direction.y, forward_direction.z);
	Vector3 t2;
	t2 = RotateVector(xdirection * -0.1f, angle, forward_direction.x, forward_direction.y, forward_direction.z);
	Vector3 t3;
	t3 = RotateVector(up_direction * 0.8f, angle, forward_direction.x, forward_direction.y, forward_direction.z);
	Vector3 t4;
	t4 = RotateVector(up_direction * (-0.8f), angle, forward_direction.x, forward_direction.y, forward_direction.z);

	luoxuanjiang[0] = forward_direction * 2.8f + t1 + up_direction * 0.1f - up_direction * 0.5f;
	luoxuanjiang[1] = forward_direction * 2.8f + t2 + up_direction * 0.1f - up_direction * 0.5f;
	luoxuanjiang[2] = forward_direction * 2.8f + t3 + up_direction * 0.1f - up_direction * 0.5f;
	luoxuanjiang[3] = forward_direction * 2.8f + t4 + up_direction * 0.1f - up_direction * 0.5f;



}
void My_plane::Update()
{
	//一个面
	vertex[0] = forward_direction * 2.8f + xdirection * 0.1f + up_direction * 0.1f - up_direction * 0.5f;
	vertex[1] = forward_direction * 2.8f - xdirection * 0.1f + up_direction * 0.1f - up_direction * 0.5f;
	vertex[2] = forward_direction * 2.8f - xdirection * 0.1f - up_direction * 0.1f - up_direction * 0.5f;
	vertex[3] = forward_direction * 2.8f + xdirection * 0.1f - up_direction * 0.1f - up_direction * 0.5f;

	vertex[4] = forward_direction * 1.2f + xdirection * 0.1f + up_direction * 0.1f - up_direction * 0.5f;
	vertex[5] = forward_direction * 1.2f - xdirection * 0.1f + up_direction * 0.1f - up_direction * 0.5f;
	vertex[6] = forward_direction * 1.2f - xdirection * 0.1f - up_direction * 0.1f - up_direction * 0.5f;
	vertex[7] = forward_direction * 1.2f + xdirection * 0.1f - up_direction * 0.1f - up_direction * 0.5f;

	vertex[8] = forward_direction * 1.0f + xdirection * 0.1f + up_direction * 0.1f+ up_direction*0.3f- up_direction*0.5f;
	vertex[9] = forward_direction * 1.0f - xdirection * 0.1f + up_direction * 0.1f+ up_direction * 0.3f - up_direction * 0.5f;
	vertex[10] = forward_direction * 1.0f - xdirection * 0.1f - up_direction * 0.1f+ up_direction * 0.3f - up_direction * 0.5f;
	vertex[11] = forward_direction * 1.0f + xdirection * 0.1f - up_direction * 0.1f+ up_direction * 0.3f - up_direction * 0.5f;

	vertex[12] = forward_direction * 1.2f + xdirection * 0.8f - up_direction * 0.5f;
	vertex[13] = forward_direction * 1.2f - xdirection * 0.8f -  up_direction * 0.5f;

	
}
void My_plane::Draw()
{
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.mTextureID);


	for (int i = 0; i < 20; i++)
	{
		
		glBegin(GL_TRIANGLES);
		
		//if ((i/2)%2)//不同颜色镶嵌
		//{
		//	glColor3ub(300, 100, 100);
		//}
		//else {
		//	glColor3ub(100, 100, 300);
		//}
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(vertex[index[i][0]].x+position.x, vertex[index[i][0]].y+ position.y, vertex[index[i][0]].z+ position.z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(vertex[index[i][1]].x+position.x, vertex[index[i][1]].y+ position.y, vertex[index[i][1]].z+ position.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(vertex[index[i][2]].x+position.x, vertex[index[i][2]].y+ position.y, vertex[index[i][2]].z+ position.z);
	}
	//Vector3 t1 = luoxuanjiang[2] - luoxuanjiang[0];
	glBindTexture(GL_TEXTURE_2D, 0);

	glBegin(GL_TRIANGLES);
	glVertex3f(luoxuanjiang[0].x + position.x, luoxuanjiang[0].y + position.y, luoxuanjiang[0].z + position.z);
	glVertex3f(luoxuanjiang[1].x + position.x, luoxuanjiang[1].y + position.y, luoxuanjiang[1].z + position.z);
	glVertex3f(luoxuanjiang[2].x + position.x, luoxuanjiang[2].y + position.y, luoxuanjiang[2].z + position.z);
	glBegin(GL_TRIANGLES);
	glVertex3f(luoxuanjiang[0].x + position.x, luoxuanjiang[0].y + position.y, luoxuanjiang[0].z + position.z);
	glVertex3f(luoxuanjiang[1].x + position.x, luoxuanjiang[1].y + position.y, luoxuanjiang[1].z + position.z);
	glVertex3f(luoxuanjiang[3].x + position.x, luoxuanjiang[3].y + position.y, luoxuanjiang[3].z + position.z);

	//glColor3ub(100, 100, 100);
	glEnd();

}

