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
		"    ┌────────────────────────────────────┐",
		"    │         欢迎来到学生增加界面       │",
		"    └────────────────────────────────────┘",
	};
	for (size_t i = 0; i < GetArrayLength(msgDisplay); i++)
	{
		out << msgDisplay[i] << std::endl;
	}
}

int StudentAddLayer::InputHandler() const
{
	/// @brief 学生编号（学号）
	std::string uid;
	/// @brief 班级
	std::string classname;
	/// @brief 姓名
	std::string name;
	/// @brief 余额，可为负数
	int deposit;
	student* stu = new student();
	out << "请输入学号：";
	in >> uid;
	auto olds = studentCollection.FindStudentById(uid);
	if (olds != nullptr)
	{
		out << "已经存在该学号的学生！\n该学生信息：" << std::endl;
		ConsoleTables ctable({ "学号","姓名","班级","上机编号","上机时间" ,"余额（元）" }, out);

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
	out << "请输入姓名：";
	in >> name;
	out << "请输入班级：";

	in >> classname;
	out << "请输入余额：";
	in >> deposit;
	while (in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		out << "请重新输入余额：";
		in >> deposit;
	}
	stu->ModifyUid(uid);
	stu->ModifyClassname(classname);
	stu->ModifyName(name);
	stu->ModifyDeposit(deposit);
	studentCollection.AddStudent(stu);

	SaveStudentsInfo();
	out << "学生添加成功！" << std::endl;
	ConsoleTables ctable({ "学号","姓名","班级","余额（元）" }, out);

	ctable.AddRow({ stu->Uid(),stu->Name(),stu->Classname() ,std::to_string(stu->Deposit()) });

	ctable.Write();

	return -1;
}