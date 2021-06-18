// 机房收费管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "MainLayer.h"
#include "computer_room.h"
#include "CommonHelper.h"
#include "student_list.h"
using namespace std;
computer_room computerRoom;
student_list studentCollection;
int main()
{
	try
	{
		Initialization();
		MainLayer mainLayer;
		DisplayLayer(&mainLayer);

		Deinitialization();
	}
	catch (invalid_argument& ex)
	{
		cout << ex.what() << endl;
		system("pause");
	}
}
//机房收费管理系统
//基本要求 : 能够对计算中心的机房进行学生上机以及收费情况的管理。
//功能要求：
//1、设计菜单实现功能选择；
//2、能够维护学生的信息：增加、修改及删除学生的上机信息（学号、班级、姓名、上机起止时间）；
//3、查询功能：按条件（班级、学号、姓名）显示学生的上机时间；
//4、能够按照学号、班级、开始时间和时长进行排序显示；
//5、计算功能：计算每个下机学生的上机费用，每小时1元；
//（上机费用 = 上机时间 * 1.0 / h ，不足一小时按一小时计算）
//6、机器使用情况的显示（显示方式不限但要一目了然）；
//7、能将所有信息读写文件。