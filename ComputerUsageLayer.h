#pragma once
#include "ILayer.h"
/// @brief ����ʹ�������ʾ
class ComputerUsageLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};