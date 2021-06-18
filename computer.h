#pragma once
#include <string>
#include <ctime>
#include "student.h"
#include "CommonHelper.h"
class student;
/// @brief �������Ϣ��
class computer
{
private:
	/// @brief ��������
	int uid;
	/// @brief �Ƿ�ʹ��
	bool isUsed;
	/// @brief �ϻ�ʱ��
	time_t begintime;
	/// @brief ʹ�õ�ѧ��
	student* studentid;
	/// @brief �ڲ�ʹ�õ�studentid
	std::string studentidInternal;
public:
	computer() : uid(-1), isUsed(false), begintime(-1), studentid(nullptr) {}
	int Uid()const { return uid; }
	bool Used()const { return isUsed; }
	time_t BeginTime()const { return begintime; }
	student* Student()const { return studentid; }
	void Uid(int _uid) { uid = _uid; }
	void Used(int _used) { isUsed = _used; }
	void BeginTime(time_t _begintime) { begintime = _begintime; }
	void Student(student* _student) { studentid = _student; }
	/// @brief ���ѧ������
	void Clear()
	{
		isUsed = false;
		begintime = -1;
		studentid = nullptr;
		studentidInternal = {};
	}
	friend std::ifstream& operator>>(std::ifstream& is, computer* cpt);
	friend std::ofstream& operator<<(std::ofstream& os, computer* cpt);

	friend void Combine();
};