#pragma once
#include "ILayer.h"
/// @brief 学生信息修改界面
class StudentModifyLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};