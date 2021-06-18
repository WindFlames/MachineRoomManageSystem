#pragma once
#include<iostream>
/// @brief 界面接口（抽象类）
class ILayer
{
protected:
	/// @brief 输入流
	std::istream& in;
	/// @brief 输出流
	std::ostream& out;
public:
	ILayer(std::istream& is = std::cin, std::ostream& os = std::cout) :in(is), out(os) {}
	//虚析构函数，不造成子类结构破坏
	virtual ~ILayer() = default;
	//显示界面
	virtual void Display()const = 0;
	/// @brief 输入处理函数
	/// @return 返回-1表示退出此界面，其他值为继续显示
	virtual int InputHandler()const = 0;
};
