#include<GL/glut.h>
#include<stdlib.h>
#include<iostream>
#include <map>
#include "texture.h"
#include "utils.h"
#include "Vector3.h"
#include "Camera.h"
#include "Ground.h"
#include "Light.h"
#include "Model.h"
#include "Block.h"
#include "New_ground.h"
#include "Scene_Manager.h"
#include "My_plane.h"
#include "Skybox.h"


using namespace std;

extern long long obj_id;
extern std::map<long long, Block> id2block;
extern void add_block2scene(Block &b);
extern void clear_draw_once();
extern float tran_angle(float angle);//角度转弧度
extern std::vector<Block> collision_Block_list;
extern void ShowFrameRate();

SkyBox skybox;
Light* light;
PointLight* point_light;
SpotLight* spotlight;
Material* material;
Ground ground;
Camera sCamera;
//地球
Texture texture;
Model model;
//黑色飞机
Texture texture2;
Model model2;

Block block;
New_ground n_ground;
My_plane myplane;
float angle=0.0f;//螺旋桨旋转角度
int mode = 0;
int plane_mode = 1;//是否上帝视角
int polygon_mode = 1;//是否线框模式
bool draw_obj=false;//是否绘制出黑色飞机
Vector3 scene_cneter(0.0f, 0.0f, 0.0f);//场景中心
float scene_len = 400.0f;//场景尺寸
Scene_Manager scene_manager(scene_cneter, scene_len);//创建8叉树管理器

float env_len = 60.0f;//自身包围盒尺寸

int cx = glutGet(GLUT_SCREEN_WIDTH);
int cy = glutGet(GLUT_SCREEN_HEIGHT);
int width = 600;
int height = 600;
float delta_time = 0.015;
//鼠标
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
int last_mousex;
int last_mousey;
bool first=true;//第一次
float time_redraw = 15;//单位ms，重绘时间

void OnMouseMove(float deltax, float deltay)
{
	float angleRotateByRightDirection = deltay / 1000.0f;//角度变化较小时，可用距离来表征角度的变化
	float angleRotateByUp = deltax / 1000.0f;
	sCamera.Pitch(-angleRotateByRightDirection);
	myplane.up_direction = RotateVector(myplane.up_direction, angleRotateByRightDirection, myplane.xdirection.x, myplane.xdirection.y, myplane.xdirection.z);

	sCamera.Yaw(-angleRotateByUp);
}

void dragmouse(int x, int y)
{
	if (first)
	{
		last_mousex = x;
		last_mousey = y;
		first = false;
		return;
	}
	//std::cout << x << y;
	float deltax = (float)(last_mousex - x);
	float deltay = (float)(last_mousey - y);
	last_mousex = x;
	last_mousey = y;
	OnMouseMove(-deltax, -deltay);
	sCamera.Update(delta_time);
	//myplane.Update_with_camera();
	//myplane.Update();
	glutPostRedisplay();
}




void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
		{
			mouseLeftDown = false;
			mouseRightDown = false;
			first = true;//"第一次"标记为真
		}
	}
	else if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
			mouseRightDown = false;
			first = true;//"第一次"标记为真
	}
}




