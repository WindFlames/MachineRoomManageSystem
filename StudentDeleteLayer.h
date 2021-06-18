#pragma once
#include "ILayer.h"
class StudentDeleteLayer :
	public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};
