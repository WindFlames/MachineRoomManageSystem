#include "ComputerUsageLayer.h"
#include "CommonHelper.h"
#include "computer_room.h"
#include "ConsoleTables.h"

extern computer_room computerRoom;
void ComputerUsageLayer::Display() const
{
	ConsoleTables ctables({ "���","�Ƿ�ʹ��","ѧ������" ,"�ϻ�ʱ��" }, out);
	for (size_t i = 0; i < computerRoom.size(); i++)
	{
		ctables.AddRow({ std::to_string(computerRoom[i]->Uid()),
			Bool2String(computerRoom[i]->Used()),
			(computerRoom[i]->Used() ? computerRoom[i]->Student()->Name() : "-"),
			(computerRoom[i]->Used() ? TimeStamp2FormatString(computerRoom[i]->BeginTime()) : "-")
			});
	}
	ctables.Write();
}

int ComputerUsageLayer::InputHandler() const
{
	//����Ҫ�������
	return -1;
}