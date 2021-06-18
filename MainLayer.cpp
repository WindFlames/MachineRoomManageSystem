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
		"    ┌──────────────────────────────────────┐",
		"    │         欢迎进入机房管理系统         │",
		"    │         1.计算机使用情况查询         │",
		"    │         2.增加学生                   │",
		"    │         3.删除学生                   │",
		"    │         4.修改学生信息               │",
		"    │         5.查询学生信息               │",
		"    │         6.显示全部学生信息           │",
		"    │         7.上机	                   │",
		"    │         8.下机                       │",
		"    │                    版权所有侵权必究  │",
		"    └──────────────────────────────────────┘",
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
	out << "               请选择（输入对应编号,-1为结束）：";
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
		out << "输入操作符错误，请重新操作!" << std::endl;
		if (in.fail())
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (in.fail())
			{
				out << "程序出现不可修复问题！程序立即退出。" << std::endl;
				system("pause");
				exit(-1);
			}
		}
		system("pause");
	}

	if (layer)
	{
		DisplayLayer(layer);
		delete layer;//Display()函数内置等待过程，所以可以保证显示完全
		layer = nullptr;
	}
	return 0;
}