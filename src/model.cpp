#include "model.h"
#include "utils.h"

Model::Model() {

}

// ģ�ͳ�ʼ��
void Model::Init(const char* modelPath)
{
	// ����ÿ�е���Ϣ ��������Դ
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
	// ����û��������
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		// ��ȡÿ�е�����
		ssFileContent.getline(szOneLine, 256);
		// ��ǰ�в�Ϊ�յ�ʱ��
		if (strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);
				// ��ǰ����������
				if (szOneLine[1] == 't')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					printf("texcoord : %f, %f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n') // ��ǰ�Ƿ���
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					printf("normal : %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else // ��ǰ�����������λ��
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
			else if (szOneLine[0] == 'f')  // ��ǰ������
			{
				printf("draw command : %s\n", szOneLine);
			}
		}
		delete fileContent;
	}
}