#include "model.h"
#include "utils.h"

Model::Model() {

}

// 模型初始化
void Model::Init(const char* modelPath)
{
	int nFileSize = 0;
	unsigned char* fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	std::stringstream ssFileContent((char*)fileContent);
	char szOneLine[256];
	// 流中没有数据了
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		// 读取每行的数据
		ssFileContent.getline(szOneLine, 256);
		// 当前行不为空的时候
		if (strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				// 当前是纹理坐标
				if (szOneLine[1] == 't')
				{
					printf("texcoord : %s\n", szOneLine);
				}
				else if (szOneLine[1] == 'n') // 当前是法线
				{
					printf("normal : %s\n", szOneLine);
				}
				else // 当前是物体的坐标位置
				{
					printf("position : %s\n", szOneLine);
				}
			}
			else if (szOneLine[0] == 'f')  // 当前是索引
			{
				printf("draw command : %s\n", szOneLine);
			}
		}
		delete fileContent;
	}
}