#include <ctime>
#include "computer.h"
#include "student.h"
#include "computer_room.h"
#include <cassert>
extern computer_room computerRoom;
bool student::SignIn(computer* machine)
{
	if (machine == nullptr || machine->Used() || IsOnline())return false;
	time_t const nowTimeStamp = time(nullptr);
	machine->Used(true);
	machine->Student(this);
	machine->BeginTime(nowTimeStamp);

	ModifyBegintime(nowTimeStamp);
	ModifyIsOnline(true);
	ModifyComputerid(machine);
	return true;
}

bool student::SignOut()
{
	return SignOut(time(nullptr));
}

bool student::SignOut(time_t offtime)
{
	if (!IsOnline())return false;
	Computerid()->Used(false);
	Computerid()->Student(nullptr);
	Computerid()->BeginTime(-1);

	ModifyComputerid(nullptr);
	ModifyIsOnline(false);
	ModifyDeposit(Deposit() - CalculateCost(offtime));
	ModifyBegintime(-1);
	return true;
}
int student::CalculateCost(time_t now) const
{
	if (Begintime() == -1)return 0; //未上机
	double const seconds = difftime(now, Begintime()); //四舍五入
	int const hours = static_cast<int>(ceil(seconds / 60.0 / 60.0)); //向上取整
	return hours * 1; //一小时一元
}
std::ifstream& operator>>(std::ifstream& is, student* stu)
{
	assert(stu != nullptr);
	if (stu)
	{
		int iOnline;
		is >> stu->uid;
		is >> stu->classname;
		is >> stu->name;
		is >> iOnline;
		is >> stu->computeridInternal;
		is >> stu->begintime;
		is >> stu->deposit;
		stu->isOnline = iOnline ? true : false;
	}

	return is;
}

std::ofstream& operator<<(std::ofstream& os, student* stu)
{
	assert(stu != nullptr);
	if (stu)
	{
		os << stu->uid << "\t";
		os << stu->classname << "\t";
		os << stu->name << '\t';
		os << (stu->isOnline ? 1 : 0) << '\t';
		os << (stu->computerid ? stu->computerid->Uid() : -1) << '\t';
		os << stu->begintime << '\t';
		os << stu->deposit;
	}
	return os;
}