#pragma once
#include "ILayer.h"
class StudentAddLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};
