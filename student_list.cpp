#include "student_list.h"

void student_list::ReadFromText(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())throw std::invalid_argument("文件" + filename + "不存在。");
	//判断文件是否为空
	char c;
	ifs >> c;
	if (ifs.eof())
	{
		ifs.close();
		return;
	}
	ifs.seekg(0, std::ios::_Seekbeg);

	int cnt;//数据条数
	ifs >> cnt;

	for (int i = 0; i < cnt; i++)
	{
		student* stu = new student;
		if (!(ifs >> stu))
		{
			throw std::invalid_argument("文件" + filename + "数据错误！");
		}
		AddToTail(stu);
	}

	ifs.close();
}

void student_list::WriteToText(const std::string& filename) const
{
	std::ofstream ofs(filename);
	if (!ofs.is_open())throw std::invalid_argument("文件" + filename + "创建失败。");
	ofs << Size() << std::endl;//写入数据条数
	for (auto cur = begin(); cur != end(); cur = cur->next)
	{
		ofs << cur->value << std::endl;
	}
	ofs.close();
}

student* student_list::FindStudentById(const std::string& uid) const noexcept(false)
{
	if (uid.empty())throw std::invalid_argument("学号不能为空！");
	for (auto cur = begin(); cur != end(); cur = cur->next)
	{
		if (cur->value->Uid() == uid)
			return cur->value;
	}

	return nullptr;
}

std::vector<student*> student_list::FindStudentByName(const std::string& name) const
{
	std::vector<student*> result;
	for (auto cur = begin(); cur != end(); cur = cur->next)
	{
		if (cur->value->Name() == name)
			result.push_back(cur->value);
	}
	return result;
}

std::vector<student*> student_list::FindStudentByClass(const std::string& classname) const
{
	std::vector<student*> result;
	for (auto cur = begin(); cur != end(); cur = cur->next)
	{
		if (cur->value->Classname() == classname)
			result.push_back(cur->value);
	}
	return result;
}