#include "utils.h"
unsigned char* LoadFileContent(const char*filepath)
{
	unsigned char* fileContent = nullptr;
	FILE* pFile = fopen(filepath, "rb");
	if (pFile)//����ļ��򿪳ɹ�
	{
		//read
		fseek(pFile,0,SEEK_END);//���ļ�ָ���Ƶ�β��
		int nLen = ftell(pFile);//�ļ���СΪnLen
		if (nLen > 0)
		{
			rewind(pFile);//ָ���Ƶ��ļ�ͷ
			fileContent = new unsigned char[nLen+1];//�ļ����0����+1
			fread(fileContent,sizeof(unsigned char),nLen,pFile);
			fileContent[nLen] = '\0';
		}
		fclose(pFile);
	}
	return fileContent;
}