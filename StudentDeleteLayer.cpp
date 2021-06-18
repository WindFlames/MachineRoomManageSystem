#include "StudentDeleteLayer.h"
#include "CommonHelper.h"
#include "StudentSearchLayer.h"
#include "student_list.h"
extern student_list studentCollection;
void StudentDeleteLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ����������������������������������������������������������������������������",
		"    ��         ��ӭ����ѧ��ɾ������       ��",
		"    ����������������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentDeleteLayer::InputHandler() const
{
	out << "���Ȳ�ѯҪɾ��ѧ����" << std::endl;
	StudentSearchLayer const searchlayer;
	auto stu = searchlayer.ObtainDefiniteStudent();
	if (!stu)
	{
		out << "��ѧ�������ڣ�" << std::endl;
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
		out << "ѧ��ɾ���ɹ���" << std::endl;
	}
	return -1;
}