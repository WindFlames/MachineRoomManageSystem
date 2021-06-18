#pragma once
#include "ILayer.h"

class MainLayer :public ILayer
{
public:
	MainLayer();
	void Display()const override;
	int InputHandler()const override;
};
