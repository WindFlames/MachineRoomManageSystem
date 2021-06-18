#pragma once
#include <string>
#include <ctime>
#include "student.h"
#include "CommonHelper.h"
class student;
/// @brief 计算机信息类
class computer
{
private:
	/// @brief 计算机编号
	int uid;
	/// @brief 是否被使用
	bool isUsed;
	/// @brief 上机时间
	time_t begintime;
	/// @brief 使用的学生
	student* studentid;
	/// @brief 内部使用的studentid
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
	/// @brief 清除学生数据
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