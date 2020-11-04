#include "model.h"
#include "utils.h"

Model::Model() {

}

// ģ�ͳ�ʼ��
void Model::Init(const char* modelPath)
{
	int nFileSize = 0;
	unsigned char* fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent == nullptr)
		return;
	std::stringstream ssFileContent((char*)fileContent);
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
				// ��ǰ����������
				if (szOneLine[1] == 't')
				{
					printf("texcoord : %s\n", szOneLine);
				}
				else if (szOneLine[1] == 'n') // ��ǰ�Ƿ���
				{
					printf("normal : %s\n", szOneLine);
				}
				else // ��ǰ�����������λ��
				{
					printf("position : %s\n", szOneLine);
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