#include "SkyBox.h"
#include "texture.h"
void SkyBox::Init() {
	mTextures[0].Init("my_texture/left.bmp");
	mTextures[1].Init("my_texture/right.bmp");
	mTextures[2].Init("my_texture/front.bmp");
	mTextures[3].Init("my_texture/back.bmp");
	mTextures[4].Init("my_texture/bottom.bmp");
	mTextures[5].Init("my_texture/top.bmp");
}
void SkyBox::Draw(float x, float y, float z) {
	;
	glDepthMask(false);
	glPushMatrix();
	glTranslatef(x, y, z);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextures[2].mTextureID);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, mTextures[0].mTextureID);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, mTextures[1].mTextureID);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, mTextures[3].mTextureID);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, mTextures[4].mTextureID);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, mTextures[5].mTextureID);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();
	glDepthMask(true);
	glEnable(GL_LIGHTING);
}