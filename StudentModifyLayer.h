#pragma once
#include "ILayer.h"
/// @brief ѧ����Ϣ�޸Ľ���
class StudentModifyLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};