#pragma once
#include <set>
#include <map>
#include <math.h>
#include <queue>
#include "Vector3.h"
#include "Block.h"
#include "Camera.h"
#include "OBB.h"
#define eps 1e-4f

#define MIN_AABB_LEN 10.0f//与MIN_AABB_LEN边长的AABB包围盒中的物体进行碰撞检测，划分不能太小，否则碰撞检测将失效。

extern bool draw_once[];


class env_AABB//立方体包围盒(针对空间)
{
public:
	float len;//全长
	Vector3 center;
	std::set<long long> contain_obj;
	//void Draw();//画出包含的物体
	env_AABB() {};
	env_AABB(float _len, Vector3 _center) :len(_len), center(_center) {};
};

//八叉树结构
typedef struct OctreeNode {
	env_AABB box;
	OctreeNode* children[2][2][2];//x,y,z的分割
	//QuadtreeNode* par;
}OctreeNode;


/************判断与AABB是否有交集************/
//判断block是否与env_AABB立方体存在交集,这里假定两者都属于AABB
bool Is_intersect_block(const env_AABB &box, const Block &block)
{
	if (abs(box.center[0] - block.center_position[0]) > (box.len + block.len) / 2.0f) return false;
	if (abs(box.center[1] - block.center_position[1]) > (box.len + block.len) / 2.0f) return false;
	if (abs(box.center[2] - block.center_position[2]) > (box.len + block.len) / 2.0f) return false;
	return true;
}

bool Test_AABB_AABB(const env_AABB &box1, const env_AABB &box2)
{
	if (abs(box1.center[0] - box2.center[0]) > (box1.len + box2.len) / 2.0f) return false;
	if (abs(box1.center[1] - box2.center[1]) > (box1.len + box2.len) / 2.0f) return false;
	if (abs(box1.center[2] - box2.center[2]) > (box1.len + box2.len) / 2.0f) return false;
	
	return true;
}

bool Test_block_block(const Block &block1, const Block &block2)
{
	if (abs(block1.center_position[0] - block2.center_position[0]) > (block1.len + block2.len) / 2.0f) return false;
	if (abs(block1.center_position[1] - block2.center_position[1]) > (block1.len + block2.len) / 2.0f) return false;
	if (abs(block1.center_position[2] - block2.center_position[2]) > (block1.len + block2.len) / 2.0f) return false;
	return true;
}


OctreeNode* build_OctTree(OctreeNode* root)
{
	extern long long obj_id;
	extern std::map<long long, Block> id2block;
	float len = root->box.len;
	Vector3 center = root->box.center;
	if (len < MIN_AABB_LEN - eps)//条件，这里MIN_AABB_LEN为叶子节点中AABB包围盒的长度
	{
		return NULL;
	}
	float new_len = len / 2.0f;
	float t = new_len / 2.0f;

	Vector3 position_1 = Vector3(center.x - t, center.y + t, center.z + t);
	env_AABB box_1(new_len, position_1);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_1, id2block[*it]))
			{
				box_1.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child1 = new OctreeNode;
	child1->box = box_1;
	root->children[0][1][1] = build_OctTree(child1);


	Vector3 position_2 = Vector3(center.x + t, center.y + t, center.z + t);
	env_AABB box_2(new_len, position_2);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_2, id2block[*it]))
			{
				box_2.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child2 = new OctreeNode;
	child2->box = box_2;
	root->children[1][1][1] = build_OctTree(child2);


	Vector3 position_3 = Vector3(center.x - t, center.y + t, center.z + -t);
	env_AABB box_3(new_len, position_3);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_3, id2block[*it]))
			{
				box_3.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child3 = new OctreeNode;
	child3->box = box_3;
	root->children[0][1][0] = build_OctTree(child3);


	Vector3 position_4 = Vector3(center.x + t, center.y + t, center.z - t);
	env_AABB box_4(new_len, position_4);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_4, id2block[*it]))
			{
				box_4.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child4 = new OctreeNode;
	child4->box = box_4;
	root->children[1][1][0] = build_OctTree(child4);


	Vector3 position_5 = Vector3(center.x - t, center.y - t, center.z + t);
	env_AABB box_5(new_len, position_5);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_5, id2block[*it]))
			{
				box_5.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child5 = new OctreeNode;
	child5->box = box_5;
	root->children[0][0][1] = build_OctTree(child5);


	Vector3 position_6 = Vector3(center.x + t, center.y - t, center.z + t);
	env_AABB box_6(new_len, position_6);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_6, id2block[*it]))
			{
				box_6.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child6 = new OctreeNode;
	child6->box = box_6;
	root->children[1][0][1] = build_OctTree(child6);


	Vector3 position_7 = Vector3(center.x - t, center.y - t, center.z - t);
	env_AABB box_7(new_len, position_7);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_7, id2block[*it]))
			{
				box_7.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child7 = new OctreeNode;
	child7->box = box_7;
	root->children[0][0][0] = build_OctTree(child7);


	Vector3 position_8 = Vector3(center.x + t, center.y - t, center.z - t);
	env_AABB box_8(new_len, position_8);
	for (std::set<long long>::iterator it = root->box.contain_obj.begin(); it != root->box.contain_obj.end(); it++)
	{
		if (id2block.find(*it) != id2block.end())
		{
			if (Is_intersect_block(box_8, id2block[*it]))
			{
				box_8.contain_obj.insert(*it);
			}
			//后面可以加上不同类的相交检测
			//
		}
	}
	OctreeNode *child8 = new OctreeNode;
	child8->box = box_8;
	root->children[1][0][0] = build_OctTree(child8);


	return root;
}





