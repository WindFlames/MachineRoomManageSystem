#include "StudentAddLayer.h"
#include "CommonHelper.h"
#include "student.h"
#include "student_list.h"
#include "ConsoleTables.h"
#include "computer.h"

extern student_list studentCollection;
void StudentAddLayer::Display() const
{
	out.clear();
	static const char* const msgDisplay[]{
		"    ����������������������������������������������������������������������������",
		"    ��         ��ӭ����ѧ�����ӽ���       ��",
		"    ����������������������������������������������������������������������������",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentAddLayer::InputHandler() const
{
	/// @brief ѧ����ţ�ѧ�ţ�
	std::string uid;
	/// @brief �༶
	std::string classname;
	/// @brief ����
	std::string name;
	/// @brief ����Ϊ����
	int deposit;
	student* stu = new student();
	out << "������ѧ�ţ�";
	in >> uid;
	auto olds = studentCollection.FindStudentById(uid);
	if (olds != nullptr)
	{
		out << "�Ѿ����ڸ�ѧ�ŵ�ѧ����\n��ѧ����Ϣ��" << std::endl;
		ConsoleTables ctable({ "ѧ��","����","�༶","�ϻ����","�ϻ�ʱ��" ,"��Ԫ��" }, out);

		ctable.AddRow({
			olds->Uid(),
			olds->Name(),
			olds->Classname(),
			(olds->Computerid() == nullptr ? "-" : std::to_string(olds->Computerid()->Uid())),
			olds->Computerid() == nullptr ? "-" : TimeStamp2FormatString(olds->Begintime()),
			std::to_string(olds->Deposit()) });

		ctable.Write();
		return -1;
	}
	out << "������������";
	in >> name;
	out << "������༶��";

	in >> classname;
	out << "��������";
	in >> deposit;
	while (in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		out << "������������";
		in >> deposit;
	}
	stu->ModifyUid(uid);
	stu->ModifyClassname(classname);
	stu->ModifyName(name);
	stu->ModifyDeposit(deposit);
	studentCollection.AddStudent(stu);

	SaveStudentsInfo();
	out << "ѧ����ӳɹ���" << std::endl;
	ConsoleTables ctable({ "ѧ��","����","�༶","��Ԫ��" }, out);

	ctable.AddRow({ stu->Uid(),stu->Name(),stu->Classname() ,std::to_string(stu->Deposit()) });

	ctable.Write();

	return -1;
}