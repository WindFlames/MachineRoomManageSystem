#pragma once
#include "ILayer.h"
class RevertLayer : public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};
