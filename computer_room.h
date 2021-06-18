#pragma once
#include <vector>
#include <fstream>
#include "computer.h"

class computer_room
{
	std::vector<computer*> computers;
public:
	computer_room() = default;

	size_t size()const { return computers.size(); }

	const computer* operator[](size_t pos) const;

	computer* operator[](size_t pos);

	computer* operator[](int uid);

	void AddComputer(const computer& newcomputer);

	void DeleteComputer(int uid);

	computer* FindRestComputer();

	void ReadFromText(const std::string& filename);

	void WriteToText(const std::string& filename);
};
