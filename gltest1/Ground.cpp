#include "Ground.h"
void Ground::Draw()
{
	mMaterial->Update();
	glEnable(GL_COLOR_MATERIAL);//�������պ�Ͳ��ῼ�Ƕ������ɫ���������Ҫ���Ƕ������ɫ�Ļ�����Ҫ��仰
	for (int z = 0; z < 20; z++)//��xzƽ�����200*200��ƽ��
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; x++)
		{
			float xStart = -100.0f + x * 10.0f;
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(0.0f, 1.0f, 0.0f);
			if ((z % 2) ^ (x % 2))//��ͬ��ɫ��Ƕ
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
