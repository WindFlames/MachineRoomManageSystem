#pragma once
#include "ILayer.h"
/// @brief ȫ��ѧ����Ϣ��ʾ����
class AllStudentDisplayLayer :public ILayer
{
public:
	void Display()const override;
	int InputHandler()const override;
};
