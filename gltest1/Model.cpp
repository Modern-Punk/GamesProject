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
	struct VertexDefine {//λ�ã��������꣬���߹�ͬ������һ����
		int position_index;
		int texcoord_index;
		int normal_index;
	};
	std::vector<FloatData> positions, texcoords, normals;//���ݳ�
	std::vector<VertexDefine> vertexes;//����1/1/1�������һ���㣬��Quadģ���й���4�������ĵ㣬��face�в鿴
	std::vector<int> indexes;//2���棬ÿ������3���㣬����6��
	std::stringstream ssFileContent((char*)filecontent);//��ʼ����
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if (strlen(szOneLine) > 0) {//���ǿ���
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't')//��������
				{
					ssOneLine >> temp;//ssOneLine���Կո�Ϊ��λ��ָ�������ƶ�,��vt���ȥ
					FloatData fd;
					ssOneLine >> fd.v[0];
					ssOneLine >> fd.v[1];
					texcoords.push_back(fd);//������������ݳ�
				}
				else if (szOneLine[1] == 'n')
				{
					ssOneLine >> temp;
					FloatData fd;
					ssOneLine >> fd.v[0];
					ssOneLine >> fd.v[1];
					ssOneLine >> fd.v[2];
					normals.push_back(fd);//���ߵ����ݳ�
				}
				else
				{
					ssOneLine >> temp;
					FloatData fd;
					ssOneLine >> fd.v[0];
					ssOneLine >> fd.v[1];
					ssOneLine >> fd.v[2];
					positions.push_back(fd);//��λ�õ����ݳ�
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
					vd.position_index = atoi(pos_index_str.c_str()) - 1;//ģ�͵������Ǵ�1��ʼ�ģ�C++�е������Ǵ�0��ʼ�ġ�
					vd.texcoord_index = atoi(texcoord_index_str.c_str()) - 1;
					vd.normal_index = atoi(normal_index_str.c_str()) - 1;
					//ȥ��
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					for (int j = 0; j < nCurrentVertexCount; j++)
					{
						if (vertexes[j].position_index == vd.position_index && vertexes[j].texcoord_index == vd.texcoord_index && vertexes[j].normal_index == vd.normal_index)
						{
							nCurrentVertexIndex = j;//�ҵ��ظ���������
							break;
						}
					}
					if (nCurrentVertexIndex == -1)//δ�ҵ�
					{
						nCurrentVertexIndex = nCurrentVertexCount;
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);//indexes��¼���ǵ������������Щ�����У�ÿ����Ҫ����һ����ġ�
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
	mMaterial->Update();//Ӧ�ò���
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mIndexCount; i++)
	{
		//����ͷ���Ҫ��glVertex3fvǰ����
		glTexCoord2f(mVertexes[mIndexes[i]].mTexcoord[0], mVertexes[mIndexes[i]].mTexcoord[1]);
		glNormal3fv(mVertexes[mIndexes[i]].mNormal);
		/*
		glVertex3f(mVertexes[mIndexes[i]].mPosition[0], mVertexes[mIndexes[i]].mPosition[1], mVertexes[mIndexes[i]].mPosition[2]);//ע���õ���mIndexes[i]����
		 */
		 //����һ�������Լ���д
		glVertex3fv(mVertexes[mIndexes[i]].mPosition);//ע���õ���mIndexes[i]����

	}
	glEnd();
}
