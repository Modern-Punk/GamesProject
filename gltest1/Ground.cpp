#include "Ground.h"
void Ground::Draw()
{
	mMaterial->Update();
	glEnable(GL_COLOR_MATERIAL);//开启光照后就不会考虑顶点的颜色，但是如果要考虑顶点的颜色的话，就要这句话
	for (int z = 0; z < 20; z++)//在xz平面绘制200*200的平面
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; x++)
		{
			float xStart = -100.0f + x * 10.0f;
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0.0f, 1.0f, 0.0f);
			if ((z % 2) ^ (x % 2))//不同颜色镶嵌
			{
				glColor3ub(100, 100, 100);
			}
			else {
				glColor3ub(200, 200, 200);
			}
			glVertex3f(xStart, -1.0f, zStart);
			glVertex3f(xStart + 10.0f, -1.0f, zStart);
			glVertex3f(xStart, -1.0f, zStart - 10.0f);
			glVertex3f(xStart + 10.0f, -1.0f, zStart - 10.0f);
		}

	}
	glEnd();

}
