#include<string.h>
#include <GL/glut.h>
#include<gl/GL.h>
#include<gl/GLU.h>

#include "texture.h"
#include "utils.h"


unsigned char* DecodeBMP(unsigned char*bmpfile, int &width, int &height)
{
	/*
	if(memcmp(bmpfile, "BM", 2)==0)
	{
		printf("i am bmp\n");
	}
	if(0x4D42==*((unsigned short*)bmpfile))
	{
		printf("i am bmp\n");
	}
	char szbuffer[4]={0};
	memcpy(szbuffer,bmpfile,4);
	return nullptr;
	 */
	if (memcmp(bmpfile, "BM", 2) == 0) {
		int pixel_bgr_data_offset = *((int*)(bmpfile + 10));
		width = *((int*)(bmpfile + 18));
		height = *((int*)(bmpfile + 22));
		unsigned char * bgr_data = bmpfile + pixel_bgr_data_offset;
		//bgr -> rgb
		for (int i = 0; i < width*height; i++) {
			int current_pixel_index = i * 3;
			unsigned char b = bgr_data[current_pixel_index];
			unsigned char r = bgr_data[current_pixel_index + 2];
			bgr_data[current_pixel_index] = r;
			bgr_data[current_pixel_index + 2] = b;
		}
		return bgr_data;//�޸Ĺ���ʵ������rgb_data
	}
	return nullptr;
}
void Texture::Init(const char*imagePath)
{
	//load image file from disk to memory
	unsigned char* imageFileContent = LoadFileContent(imagePath);//ͼ���ļ�����


	//decode image
	int width = 0;
	int height = 0;
	unsigned char*pixelData = DecodeBMP(imageFileContent,width,height);//��������


	//generate an opengl texture
	glGenTextures(1,&mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);//���ñ��ΪmTextureID������Ϊ��ǰ����

	//pixelӳ����texel�ϣ�GL_NEAREST��GL_LINEAR���ֲ�ֵ��ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//�������곬��0��1�Ĵ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0, GL_RGB,GL_UNSIGNED_BYTE, pixelData);//���ڴ�ˢ���Դ棬�Դ����ݸ�ʽΪRGB���ڴ�����Դ��ʽҲ��RGB�����ڴ���RGB�ķ����Ĵ洢��ʽΪGL_UNSIGNED_BYTE
	//ʹ��glTexImage2D��mTextureID��ָ�����Դ��е�һ�����򣬸�����ڷ���һ������
	


	delete[] imageFileContent;//�����Ѿ�ˢ���Դ棬����ɾ���ڴ���������
	glBindTexture(GL_TEXTURE_2D, 0);//������󣬵�ǰ������Ϊ0����ֹ�����GL_TEXTURE_2D����
}