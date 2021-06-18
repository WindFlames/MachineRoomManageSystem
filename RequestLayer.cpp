#include "RequestLayer.h"
#include "CommonHelper.h"
#include "StudentSearchLayer.h"
#include "computer_room.h"
extern computer_room computerRoom;
void RequestLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ����������������������������������������������������������������������",
		"    ��         ��ӭ�����ϻ�����        ��",
		"    ����������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int RequestLayer::InputHandler() const
{
	out << "���Ȳ�ѯ�ϻ�ѧ����" << std::endl;
	StudentSearchLayer searchlayer;
	auto stu = searchlayer.ObtainDefiniteStudent(false);

	if (stu == nullptr)
	{
		out << "û���ҵ�ѧ����" << std::endl;
	}
	else if (stu->IsOnline())
	{
		out << "ѧ�� \"" << stu->Name() << "\" �Ѿ��ϻ��ˣ�������ţ�" << stu->Computerid()->Uid()
			<< " �ϻ�ʱ�䣺" << TimeStamp2FormatString(stu->Begintime()) << std::endl;
	}
	else if (stu->Deposit() <= 0)
	{
		out << "ѧ�� \"" << stu->Name() << "\" ���㣬���ֵ����ѡ���ϻ���\n��ǰ��" << stu->Deposit() << " Ԫ" << std::endl;
	}
	else
	{
		auto cpt = computerRoom.FindRestComputer();
		if (cpt)
		{
			stu->SignIn(cpt);
			out << "�ϻ��ɹ�!" << std::endl;
			out << "�������Ϊ:" << cpt->Uid() << std::endl;
			SaveComputerRoom();
			SaveStudentsInfo();
		}
		else
		{
			out << "��ʣ��������ϻ�ʧ�ܣ�" << std::endl;
		}
	}
	return -1;
}