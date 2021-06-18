#include "computer.h"
#include <fstream>
#include <cassert>
//TODO:ÎÊÌâµã
std::ifstream& operator>>(std::ifstream& is, computer* cpt)
{
	assert(cpt != nullptr);
	if (cpt)
	{
		is >> cpt->uid >> cpt->isUsed >> cpt->begintime >> cpt->studentidInternal;
		cpt->studentid = nullptr;
	}

	return is;
}

std::ofstream& operator<<(std::ofstream& os, computer* cpt)
{
	assert(cpt != nullptr);
	if (cpt)
	{
		os << cpt->Uid() << '\t' << cpt->Used() << '\t' << cpt->BeginTime() << '\t' << (cpt->studentid ? cpt->studentid->Uid() : "-1");
	}
	return os;
}