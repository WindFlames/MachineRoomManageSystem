#pragma once
#include<cstdlib>
#include "ILayer.h"
#include "student.h"

/// @brief 获取数组长度
/// @tparam T 数组数据类型
/// @param
/// @return 数组长度
template<typename T, size_t SIZE>
constexpr size_t GetArrayLength(T(&)[SIZE])
{
	return SIZE;
}
/// @brief 清屏
inline void CleanScreen()
{
	std::system("cls");
}
/// @brief 初始化数据
void Initialization();
/// @brief 反初始化
void Deinitialization();
//TODO:inline的使用
inline const char* Bool2String(bool boolean)
{
	return boolean ? "是" : "否";
}
int DisplayLayer(ILayer* layer);
void Combine();

void SaveComputerRoom();
void SaveStudentsInfo();
std::string TimeStamp2FormatString(time_t t);