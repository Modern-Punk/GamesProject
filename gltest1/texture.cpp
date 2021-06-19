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
		return bgr_data;//修改过后，实际上是rgb_data
	}
	return nullptr;
}
void Texture::Init(const char*imagePath)
{
	//load image file from disk to memory
	unsigned char* imageFileContent = LoadFileContent(imagePath);//图像文件数据


	//decode image
	int width = 0;
	int height = 0;
	unsigned char*pixelData = DecodeBMP(imageFileContent,width,height);//像素数据


	//generate an opengl texture
	glGenTextures(1,&mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);//设置编号为mTextureID的纹理为当前纹理

	//pixel映射至texel上，GL_NEAREST和GL_LINEAR两种差值方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//纹理坐标超过0到1的处理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0, GL_RGB,GL_UNSIGNED_BYTE, pixelData);//从内存刷到显存，显存数据格式为RGB，内存数据源格式也是RGB，在内存中RGB的分量的存储方式为GL_UNSIGNED_BYTE
	//使用glTexImage2D后，mTextureID就指向了显存中的一块区域，该区域摆放着一块纹理
	


	delete[] imageFileContent;//数据已经刷入显存，可以删除内存中数据了
	glBindTexture(GL_TEXTURE_2D, 0);//操作完后，当前纹理设为0，防止误操作GL_TEXTURE_2D纹理
}