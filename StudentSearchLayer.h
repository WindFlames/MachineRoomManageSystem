#pragma once
#include "ILayer.h"
#include "student.h"
#include <vector>

/// @brief 学生查找界面
class StudentSearchLayer : public ILayer
{
	/// @brief 获取搜索方式
	/// @return
	int ObtainSearchType(bool includeCptId = true) const;
	/// @brief 获取排序方式
	/// @return
	int ObtainSortType() const;
	/// @brief 选择确定的学生
	/// @param stuCount 学生数量
	/// @return 确认的学生序号
	int FurtherChoice(int stuCount) const;

	std::vector<student*> ObtainAllStudents(bool includeCptId = true)const;
public:
	void Display()const override;
	int InputHandler()const override;
	//读取确定的学生
	student* ObtainDefiniteStudent(bool includeCptId = true) const;
};