class Scene_Manager
{
public:
	Vector3 center;
	float scene_len;
	OctreeNode* root;
	OctreeNode* Update()//对现有物体和场景生成8叉树
	{
		extern long long obj_id;
		extern std::map<long long, Block> id2block;
		env_AABB box(scene_len, center);//整个场景作为一个bounding box进行细分
		for (long long i = 0; i < obj_id; i++)
		{
			box.contain_obj.insert(i);
		}
		OctreeNode* q = new OctreeNode;
		q->box = box;
		root = build_OctTree(q);
		return root;
	}



	/************场景中物体的操作************/
	void delete_block(OctreeNode* node, const Block &block)//删除方块类型物体
	{
		auto it = node->box.contain_obj.find(block.id);
		if (it != node->box.contain_obj.end())
		{
			node->box.contain_obj.erase(it);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 2; k++)
					{
						if (node->children[i][j][k] != NULL)
						{
							delete_block(node->children[i][j][k], block);
						}
					}
				}
			}
		}
	}
	void add_block(OctreeNode* node, const Block &block)//加入方块类型物体
	{
		if (Is_intersect_block(node->box, block))
		{
			node->box.contain_obj.insert(block.id);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 2; k++)
					{
						if (node->children[i][j][k] != NULL)
						{
							add_block(node->children[i][j][k], block);
						}
					}
				}
			}
		}
	}
	void Update_block(Block &b)//当Block位置信息发生变化时，需要调用此函数更新Block与AABB包围盒的关系,更新八叉树节点信息
	{
		delete_block(root, b);
		add_block(root, b);
	}



	/************碰撞检测************/
	OctreeNode*  find_leaf(Vector3 obj_position, OctreeNode* root)//深搜，根据自身的位置寻找场景中最近的非空叶子节点（即最近的AABBbox）,返回找到的叶子节点
	{
		//如果不是叶子节点就要向下递推，递推原则（找最近距离）
		int _i = -1, _j = -1, _k = -1;//要递推的i,j,k
		float minf = 50000.0f;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					if (root->children[i][j][k] != NULL && root->children[i][j][k]->box.contain_obj.size()!=0)
					{
						Vector3 v = obj_position - (root->children[i][j][k]->box.center);
						float val = Dot(v, v);
						if (val < minf)
						{
							minf = val;
							_i = i;
							_j = j;
							_k = k;
						}
					}
				}
			}
		}
		if (_i == -1 && _j == -1 && _k == -1)
		{
			return root;
		}
		else
		{
			find_leaf(obj_position, root->children[_i][_j][_k]);
		}
	}

	void generate_block_with_gravity(Vector3 mPosition,Material *material)
	{
		extern std::vector<Block> collision_Block_list;
		Block *b = new Block();
		Vector3 x_dir(1.0f, 0.0f, 0.0f);
		Vector3 z_dir(0.0f, 0.0f, 1.0f);
		float len = 2.0f;
		b->speed_enable = true;
		b->speed = 0.0f;
		b->a = 0.0008f;
		b->k = 0.9;
		b->Init_2(mPosition, x_dir, z_dir, len, material);
		/*b.center_position = mPosition;
		b.x_direction = x_dir;*/
		b->Update();
		add_block2scene(*b);//定义在global.h中
		collision_Block_list.push_back(*b);
		add_block(this->root,*b);
		std::cout << "生成了可碰撞物体" << b->id << std::endl;
		
	}


	