void init(int width,int height)
{
	std::cout << "初始状态为模式1" << endl;
	std::cout << "按q进行切换(模式1：自身包围盒场景加载，模式2：全部场景加载（会使得帧率变低），模式3：加载离自身最近的分割子块包围盒)" << endl;
	std::cout << "按e切换为上帝视角" << endl;
	std::cout << "按m转换为线框模式" << endl;
	std::cout << "按n纸飞机和地球切换" << endl;
	std::cout << "按j可以向下抛出弹性物体"<<endl;
	std::cout << "按k可以使得弹性物体静止（以提高帧率）" << endl;
	std::cout << "模式1下：按p可以扩大自身包围盒尺寸（帧率降低）" << endl;
	std::cout << "模式1下：按o可以减小自身包围盒尺寸（帧率提高）" << endl;


	sCamera.Set(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
	sCamera.mViewportWidth = (float)width;
	sCamera.mViewportHeight = (float)height;
	/*Vector3 t1(0.0f, 0.0f, 1.0f);
	Vector3 t2(0.0f, 1.0f, 0.0f);
	myplane.forward_direction = t1;
	myplane.up_direction = t2;*/
	
	//地球模型
	texture.Init("my_texture/earth.bmp"); 
	model.Init("my_obj/Sphere.obj");
	//玩具飞机模型
	texture2.Init("my_texture/NH90.bmp");
	model2.Init("my_obj/fly.obj");

	light = new DirectionLight(GL_LIGHT0);
	light->SetPosition(-1.0f, 1.0f, 0.0f);
	light->SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	light->SetDiffuseColor(10.0f, 10.0f, 10.0f, 1.0f);
	light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);

	point_light = new PointLight(GL_LIGHT1);
	point_light->SetPosition(0.0f, 5.0f, 0.0f);
	point_light->SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	point_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	point_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	point_light->SetAttenuation(1.0f, 0.4f, 0.0f);//设置衰减系数

	spotlight = new SpotLight(GL_LIGHT2);
	spotlight->SetPosition(0.0f, 5.0f, 0.0f);
	spotlight->SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
	spotlight->SetDiffuseColor(10.0f, 10.0f, 10.0f, 1.0f);
	spotlight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	spotlight->SetAttenuation(1.0f, 0.4f, 0.0f);//设置衰减系数
	spotlight->SetDirection(0.0f, -1.0f, 0.0f);//向下照射
	spotlight->SetExponent(5.0f);//亮斑区5度
	spotlight->SetCutoff(8.0f);//超过8度无光



	material = new Material;
	material->SetSpecularShininess(32.0f);
	material->SetAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	material->SetDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	material->SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
	
	model.SetMaterial(material);
	model2.SetMaterial(material);
	ground.mMaterial = material;

	sCamera.SwitchTo3D();
	sCamera.Update(0);//Update函数中有glLoadIdentity(),主要用于刚开始的摆放视角

	myplane.init();

	Vector3 center_vector(-10.0f, -20.0f, -10.0f);
	n_ground.Init(center_vector, 5.0f, 50, material);

	skybox.Init();
	auto p = scene_manager.Update();//建树

}

void display()
{
	glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	sCamera.SwitchTo3D();
	sCamera.Update(delta_time);//Update函数中有glLoadIdentity()
	light->Update();
	//point_light->Update();
	spotlight->Update();

	//skybox.Draw(sCamera.mPosition.x, sCamera.mPosition.y, sCamera.mPosition.z);
	//ground.Draw();

	//block.Draw();
	//n_ground.Draw();
	skybox.Draw(sCamera.mPosition.x, sCamera.mPosition.y, sCamera.mPosition.z);
	if (plane_mode == 1)
	{
		myplane.Update_with_camera();
		myplane.Update_luoxuan(tran_angle(angle));
		myplane.Update();
	}
	myplane.Draw();

	env_AABB my_box;
	my_box.center = sCamera.mPosition;
	my_box.len = env_len;
	//std::cout << "sCamera:" << "(" << sCamera.mPosition.x << "," << sCamera.mPosition.y << "," << sCamera.mPosition.z << ")";
	if (mode == 0)
	{
		scene_manager.Draw_mybox(scene_manager.root,my_box);
		clear_draw_once();
	}
	else if(mode==1)
	{
		scene_manager.Draw_all();
	}
	else if (mode == 2)
	{
		scene_manager.Draw_dynamic(sCamera.mPosition);
	}
	//scene_manager.Draw_dynamic(sCamera.mPosition);
	//scene_manager.Draw_frustum(scene_manager.root);
	//scene_manager.Draw_all();

	//glLoadIdentity();//不能添加glloadidentity
	
	
	if (draw_obj == true)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 140.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture2.mTextureID);
		model2.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 20.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture.mTextureID);
		model.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
	

	
	

	sCamera.SwitchTo2D();
	//draw UI


	glFlush();

}
void reshape(int w,int h)
{
	/*
	width = w;
	height = h;
	sCamera.Set(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f));
	sCamera.mViewportWidth = (float)width;
	sCamera.mViewportHeight = (float)height;
	sCamera.SwitchTo3D();
	*/

}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}
	if (key == 'w')
	{
		sCamera.mForward = true;
		sCamera.Update(delta_time);//Update函数中有glLoadIdentity()
		glutPostRedisplay();//提供标志，在keyboard函数结束完才会绘制
	}
	if (key == 'a')
	{
		sCamera.mMoveLeft = true;
		sCamera.Update(delta_time);//Update函数中有glLoadIdentity()
		glutPostRedisplay();//提供标志，在keyboard函数结束完才会绘制
	}
	if (key == 'd')
	{
		sCamera.mMoveRight = true;
		sCamera.Update(delta_time);//Update函数中有glLoadIdentity()
		glutPostRedisplay();//提供标志，在keyboard函数结束完才会绘制
	}
	if (key == 's')
	{
		sCamera.mBackward = true;
		sCamera.Update(delta_time);//Update函数中有glLoadIdentity()
		glutPostRedisplay();//提供标志，在keyboard函数结束完才会绘制
	}
	if (key == 'q')
	{
		mode++;
		if (mode == 3) mode = 0;
		if (mode == 0) std::cout << "模式1" << endl;
		if (mode == 1) std::cout << "模式2" << endl;
		if (mode == 2) std::cout << "模式3" << endl;
	}
	if (key == 'e')
	{
		plane_mode = ~plane_mode;
	}
	if (key == 'j')
	{
		scene_manager.generate_block_with_gravity(sCamera.mPosition,material);
	}
	if (key == 'k')
	{
		if (collision_Block_list.size() != 0)
		{
			collision_Block_list.pop_back();
		}
	}
	if (key == 'p')
	{
		if (mode == 0)
		{
			env_len += 5.0f;
		}
	}
	if (key == 'o')
	{
		if (mode == 0)
		{
			env_len -= 5.0f;
		}
	}
	if (key == 'm')
	{
		polygon_mode = ~polygon_mode;
		if (polygon_mode == 1)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	if (key == 'n')
	{
		if (draw_obj == false)
		{
			draw_obj = true;
		}
		else
		{
			draw_obj = false;
		}
	}
}

