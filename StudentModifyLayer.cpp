#include "StudentModifyLayer.h"
#include "CommonHelper.h"
#include "StudentSearchLayer.h"
#include "computer_room.h"
#include "student_list.h"
extern computer_room computerRoom;
void StudentModifyLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ┌──────────────────────────────────────────┐",
		"    │         欢迎来到学生信息修改界面         │",
		"    └──────────────────────────────────────────┘",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentModifyLayer::InputHandler() const
{
	out << "请先查询要修改学生：" << std::endl;
	StudentSearchLayer searchLayer;
	student* stu = searchLayer.ObtainDefiniteStudent();
	if (stu == nullptr)//学生未找到
	{
		out << "未找到对应学生，无法修改！" << std::endl;
		return -1;
	}
	out << "请输入你要修改的项目：" << std::endl;
	out << R"(1.学号
2.班级
3.姓名
4.上机计算机编号
5.上机时间
6.余额)" << std::endl;

	int op;
	in >> op;
	switch (op)
	{
	case 1:
	{
		out << "请输入新学号：";
		std::string nuid;
		in >> nuid;
		stu->ModifyUid(nuid);
	}
	break;
	case 2:
	{
		out << "请输入新班级：";
		std::string nclass;
		in >> nclass;
		stu->ModifyClassname(nclass);
	}
	break;
	case 3:
	{
		out << "请输入新姓名：";
		std::string nname;
		in >> nname;
		stu->ModifyName(nname);
	}
	break;
	case 4:
	{
		if (!stu->IsOnline())
		{
			out << "未上机，请先上机后再修改！";
			return -1;
		}
		out << "请输入新上机编号：";
		int cptid;
		in >> cptid;
		auto cpt = computerRoom[cptid];
		if (!cpt)
		{
			out << "未找到对应编号的计算机，修改失败！" << std::endl;
		}
		else if (cpt->Used())
		{
			out << "计算机已经被使用，修改失败！" << std::endl;
		}
		else
		{
			stu->Computerid()->Clear();//清除原来机子的数据
			stu->ModifyComputerid(cpt);
			cpt->Used(true);
			cpt->Student(stu);
			cpt->BeginTime(stu->Begintime());
		}
	}
	break;
	case 5:
	{
		if (!stu->IsOnline())
		{
			out << "未上机，请先上机后再修改！";
			return -1;
		}
		out << "请输入新上机时间（格式：年 月 日 时 分）：";
		int year, month, day, hour, min;
		in >> year >> month >> day >> hour >> min;
		tm t{};
		t.tm_year = year - 1900;
		t.tm_mon = month - 1;
		t.tm_mday = day;
		t.tm_hour = hour;
		t.tm_min = min;
		t.tm_sec = 0;
		time_t const tt = mktime(&t);
		stu->ModifyBegintime(tt);
		stu->Computerid()->BeginTime(tt);
	}
	break;
	case 6:
	{
		out << "请输入新余额：";
		int ndeposit;
		in >> ndeposit;
		stu->ModifyDeposit(ndeposit);
	}
	break;
	default:
		out << "输入错误!";
		return -1;
	}
	out << "修改成功!" << std::endl;
	SaveStudentsInfo();
	return -1;
}