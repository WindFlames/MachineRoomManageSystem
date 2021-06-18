#pragma once
#include "ILayer.h"
/// @brief 上机界面
class RequestLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};