void timerfunc(int value) {//15ms检测一次
	//用于螺旋桨旋转
	angle = angle + 3.0f;
	if (angle > 360.0f) angle = 0.0f;

	for (int i = 0; i < collision_Block_list.size(); i++)
	{

		collision_Block_list[i].center_position.y = collision_Block_list[i].center_position.y - collision_Block_list[i].speed*time_redraw;
		collision_Block_list[i].Update();
		scene_manager.Update_block(collision_Block_list[i]);//对八叉树的节点更新
		id2block[collision_Block_list[i].id] = collision_Block_list[i];

		auto p=scene_manager.find_leaf(collision_Block_list[i].center_position, scene_manager.root);
		bool collision_flag = false;
		for (auto iter_s = p->box.contain_obj.begin(); iter_s != p->box.contain_obj.end(); iter_s++)
		{
			//std::cout << "正在尝试：" << (*iter_s) << "号物体与" << collision_Block_list[i].id << "号物体相交";
			if (*iter_s == collision_Block_list[i].id) {  continue; }//创建场景后，自身也在场景中，自身与自身的相交不能算
			auto iter_block = id2block.find(*iter_s);
			if (iter_block != id2block.end() )
			{

				if (Test_block_block(iter_block->second, collision_Block_list[i]) == true)
				{
					//std::cout << "相交";
					collision_Block_list[i].speed = (collision_Block_list[i].speed)*-1 * collision_Block_list[i].k;
					collision_flag = true;
					break;
				}
			}
			//不一定每个id都对应这block类的物体
			//可以写更多
		}
		if (collision_flag==false)
		{
			collision_Block_list[i].speed = collision_Block_list[i].speed + collision_Block_list[i].a;
		}
	}

	ShowFrameRate();
	glutPostRedisplay();  //标记当前窗口需要重新绘制
	glutTimerFunc(time_redraw, timerfunc, 1);




}
int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width,height);
	glutInitWindowPosition((cx - width) / 2, (cy - height) / 2);
	glutCreateWindow(argv[0]);
	init(width, height);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseCB);//鼠标
	glutMotionFunc(dragmouse);
	glutTimerFunc(time_redraw, timerfunc, 1);
	glutMainLoop();
	return 0;
}