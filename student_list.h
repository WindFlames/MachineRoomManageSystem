#pragma once
#include "student.h"
#include <list>
#include <stdexcept>
#include <fstream>
#include <vector>
struct StudentListNode
{
	student* value;
	StudentListNode* next;
	StudentListNode() :value(nullptr), next(nullptr) {}
	StudentListNode(student* val) :value(val), next(nullptr) {}
};
class student_list
{
	/// @brief 用指针方式保存学生数据
	StudentListNode* head;
	StudentListNode* tail;
	size_t len;
public:
	student_list() :head(new StudentListNode), tail(head), len(0u) {}
	/*数据操作部分*/
	/// @brief 从文件中读取学生数据
	/// @param filename 文件名
	void ReadFromText(const std::string& filename);
	/// @brief 将学生信息写入文件
	/// @param filename 文件名
	void WriteToText(const std::string& filename) const;

	/// @brief 通过学号查找对应的学生，默认学号不重复
	/// @param uid 学号
	/// @return 返回找到的那位学生的指针，找不到返回nullptr
	student* FindStudentById(const std::string& uid) const noexcept(false);

	/// @brief 通过姓名查找对应的学生
	/// @param name 姓名
	/// @return 返回找到所有学生集合,找不到返回{}
	std::vector<student*> FindStudentByName(const std::string& name) const;
	/// @brief 通过班级查找对应学生
	std::vector<student*> FindStudentByClass(const std::string& classname) const;

	void AddStudent(student* stu)
	{
		AddToTail(stu);
	}
	void DeleteStudent(student* stu)
	{
		StudentListNode* pre = head, * cur;
		for (cur = begin(); cur != end(); cur = cur->next)
		{
			if (cur->value == stu)
			{
				break;
			}
			pre = cur;
		}
		if (pre && cur && cur != end())
		{
			pre->next = cur->next;

			if (cur == tail)
			{
				tail = pre;
				tail->next = nullptr;
			}
			delete cur->value;
			delete cur;
			len--;
		}
	}

	std::size_t Size()const
	{
		return len;
	}
	/*链表操作部分*/
	template<typename Pred>
	void Sort(Pred process)
	{
		StudentListNode dummyHead;
		dummyHead.next = head->next;
		auto p = head->next;
		int length = 0;
		while (p) {
			++length;
			p = p->next;
		}

		for (int size = 1; size < length; size <<= 1) {
			auto cur = dummyHead.next;
			auto tail = &dummyHead;

			while (cur) {
				auto left = cur;
				auto right = cut(left, size); // left->@->@ right->@->@->@...
				cur = cut(right, size); // left->@->@ right->@->@  cur->@->...

				tail->next = merge(left, right, process);
				while (tail->next) {
					tail = tail->next;
				}
			}
		}
		head->next = dummyHead.next;//把节点连回去
	}

	StudentListNode* cut(StudentListNode* head, int n) {
		auto p = head;
		while (--n && p) {
			p = p->next;
		}

		if (!p) return nullptr;

		const auto next = p->next;
		p->next = nullptr;
		return next;
	}
	template<typename Pred>
	StudentListNode* merge(StudentListNode* l1, StudentListNode* l2, Pred process) {
		StudentListNode dummyHead;//哨兵节点,使用局部变量而不使用new是为了自动销毁
		auto p = &dummyHead;
		while (l1 && l2) {
			if (process(l1->value, l2->value)) {
				p->next = l1;
				p = l1;
				l1 = l1->next;
			}
			else {
				p->next = l2;
				p = l2;
				l2 = l2->next;
			}
		}
		p->next = l1 ? l1 : l2;
		return dummyHead.next;
	}
	void AddToTail(student* stu)
	{
		tail->next = new StudentListNode(stu);
		tail = tail->next;
		len++;
	}
	/// @brief 头节点
	/// @return 返回头节点
	StudentListNode* begin() const { return head->next; }
	/// @brief 返回尾节点后一个节点的指针
	/// @return 永远是nullptr
	StudentListNode* end()const { return nullptr; }
};
