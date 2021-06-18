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
		"    ����������������������������������������������������������������������������������������",
		"    ��         ��ӭ����ѧ����Ϣ�޸Ľ���         ��",
		"    ����������������������������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentModifyLayer::InputHandler() const
{
	out << "���Ȳ�ѯҪ�޸�ѧ����" << std::endl;
	StudentSearchLayer searchLayer;
	student* stu = searchLayer.ObtainDefiniteStudent();
	if (stu == nullptr)//ѧ��δ�ҵ�
	{
		out << "δ�ҵ���Ӧѧ�����޷��޸ģ�" << std::endl;
		return -1;
	}
	out << "��������Ҫ�޸ĵ���Ŀ��" << std::endl;
	out << R"(1.ѧ��
2.�༶
3.����
4.�ϻ���������
5.�ϻ�ʱ��
6.���)" << std::endl;

	int op;
	in >> op;
	switch (op)
	{
	case 1:
	{
		out << "��������ѧ�ţ�";
		std::string nuid;
		in >> nuid;
		stu->ModifyUid(nuid);
	}
	break;
	case 2:
	{
		out << "�������°༶��";
		std::string nclass;
		in >> nclass;
		stu->ModifyClassname(nclass);
	}
	break;
	case 3:
	{
		out << "��������������";
		std::string nname;
		in >> nname;
		stu->ModifyName(nname);
	}
	break;
	case 4:
	{
		if (!stu->IsOnline())
		{
			out << "δ�ϻ��������ϻ������޸ģ�";
			return -1;
		}
		out << "���������ϻ���ţ�";
		int cptid;
		in >> cptid;
		auto cpt = computerRoom[cptid];
		if (!cpt)
		{
			out << "δ�ҵ���Ӧ��ŵļ�������޸�ʧ�ܣ�" << std::endl;
		}
		else if (cpt->Used())
		{
			out << "������Ѿ���ʹ�ã��޸�ʧ�ܣ�" << std::endl;
		}
		else
		{
			stu->Computerid()->Clear();//���ԭ�����ӵ�����
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
			out << "δ�ϻ��������ϻ������޸ģ�";
			return -1;
		}
		out << "���������ϻ�ʱ�䣨��ʽ���� �� �� ʱ �֣���";
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
		out << "����������";
		int ndeposit;
		in >> ndeposit;
		stu->ModifyDeposit(ndeposit);
	}
	break;
	default:
		out << "�������!";
		return -1;
	}
	out << "�޸ĳɹ�!" << std::endl;
	SaveStudentsInfo();
	return -1;
}