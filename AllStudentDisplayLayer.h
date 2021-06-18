#pragma once
#include "ILayer.h"
/// @brief 全部学生信息显示界面
class AllStudentDisplayLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};
