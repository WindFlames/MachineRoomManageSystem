#include <algorithm>
#include <cassert>

#include "ConsoleTables.h"

std::vector<int> ConsoleTables::ColumnLengths()
{
	std::vector<int> columnWidths(headers.size());
	for (size_t i = 0; i < headers.size(); i++)
	{
		int maxLen = static_cast<int>(headers[i].length());
		for (auto& row : rows)
		{
			maxLen = std::max(maxLen, static_cast<int>(row[i].length()));
		}
		columnWidths[i] = maxLen;
	}
	return columnWidths;
}

std::string ConsoleTables::FormatDivider(std::vector<int>& lengths, char delimiter)
{
	std::string s;
	s += delimiter;
	for (int length : lengths)
	{
		s += std::string(length + 1, '-');
		s += delimiter;
	}
	s.pop_back();
	s += delimiter;
	return s;
}

ConsoleTables::ConsoleTables(const std::initializer_list<std::string>& headers, std::ostream& os) : headers(headers), out(os)
{
}

ConsoleTables& ConsoleTables::AddColumn(const std::string& name)
{
	headers.push_back(name);
	return *this;
}

ConsoleTables& ConsoleTables::AddRow(const std::initializer_list<std::string>& values)
{
	assert(!headers.empty());
	assert(values.size() == headers.size());
	rows.emplace_back(values);
	return *this;
}

std::string ConsoleTables::FormatEachLine(std::vector<std::string>& cols, std::vector<int>& lengths, char delimiter)
{
	assert(cols.size() == lengths.size());
	std::stringstream ss;
	ss.fill(' ');
	ss.setf(std::ios::left);

	ss << delimiter;

	for (size_t i = 0; i < cols.size(); i++)
	{
		ss << std::setw(lengths[i]) << cols[i];
		ss << ' ' << delimiter;
	}

	return ss.str();
}

std::string ConsoleTables::GetFormatString()
{
	std::stringstream builder;

	auto columnLengths = ColumnLengths();

	std::string columnsHeader = FormatEachLine(headers, columnLengths);

	auto dividerPlus = FormatDivider(columnLengths);
	builder << dividerPlus << std::endl;
	builder << columnsHeader << std::endl;

	for (size_t i = 0; i < rows.size(); i++)
	{
		builder << dividerPlus << std::endl;
		builder << FormatEachLine(rows[i], columnLengths) << std::endl;
	}
	builder << dividerPlus << std::endl;
	return builder.str();
}

void ConsoleTables::Write()
{
	std::string s = GetFormatString();
	out << s;
}