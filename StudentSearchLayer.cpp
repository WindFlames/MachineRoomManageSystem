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
	out << R"(��ѯ��ʽ��
1.ѧ��
2.����
3.�༶)" << std::endl;
	if (includeCptId)
	{
		out << "4.�ϻ����" << std::endl;
	}
	out << "�������ѯ��ʽ��";
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
				out << "������ֲ����޸����⣡���������˳���" << std::endl;
				system("pause");
				exit(-1);
			}
		}

		out << "����������������룺";
	}
}

int StudentSearchLayer::ObtainSortType() const
{
	out << R"(��ѯ��������¼����ѡ������ʽ��
1.��ѧ������
2.���༶����
3.����ʼʱ������
4.��ʱ������)" << std::endl;
	out << "����������ʽ��";
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
				out << "������ֲ����޸����⣡���������˳���" << std::endl;
				system("pause");
				exit(-1);
			}
		}
		out << "����������������룺";
	}
}

int StudentSearchLayer::FurtherChoice(int stuCount) const
{
	out << "��������Ҫ��ѯ��ѧ����ţ�";
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
				out << "������ֲ����޸����⣡���������˳���" << std::endl;
				system("pause");
				exit(-1);
			}
		}
		out << "����������������룺";
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
		out << "������ѧ�ţ�";
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
		out << "������������";
		//���ǵ���������ֿո�����Ҫ��getline
		in.ignore();//ȥ���س�
		std::getline(in, name);
		result = studentCollection.FindStudentByName(name);
	}
	break;
	case 3:
	{
		std::string classname;
		out << "������༶��";
		in.ignore();
		getline(in, classname);
		result = studentCollection.FindStudentByClass(classname);
	}
	break;
	case 4:
		assert(includeCptId);
		int id;
		out << "�����������ţ�" << std::endl;
		while (!(in >> id))
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			out << "��������Ч�ַ������������룺";
		}
		auto cpt = computerRoom[id];
		if (cpt == nullptr)//�����δ�ҵ�
			return { };
		if (cpt->Student() == nullptr)//δ���ϻ�
			return { };
		return { cpt->Student() };
	}

	//ѧ������С��1ֱ�ӷ���
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
		"    ����������������������������������������������������������������������������",
		"    ��        ��ӭ����ѧ�����ҽ���        ��",
		"    ����������������������������������������������������������������������������",
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
		out << "�Ҳ�����Ӧѧ����" << std::endl;
		return -1;
	}
	out << "�������з���������ѧ����" << std::endl;
	ConsoleTables ctable({ "ѧ��","����","�༶","�ϻ����","�ϻ�ʱ��" }, out);

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
	out << "�������з���������ѧ����" << std::endl;
	ConsoleTables ctable({ "���","ѧ��","����","�༶","�ϻ����","�ϻ�ʱ��" }, out);
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