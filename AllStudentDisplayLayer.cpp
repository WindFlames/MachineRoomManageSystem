#include <string>

#include "AllStudentDisplayLayer.h"
#include "CommonHelper.h"
#include "ConsoleTables.h"
#include "student_list.h"
#include "computer.h"
extern student_list studentCollection;
void AllStudentDisplayLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ����������������������������������������������������������������������������������������",
		"    ��         ��ӭ����ѧ����Ϣչʾ����         ��",
		"    ����������������������������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int AllStudentDisplayLayer::InputHandler() const
{
	//�������ʽ
	out << R"(��ѯ��������¼����ѡ������ʽ��
1.��ѧ������
2.���༶����
3.����ʼʱ������)" << std::endl;
	out << "����������ʽ��";
	int type;
	while (true)
	{
		in >> type;
		if (type == -1)return -1;
		if (type >= 1 && type <= 3)
			break;
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
	switch (type)
	{
	case 1:
		studentCollection.Sort([](student* s1, student* s2) {return s1->Uid() < s2->Uid(); });
		break;
	case 2:
		studentCollection.Sort([](student* s1, student* s2) {return s1->Classname() < s2->Classname(); });
		break;
	case 3:
		studentCollection.Sort([](student* s1, student* s2) {
			if (s1->Begintime() == -1 || s2->Begintime() == -1)return s1->Begintime() != -1;
			return s1->Begintime() < s2->Begintime(); });
		break;
	}
	ConsoleTables ctable({ "ѧ��","����","�༶","�Ƿ��ϻ�","�ϻ����","�ϻ�ʱ��" ,"��Ԫ��" }, out);

	for (auto cur = studentCollection.begin(); cur != studentCollection.end(); cur = cur->next)
	{
		ctable.AddRow({
			cur->value->Uid(),
			cur->value->Name(),
			cur->value->Classname(),
			Bool2String(cur->value->IsOnline()),
			(cur->value->IsOnline() ? std::to_string(cur->value->Computerid()->Uid()) : "-"),
			(cur->value->IsOnline() ? TimeStamp2FormatString(cur->value->Begintime()) : "-"),
			std::to_string(cur->value->Deposit()) });
	}
	ctable.Write();
	return -1;
}