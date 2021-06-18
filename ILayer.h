#pragma once
#include<iostream>
/// @brief ����ӿڣ������ࣩ
class ILayer
{
protected:
	/// @brief ������
	std::istream& in;
	/// @brief �����
	std::ostream& out;
public:
	ILayer(std::istream& is = std::cin, std::ostream& os = std::cout) :in(is), out(os) {}
	//���������������������ṹ�ƻ�
	virtual ~ILayer() = default;
	//��ʾ����
	virtual void Display()const = 0;
	/// @brief ���봦����
	/// @return ����-1��ʾ�˳��˽��棬����ֵΪ������ʾ
	virtual int InputHandler()const = 0;
};
