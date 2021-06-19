#pragma once
#include <gl/glut.h>
#include <stdio.h>
#include "texture.h"
class SkyBox {
public:
	Texture mTextures[6];
	void Init();
	void Draw(float x, float y, float z);
};

