#pragma once
#include "ILayer.h"
/// @brief 机器使用情况显示
class ComputerUsageLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};