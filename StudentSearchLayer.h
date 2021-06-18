#pragma once
#include "ILayer.h"
#include "student.h"
#include <vector>

/// @brief ѧ�����ҽ���
class StudentSearchLayer : public ILayer
{
	/// @brief ��ȡ������ʽ
	/// @return
	int ObtainSearchType(bool includeCptId = true) const;
	/// @brief ��ȡ����ʽ
	/// @return
	int ObtainSortType() const;
	/// @brief ѡ��ȷ����ѧ��
	/// @param stuCount ѧ������
	/// @return ȷ�ϵ�ѧ�����
	int FurtherChoice(int stuCount) const;

	std::vector<student*> ObtainAllStudents(bool includeCptId = true)const;
public:
	void Display()const override;
	int InputHandler()const override;
	//��ȡȷ����ѧ��
	student* ObtainDefiniteStudent(bool includeCptId = true) const;
};
