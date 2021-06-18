#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <cassert>
class computer;
/// @brief ѧ����Ϣ��
class student
{
private:
	/// @brief ѧ����ţ�ѧ�ţ�
	std::string uid;
	/// @brief �༶
	std::string classname;
	/// @brief ����
	std::string name;
	/// @brief �Ƿ��ϻ�
	bool isOnline;
	/// @brief �ϻ��ļ�������,isOnlineΪtrueʱ��Ч
	computer* computerid;
	/// @brief �ڲ�ʹ�õ�computerid
	int computeridInternal{ 0 };
	/// @brief �ϻ�ʱ��(��������ʱ��)
	time_t begintime;
	/// @brief ����Ϊ����
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
	/// @brief �ϻ�
	/// @param machine �ϻ�ѧ��
	/// @return �Ƿ�ɹ��ϻ�
	bool SignIn(computer* machine);

	/// @brief �»�
	/// @return �Ƿ�ɹ��»�
	bool SignOut();
	/// @brief �»�
	/// @param offtime �»�ʱ��
	/// @return �Ƿ�ɹ��»�
	bool SignOut(time_t offtime);

	/// @brief ���㵽now���ϻ���
	/// @param now ��ǰʱ���
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