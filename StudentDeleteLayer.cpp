#include "StudentDeleteLayer.h"
#include "CommonHelper.h"
#include "StudentSearchLayer.h"
#include "student_list.h"
extern student_list studentCollection;
void StudentDeleteLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ┌────────────────────────────────────┐",
		"    │         欢迎来到学生删除界面       │",
		"    └────────────────────────────────────┘",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentDeleteLayer::InputHandler() const
{
	out << "请先查询要删除学生：" << std::endl;
	StudentSearchLayer const searchlayer;
	auto stu = searchlayer.ObtainDefiniteStudent();
	if (!stu)
	{
		out << "该学生不存在！" << std::endl;
	}
	else
	{
		if (stu->IsOnline())
		{
			stu->SignOut();
		}
		studentCollection.DeleteStudent(stu);
		SaveComputerRoom();
		SaveStudentsInfo();
		out << "学生删除成功！" << std::endl;
	}
	return -1;
}