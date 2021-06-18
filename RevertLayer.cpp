#include "RevertLayer.h"
#include "StudentSearchLayer.h"
#include "CommonHelper.h"

void RevertLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ����������������������������������������������������������������������",
		"    ��         ��ӭ�����»�����        ��",
		"    ����������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int RevertLayer::InputHandler() const
{
	out << "���Ȳ�ѯ�»�ѧ����" << std::endl;
	StudentSearchLayer searchlayer;
	auto stu = searchlayer.ObtainDefiniteStudent();
	if (!stu)
	{
		out << "û���ҵ�ѧ����" << std::endl;
	}
	else if (!stu->IsOnline())
	{
		out << '\"' << stu->Name() << "\" ͬѧ��δ�ϻ���" << std::endl;
	}
	else
	{
		time_t now = time(nullptr);
		out << "�ϻ����ã�" << stu->CalculateCost(now) << "Ԫ" << std::endl;
		stu->SignOut(now);
		out << "ʣ���" << stu->Deposit() << "Ԫ" << std::endl;
		if (stu->Deposit() <= 0)
			out << "���棺�ϻ������Ѳ��㣬�뼰ʱ��ֵ��" << std::endl;
		SaveComputerRoom();
		SaveStudentsInfo();
	}
	return -1;
}