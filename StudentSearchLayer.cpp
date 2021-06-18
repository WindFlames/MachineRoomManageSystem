#include "StudentSearchLayer.h"
#include "student.h"
#include <vector>
#include "student_list.h"
#include <algorithm>
#include <ctime>
#include "ConsoleTables.h"
#include<string>
#include "computer_room.h"
extern student_list studentCollection;
extern computer_room computerRoom;
int StudentSearchLayer::ObtainSearchType(bool includeCptId) const
{
	out << R"(查询方式：
1.学号
2.姓名
3.班级)" << std::endl;
	if (includeCptId)
	{
		out << "4.上机编号" << std::endl;
	}
	out << "请输入查询方式：";
	int opIn;
	while (true)
	{
		in >> opIn;
		if (opIn == -1 || opIn >= 1 && opIn <= 3 || includeCptId && opIn == 4)
			return opIn;
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

		out << "输入错误请重新输入：";
	}
}

int StudentSearchLayer::ObtainSortType() const
{
	out << R"(查询到多条记录，请选择排序方式：
1.按学号排序
2.按班级排序
3.按开始时间排序
4.按时长排序)" << std::endl;
	out << "请输入排序方式：";
	int opIn;
	while (true)
	{
		in >> opIn;
		if (opIn == -1 || opIn >= 1 && opIn <= 4)
			return opIn;
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
		out << "输入错误请重新输入：";
	}
}

int StudentSearchLayer::FurtherChoice(int stuCount) const
{
	out << "请输入你要查询的学生编号：";
	int opIn;
	while (true)
	{
		in >> opIn;
		if (opIn == -1 || opIn >= 1 && opIn <= stuCount)
			return opIn;
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
		out << "输入错误请重新输入：";
	}
}

std::vector<student*> StudentSearchLayer::ObtainAllStudents(bool includeCptId)const
{
	std::vector<student*> result;
	int type = ObtainSearchType(includeCptId);
	switch (type)
	{
	case -1:
		return { };
	case 1:
	{
		std::string id;
		out << "请输入学号：";
		in >> id;
		auto p = studentCollection.FindStudentById(id);
		if (p == nullptr)
		{
			return {};
		}
		return { p };
	}
	case 2:
	{
		std::string name;
		out << "请输入姓名：";
		//考虑到姓名会出现空格，所以要用getline
		in.ignore();//去掉回车
		std::getline(in, name);
		result = studentCollection.FindStudentByName(name);
	}
	break;
	case 3:
	{
		std::string classname;
		out << "请输入班级：";
		in.ignore();
		getline(in, classname);
		result = studentCollection.FindStudentByClass(classname);
	}
	break;
	case 4:
		assert(includeCptId);
		int id;
		out << "请输入机器编号：" << std::endl;
		while (!(in >> id))
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			out << "输入了无效字符！请重新输入：";
		}
		auto cpt = computerRoom[id];
		if (cpt == nullptr)//计算机未找到
			return { };
		if (cpt->Student() == nullptr)//未被上机
			return { };
		return { cpt->Student() };
	}

	//学生数量小于1直接返回
	if (result.size() <= 1)
	{
		return result;
	}

	type = ObtainSortType();

	switch (type)
	{
	case -1:
		return { };
	case 1:
		std::sort(result.begin(), result.end(), [](student* s1, student* s2) {return s1->Uid() < s2->Uid(); });
		break;
	case 2:
		std::sort(result.begin(), result.end(), [](student* s1, student* s2) {return s1->Classname() < s2->Classname(); });
		break;
	case 3:
		std::sort(result.begin(), result.end(), [](student* s1, student* s2) {return s1->Begintime() < s2->Begintime(); });
		break;
	case 4:
		time_t now = time(nullptr);
		std::sort(result.begin(), result.end(), [](student* s1, student* s2) {
			if (s1->Begintime() == -1 || s2->Begintime() == -1)return s1->Begintime() != -1;
			return s1->Begintime() < s2->Begintime(); });
		break;
	}
	return result;
}

void StudentSearchLayer::Display() const
{
	static const char* const msgDisplay[]{
		"    ┌────────────────────────────────────┐",
		"    │        欢迎来到学生查找界面        │",
		"    └────────────────────────────────────┘",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentSearchLayer::InputHandler() const
{
	auto stucoll = ObtainAllStudents(true);
	if (stucoll.empty())
	{
		out << "找不到对应学生！" << std::endl;
		return -1;
	}
	out << "这是所有符合条件的学生：" << std::endl;
	ConsoleTables ctable({ "学号","姓名","班级","上机编号","上机时间" }, out);

	for (auto i : stucoll)
	{
		ctable.AddRow({
			i->Uid(),
			i->Name(),
			i->Classname(),
			(i->Computerid() == nullptr ? "-" : std::to_string(i->Computerid()->Uid())),
			i->Computerid() == nullptr ? "-" : TimeStamp2FormatString(i->Begintime()) });
	}
	ctable.Write();
	return -1;
}

student* StudentSearchLayer::ObtainDefiniteStudent(bool includeCptId) const
{
	auto stucoll = ObtainAllStudents(includeCptId);
	if (stucoll.empty())
	{
		return nullptr;
	}

	if (stucoll.size() == 1)
	{
		return stucoll.front();
	}
	out << "这是所有符合条件的学生：" << std::endl;
	ConsoleTables ctable({ "编号","学号","姓名","班级","上机编号","上机时间" }, out);
	int index = 1;
	for (auto i : stucoll)
	{
		ctable.AddRow({
			std::to_string(index++),
			i->Uid(),
			i->Name(),
			i->Classname(),
			(i->Computerid() == nullptr ? "-" : std::to_string(i->Computerid()->Uid())),
			i->Computerid() == nullptr ? "-" : TimeStamp2FormatString(i->Begintime()) });
	}
	ctable.Write();
	index = FurtherChoice(static_cast<int>(stucoll.size()));
	if (index == -1)return nullptr;
	return  stucoll[index - 1];
}