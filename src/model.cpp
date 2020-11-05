#include "model.h"
#include "utils.h"

Model::Model() {

}

// 模型初始化
void Model::Init(const char* modelPath)
{
	// 保存每行的信息 顶点数据源
	struct FloatData {
		float v[3];
	};

	int nFileSize = 0;
	unsigned char* fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	std::vector<FloatData> positions, texcoords, normals;
	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;
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
				std::stringstream ssOneLine(szOneLine);
				// 当前是纹理坐标
				if (szOneLine[1] == 't')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					printf("texcoord : %f, %f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n') // 当前是法线
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					printf("normal : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else // 当前是物体的坐标位置
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					printf("position : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
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