#include "New_ground.h"
void New_ground::Init(const Vector3&position_start, const float &block_len, const int&edge_len, Material* material)
{
	this->position_start = position_start;
	this->block_len = block_len;
	this->edge_len = edge_len;
	this->material = material;


	Vector3 x_dir(1.0f, 0.0f, 0.0f);
	Vector3 z_dir(0.0f, 0.0f, 1.0f);
	Block block;//创建出范例方块
	block.Init(this->position_start, x_dir, z_dir, this->block_len, this->material);

	for (int i = 0; i < MAX_GROUND_LEN; i++)
	{
		for (int j = 0; j < MAX_GROUND_LEN; j++)
		{
			ground_height[i][j] = (this->noise.PerlinNoise((double)i,(double)j)+ (double)LOW_HEIGHT);//地形数据更新并存放
			ground_block[index] = block;//方块数据
			index++;
		}
	}
	index = 0;
	Vector3 t_position = this->position_start;
	for (int i = 0; i < this->edge_len; i++)
	{
		t_position.x = this->position_start.x + i * this->block_len;
		for (int j = 0; j < this->edge_len; j++)
		{
			t_position.z = this->position_start.z + j * this->block_len;
			int t = (int)(ground_height[i][j] + 0.5);
			for (int h = 0; h < t; h++)
			{
				t_position.y = this->position_start.y + h * this->block_len;
				//this->ground_block[this->index].Init(t_position, x_dir, z_dir, this->block_len, this->material);
				this->ground_block[this->index].set_pos_dir(t_position, x_dir, z_dir);
				this->ground_block[this->index].Update();
				add_block2scene(this->ground_block[this->index]);
				this->index++;
			}
		}
	}
}
void New_ground::Draw()
{
	material->Update();
	for (int i = 0; i < this->index; i++)
	{
		this->ground_block[i].Draw();
	}
}
