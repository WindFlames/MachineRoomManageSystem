#pragma once
#include "ILayer.h"
/// @brief �ϻ�����
class RequestLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};