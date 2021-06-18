#include "RevertLayer.h"
#include "StudentSearchLayer.h"
#include "CommonHelper.h"

void RevertLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ┌─────────────────────────────────┐",
		"    │         欢迎来到下机界面        │",
		"    └─────────────────────────────────┘",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int RevertLayer::InputHandler() const
{
	out << "请先查询下机学生：" << std::endl;
	StudentSearchLayer searchlayer;
	auto stu = searchlayer.ObtainDefiniteStudent();
	if (!stu)
	{
		out << "没有找到学生！" << std::endl;
	}
	else if (!stu->IsOnline())
	{
		out << '\"' << stu->Name() << "\" 同学还未上机！" << std::endl;
	}
	else
	{
		time_t now = time(nullptr);
		out << "上机费用：" << stu->CalculateCost(now) << "元" << std::endl;
		stu->SignOut(now);
		out << "剩余金额：" << stu->Deposit() << "元" << std::endl;
		if (stu->Deposit() <= 0)
			out << "警告：上机费用已不足，请及时充值！" << std::endl;
		SaveComputerRoom();
		SaveStudentsInfo();
	}
	return -1;
}