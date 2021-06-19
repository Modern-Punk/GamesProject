#include <vector>
#include <sstream>
#include <string>
#include <string.h>
#include "Model.h"
#include "utils.h"


void Model::Init(const char *path)
{
	unsigned char* filecontent = LoadFileContent(path);
	struct FloatData {
		float v[3];
	};
	struct VertexDefine {//位置，纹理坐标，法线共同定义了一个点
		int position_index;
		int texcoord_index;
		int normal_index;
	};
	std::vector<FloatData> positions, texcoords, normals;//数据池
	std::vector<VertexDefine> vertexes;//比如1/1/1代表的是一个点，在Quad模型中共有4个这样的点，在face中查看
	std::vector<int> indexes;//2个面，每个面有3个点，共有6个
	std::stringstream ssFileContent((char*)filecontent);//初始化流
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if (strlen(szOneLine) > 0) {//不是空行
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't')//纹理坐标
				{
					ssOneLine >> temp;//ssOneLine是以空格为单位的指针坐标移动,将vt输出去
					FloatData fd;
					ssOneLine >> fd.v[0];
					ssOneLine >> fd.v[1];
					texcoords.push_back(fd);//纹理坐标的数据池
				}
				else if (szOneLine[1] == 'n')
				{
					ssOneLine >> temp;
					FloatData fd;
					ssOneLine >> fd.v[0];
					ssOneLine >> fd.v[1];
					ssOneLine >> fd.v[2];
					normals.push_back(fd);//法线的数据池
				}
				else
				{
					ssOneLine >> temp;
					FloatData fd;
					ssOneLine >> fd.v[0];
					ssOneLine >> fd.v[1];
					ssOneLine >> fd.v[2];
					positions.push_back(fd);//点位置的数据池
				}
			}
			else if (szOneLine[0] == 'f') {
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string tempStr;
				for (int i = 0; i < 3; i++)
				{
					ssOneLine >> tempStr;
					size_t pos = tempStr.find_first_of('/');
					std::string pos_index_str = tempStr.substr(0, pos);
					size_t pos2 = tempStr.find_first_of('/', pos + 1);
					std::string texcoord_index_str = tempStr.substr(pos + 1, (pos2 - 1) - (pos + 1) + 1);
					std::string normal_index_str = tempStr.substr(pos2 + 1, tempStr.length() - 1 - pos2);
					VertexDefine vd;
					vd.position_index = atoi(pos_index_str.c_str()) - 1;//模型的索引是从1开始的，C++中的索引是从0开始的。
					vd.texcoord_index = atoi(texcoord_index_str.c_str()) - 1;
					vd.normal_index = atoi(normal_index_str.c_str()) - 1;
					//去重
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					for (int j = 0; j < nCurrentVertexCount; j++)
					{
						if (vertexes[j].position_index == vd.position_index && vertexes[j].texcoord_index == vd.texcoord_index && vertexes[j].normal_index == vd.normal_index)
						{
							nCurrentVertexIndex = j;//找到重复的索引了
							break;
						}
					}
					if (nCurrentVertexIndex == -1)//未找到
					{
						nCurrentVertexIndex = nCurrentVertexCount;
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);//indexes记录的是点的索引，在这些索引中，每三个要生成一个面的。
				}

			}
		}
	}
	delete[] filecontent;
	mIndexCount = indexes.size();
	mIndexes = new unsigned int[mIndexCount];
	for (int i = 0; i < mIndexCount; i++)
	{
		mIndexes[i] = indexes[i];
	}
	int vertex_count = vertexes.size();
	mVertexes = new VertexData[vertex_count];
	for (int i = 0; i < vertex_count; i++)
	{
		memcpy(mVertexes[i].mPosition, positions[vertexes[i].position_index].v, sizeof(float) * 3);
		memcpy(mVertexes[i].mTexcoord, texcoords[vertexes[i].texcoord_index].v, sizeof(float) * 2);
		memcpy(mVertexes[i].mNormal, normals[vertexes[i].normal_index].v, sizeof(float) * 3);
	}

}
void Model::Draw()
{
	mMaterial->Update();//应用材质
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mIndexCount; i++)
	{
		//纹理和法线要在glVertex3fv前设置
		glTexCoord2f(mVertexes[mIndexes[i]].mTexcoord[0], mVertexes[mIndexes[i]].mTexcoord[1]);
		glNormal3fv(mVertexes[mIndexes[i]].mNormal);
		/*
		glVertex3f(mVertexes[mIndexes[i]].mPosition[0], mVertexes[mIndexes[i]].mPosition[1], mVertexes[mIndexes[i]].mPosition[2]);//注意用得是mIndexes[i]索引
		 */
		 //上面一句代码可以简化来写
		glVertex3fv(mVertexes[mIndexes[i]].mPosition);//注意用得是mIndexes[i]索引

	}
	glEnd();
}
