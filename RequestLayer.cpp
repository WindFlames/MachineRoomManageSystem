#include "RequestLayer.h"
#include "CommonHelper.h"
#include "StudentSearchLayer.h"
#include "computer_room.h"
extern computer_room computerRoom;
void RequestLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ┌─────────────────────────────────┐",
		"    │         欢迎来到上机界面        │",
		"    └─────────────────────────────────┘",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int RequestLayer::InputHandler() const
{
	out << "请先查询上机学生：" << std::endl;
	StudentSearchLayer searchlayer;
	auto stu = searchlayer.ObtainDefiniteStudent(false);

	if (stu == nullptr)
	{
		out << "没有找到学生！" << std::endl;
	}
	else if (stu->IsOnline())
	{
		out << "学生 \"" << stu->Name() << "\" 已经上机了，机器编号：" << stu->Computerid()->Uid()
			<< " 上机时间：" << TimeStamp2FormatString(stu->Begintime()) << std::endl;
	}
	else if (stu->Deposit() <= 0)
	{
		out << "学生 \"" << stu->Name() << "\" 余额不足，请充值后再选择上机。\n当前余额：" << stu->Deposit() << " 元" << std::endl;
	}
	else
	{
		auto cpt = computerRoom.FindRestComputer();
		if (cpt)
		{
			stu->SignIn(cpt);
			out << "上机成功!" << std::endl;
			out << "机器编号为:" << cpt->Uid() << std::endl;
			SaveComputerRoom();
			SaveStudentsInfo();
		}
		else
		{
			out << "无剩余机器，上机失败！" << std::endl;
		}
	}
	return -1;
}