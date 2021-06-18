#include "computer_room.h"

const computer* computer_room::operator[](size_t pos) const
{
	return computers[pos];
}

computer* computer_room::operator[](size_t pos)
{
	return computers[pos];
}

computer* computer_room::operator[](int uid)
{
	for (auto cpt : computers)
	{
		if (cpt->Uid() == uid)
			return cpt;
	}
	return nullptr;
}

void computer_room::AddComputer(const computer& newcomputer)
{
	computers.push_back(new computer(newcomputer));
}

void computer_room::DeleteComputer(int uid)
{
	for (auto p = computers.cbegin(); p != computers.cend(); ++p)
	{
		if ((*p)->Uid() == uid)
		{
			computers.erase(p);
			return;
		}
	}
}

computer* computer_room::FindRestComputer()
{
	for (auto com : computers)
	{
		if (!com->Used())
			return com;
	}
	return nullptr;
}

void computer_room::ReadFromText(const std::string& filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())throw std::invalid_argument("�ļ�" + filename + "�����ڡ�");
	//�ж��ļ��Ƿ�Ϊ��
	char c;
	ifs >> c;
	if (ifs.eof())
	{
		ifs.close();
		return;
	}
	ifs.seekg(0);

	std::vector<computer*>().swap(computers);

	int cnt;
	ifs >> cnt;
	computers.resize(cnt);
	for (int i = 0; i < cnt; i++)
	{
		computer* cpt = new computer;
		if (!(ifs >> cpt))
		{
			throw std::invalid_argument("�ļ�" + filename + "���ݴ���");
		}
		computers[i] = cpt;
	}

	ifs.close();
}

void computer_room::WriteToText(const std::string& filename)
{
	std::ofstream ofs(filename);
	if (!ofs.is_open())throw std::invalid_argument("�ļ�" + filename + "����ʧ�ܡ�");
	ofs << computers.size() << std::endl;
	for (auto cpt : computers)
	{
		ofs << cpt << std::endl;
	}
	ofs.close();
}