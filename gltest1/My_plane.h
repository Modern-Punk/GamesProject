#pragma once
#include <math.h>
#include <gl/glut.h>
#include "Vector3.h"
#include "Camera.h"
#include "texture.h"
class My_plane {
public:
	Vector3 forward_direction;
	Vector3 up_direction;
	Vector3 position;
	Vector3 xdirection;
	Vector3 vertex[100];
	Vector3 luoxuanjiang[100];
	int index[100][3];
	Texture texture;
	My_plane();
	void init();
	void Draw();
	void Update_with_camera();
	void Update();
	void Update_luoxuan(float angle);


	
};