/************绘图************/
	//对所有的id对应的物体进行绘制
	void Draw_all()
	{
		extern long long obj_id;
		extern std::map<long long, Block> id2block;
		for (int i = 0; i < obj_id; i++)
		{
			auto iter_block = id2block.find(i);
			if (iter_block != id2block.end())
			{
				iter_block->second.Draw();
			}
			//不一定每个id都对应这block类的物体
			//可以写更多
		}
	}
	//动态绘制物体
	void Draw_dynamic(Vector3 my_position)
	{
		extern long long obj_id;
		extern std::map<long long, Block> id2block;
		auto p = find_leaf(my_position,this->root);
		for (auto iter_s = p->box.contain_obj.begin(); iter_s != p->box.contain_obj.end(); iter_s++)
		{
			auto iter_block = id2block.find(*iter_s);
			if (iter_block != id2block.end())
			{
				iter_block->second.Draw();
			}
			//不一定每个id都对应这block类的物体
			//可以写更多
		}
	}
	
	void Draw_mybox(OctreeNode* root,const env_AABB &my_box)
	{
		extern std::map<long long, Block> id2block;
		if (root->box.contain_obj.size() == 0) return;
		if (Test_AABB_AABB(root->box, my_box))
		{
			//std::cout << "相交";
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					for (int k = 0; k < 2; k++)
					{
						if (root->children[i][j][k] != NULL)
						{
							Draw_mybox(root->children[i][j][k], my_box);
						}
						else//叶子节点
						{
							for (auto iter_s = root->box.contain_obj.begin(); iter_s != root->box.contain_obj.end(); iter_s++)
							{
								if (draw_once[*iter_s] == true) { /*std::cout << "有重复的";*/ continue; }
								else
								{
									draw_once[*iter_s] = true;
								}
								auto iter_block = id2block.find(*iter_s);
								if (iter_block != id2block.end())
								{
									iter_block->second.Draw();
								}
								//不一定每个id都对应这block类的物体
								//可以写更多
							}
						}

					}
				}
			}
		}
	}
	void Draw_frustum(OctreeNode* root)
	{
		//std::cout << "执行";
		extern Camera sCamera;
		//std::cout << "sCamera:" << "(" << sCamera.obb.c.x << "," << sCamera.obb.c.y << "," << sCamera.obb.c.z << ")";
		//std::cout << "sCamera:长度为" << "(" << sCamera.obb.e.x << "," << sCamera.obb.e.y << "," << sCamera.obb.e.z << ")";
		extern std::map<long long, Block>id2block;
		if (root->box.contain_obj.size() == 0) return;
		else
		{
			OBB t;//通过AABB构造出OBB，从而判断能否相交
			t.c = root->box.center;
			//std::cout << "场景中心:" << "(" << t.c.x << "," << t.c.y << "," << t.c.z << ")";
			Vector3 x_dir(1.0f, 0.0f, 0.0f);
			Vector3 y_dir(0.0f, 1.0f, 0.0f);
			Vector3 z_dir(0.0f, 0.0f, 1.0f);
			t.u[0] = x_dir;
			t.u[1] = y_dir;
			t.u[2] = z_dir;
			Vector3 len = Vector3(root->box.len/2.0f, root->box.len/2.0f, root->box.len/2.0f);
			t.e = len;
			//std::cout << "半长为" << root->box.len / 2.0f;
			if (TestOBBOBB(sCamera.obb, t))
			{
				std::cout << "相交";
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 2; k++)
						{
							if (root->children[i][j][k] != NULL)
							{
								Draw_frustum(root->children[i][j][k]);
							}
							else//叶子节点
							{
								std::cout << "绘画";
								for (auto iter_s = root->box.contain_obj.begin(); iter_s != root->box.contain_obj.end(); iter_s++)
								{
									auto iter_block = id2block.find(*iter_s);
									if (iter_block != id2block.end())
									{
										iter_block->second.Draw();
									}
									//不一定每个id都对应这block类的物体
									//可以写更多
								}
								return;
							}
						}
					}
				}
			}
			else
			{
				std::cout << "不相交";
				return;
			}

		}
	}

	Scene_Manager() {};
	Scene_Manager(const Vector3 &_center, const float &_scene_len) :center(_center), scene_len(_scene_len) {};


};