#pragma once
#include<cstdlib>
#include "ILayer.h"
#include "student.h"

/// @brief ��ȡ���鳤��
/// @tparam T ������������
/// @param
/// @return ���鳤��
template<typename T, size_t SIZE>
constexpr size_t GetArrayLength(T(&)[SIZE])
{
	return SIZE;
}
/// @brief ����
inline void CleanScreen()
{
	std::system("cls");
}
/// @brief ��ʼ������
void Initialization();
/// @brief ����ʼ��
void Deinitialization();
//TODO:inline��ʹ��
inline const char* Bool2String(bool boolean)
{
	return boolean ? "��" : "��";
}
int DisplayLayer(ILayer* layer);
void Combine();

void SaveComputerRoom();
void SaveStudentsInfo();
std::string TimeStamp2FormatString(time_t t);