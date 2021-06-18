#include "MainLayer.h"
#include "CommonHelper.h"
#include "ComputerUsageLayer.h"
#include "StudentModifyLayer.h"
#include "StudentSearchLayer.h"
#include "AllStudentDisplayLayer.h"
#include "RevertLayer.h"
#include "RequestLayer.h"
#include "StudentAddLayer.h"
#include "StudentDeleteLayer.h"

MainLayer::MainLayer()
{
}

void MainLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ��������������������������������������������������������������������������������",
		"    ��         ��ӭ�����������ϵͳ         ��",
		"    ��         1.�����ʹ�������ѯ         ��",
		"    ��         2.����ѧ��                   ��",
		"    ��         3.ɾ��ѧ��                   ��",
		"    ��         4.�޸�ѧ����Ϣ               ��",
		"    ��         5.��ѯѧ����Ϣ               ��",
		"    ��         6.��ʾȫ��ѧ����Ϣ           ��",
		"    ��         7.�ϻ�	                   ��",
		"    ��         8.�»�                       ��",
		"    ��                    ��Ȩ������Ȩ�ؾ�  ��",
		"    ��������������������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int MainLayer::InputHandler() const
{
	bool receiveRightAnswer = true;
	int opId;
	ILayer* layer = nullptr;
	out << "               ��ѡ�������Ӧ���,-1Ϊ��������";
	in >> opId;

	switch (opId)
	{
	case -1:
		return -1;
	case 1:
		layer = new ComputerUsageLayer();
		break;
	case 2:
		layer = new StudentAddLayer();
		break;
	case 3:
		layer = new StudentDeleteLayer();
		break;
	case 4:
		layer = new StudentModifyLayer();
		break;
	case 5:
		layer = new StudentSearchLayer();
		break;
	case 6:
		layer = new AllStudentDisplayLayer();
		break;
		//case 5:
		//	layer = new ChargeLayer();
		//	break;
	case 7:
		layer = new RequestLayer();
		break;
	case 8:
		layer = new RevertLayer();
		break;
	default:
		out << "������������������²���!" << std::endl;
		if (in.fail())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (in.fail())
			{
				out << "������ֲ����޸����⣡���������˳���" << std::endl;
				system("pause");
				exit(-1);
			}
		}
		system("pause");
	}

	if (layer)
	{
		DisplayLayer(layer);
		delete layer;//Display()�������õȴ����̣����Կ��Ա�֤��ʾ��ȫ
		layer = nullptr;
	}
	return 0;
}