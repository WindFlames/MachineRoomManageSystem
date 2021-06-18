#include <iomanip>
#include <sstream>

#include "CommonHelper.h"
#include "computer_room.h"
#include "ILayer.h"
#include "student_list.h"
extern computer_room computerRoom;
extern student_list studentCollection;

static const char* computerPath = "Computers.txt", * studentPath = "Students.txt";
void Initialization()
{
	computerRoom.ReadFromText(computerPath);
	studentCollection.ReadFromText(studentPath);
	Combine();
}
void Deinitialization()
{
	computerRoom.WriteToText(computerPath);
	studentCollection.WriteToText(studentPath);
}
void SaveComputerRoom()
{
	computerRoom.WriteToText(computerPath);
}
void SaveStudentsInfo()
{
	studentCollection.WriteToText(studentPath);
}

int DisplayLayer(ILayer* layer)
{
	if (layer == nullptr)throw std::invalid_argument("layer不能为null!");
	int ret = 0;
	do
	{
		CleanScreen();
		layer->Display();
		ret = layer->InputHandler();
		if (ret == -1)
			system("pause");
	} while (ret >= 0);
	return ret;
}
void Combine()
{
	//将学生和机器关联起来
	for (auto cur = studentCollection.begin(); cur != studentCollection.end(); cur = cur->next)
	{
		if (cur->value->computeridInternal != -1)
		{
			auto cpt = computerRoom[cur->value->computeridInternal];
			cur->value->ModifyComputerid(cpt);
			cur->value->ModifyIsOnline(true);

			cpt->Student(cur->value);
			cpt->Used(true);
			cpt->BeginTime(cur->value->Begintime());
		}
	}
}

std::string TimeStamp2FormatString(time_t t)
{
	if (t == -1)return "-";
	//0000-00-00 00:00:00
	tm lt{};
	localtime_s(&lt, &t);
	std::stringstream ss;
	ss.fill('0');
	ss << std::setw(4) << lt.tm_year + 1900;
	ss << '-';
	ss << std::setw(2) << lt.tm_mon + 1;
	ss << '-';
	ss << std::setw(2) << lt.tm_mday;
	ss << ' ';
	ss << std::setw(2) << lt.tm_hour;
	ss << ':';
	ss << std::setw(2) << lt.tm_min;
	ss << ':';
	ss << std::setw(2) << lt.tm_sec;
	return ss.str();
}