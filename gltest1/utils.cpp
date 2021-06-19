#include "utils.h"
unsigned char* LoadFileContent(const char*filepath)
{
	unsigned char* fileContent = nullptr;
	FILE* pFile = fopen(filepath, "rb");
	if (pFile)//如果文件打开成功
	{
		//read
		fseek(pFile,0,SEEK_END);//将文件指针移到尾部
		int nLen = ftell(pFile);//文件大小为nLen
		if (nLen > 0)
		{
			rewind(pFile);//指针移到文件头
			fileContent = new unsigned char[nLen+1];//文件最后补0，故+1
			fread(fileContent,sizeof(unsigned char),nLen,pFile);
			fileContent[nLen] = '\0';
		}
		fclose(pFile);
	}
	return fileContent;
}