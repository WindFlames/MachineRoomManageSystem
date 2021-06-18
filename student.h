#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <cassert>
class computer;
/// @brief 学生信息类
class student
{
private:
	/// @brief 学生编号（学号）
	std::string uid;
	/// @brief 班级
	std::string classname;
	/// @brief 姓名
	std::string name;
	/// @brief 是否上机
	bool isOnline;
	/// @brief 上机的计算机编号,isOnline为true时有效
	computer* computerid;
	/// @brief 内部使用的computerid
	int computeridInternal{ 0 };
	/// @brief 上机时间(格林尼治时间)
	time_t begintime;
	/// @brief 余额，可为负数
	int deposit;
public:
	student() : uid(""), classname(""), name(""), isOnline(false), computerid(nullptr), begintime(-1), deposit(-1) {}

	std::string Uid() const { return uid; }
	std::string Classname() const { return classname; }
	std::string Name() const { return name; }
	bool IsOnline() const { if (isOnline) assert(computerid); return isOnline && computerid; }
	computer* Computerid() const { return computerid; }
	time_t Begintime() const { return begintime; }
	int Deposit() const { return deposit; }
	/// @brief 上机
	/// @param machine 上机学生
	/// @return 是否成功上机
	bool SignIn(computer* machine);

	/// @brief 下机
	/// @return 是否成功下机
	bool SignOut();
	/// @brief 下机
	/// @param offtime 下机时间
	/// @return 是否成功下机
	bool SignOut(time_t offtime);

	/// @brief 计算到now的上机费
	/// @param now 当前时间戳
	/// @return
	int CalculateCost(time_t now) const;
	void ModifyUid(const std::string& uid) { this->uid = uid; }
	void ModifyClassname(const  std::string& classname) { this->classname = classname; }
	void ModifyName(const std::string& name) { this->name = name; }
	void ModifyIsOnline(bool isOnline) { this->isOnline = isOnline; }
	void ModifyComputerid(computer* computerid) { this->computerid = computerid; }
	void ModifyBegintime(time_t begintime) { this->begintime = begintime; }
	void ModifyDeposit(int deposit) { this->deposit = deposit; }

	friend std::ifstream& operator>>(std::ifstream& is, student* stu);
	friend std::ofstream& operator<<(std::ofstream& os, student* stu);

	friend void Combine();
};