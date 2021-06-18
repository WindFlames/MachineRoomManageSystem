#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

class ConsoleTables
{
	std::vector<std::string> headers;
	std::vector<std::vector<std::string>> rows;
	std::ostream& out;
	std::vector<int> ColumnLengths();

	static std::string FormatDivider(std::vector<int>& lengths, char delimiter = '+');
public:
	ConsoleTables(const std::initializer_list<std::string>& headers, std::ostream& os = std::cout);
	ConsoleTables& AddColumn(const std::string& name);

	ConsoleTables& AddRow(const std::initializer_list<std::string>& values);

	static std::string FormatEachLine(std::vector<std::string>& cols, std::vector<int>& lengths,char delimiter = '|');

	std::string GetFormatString();

	void Write();
};
