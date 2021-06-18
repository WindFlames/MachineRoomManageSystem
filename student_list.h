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
	/// @brief ��ָ�뷽ʽ����ѧ������
	StudentListNode* head;
	StudentListNode* tail;
	size_t len;
public:
	student_list() :head(new StudentListNode), tail(head), len(0u) {}
	/*���ݲ�������*/
	/// @brief ���ļ��ж�ȡѧ������
	/// @param filename �ļ���
	void ReadFromText(const std::string& filename);
	/// @brief ��ѧ����Ϣд���ļ�
	/// @param filename �ļ���
	void WriteToText(const std::string& filename) const;

	/// @brief ͨ��ѧ�Ų��Ҷ�Ӧ��ѧ����Ĭ��ѧ�Ų��ظ�
	/// @param uid ѧ��
	/// @return �����ҵ�����λѧ����ָ�룬�Ҳ�������nullptr
	student* FindStudentById(const std::string& uid) const noexcept(false);

	/// @brief ͨ���������Ҷ�Ӧ��ѧ��
	/// @param name ����
	/// @return �����ҵ�����ѧ������,�Ҳ�������{}
	std::vector<student*> FindStudentByName(const std::string& name) const;
	/// @brief ͨ���༶���Ҷ�Ӧѧ��
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
	/*�����������*/
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
		head->next = dummyHead.next;//�ѽڵ�����ȥ
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
		StudentListNode dummyHead;//�ڱ��ڵ�,ʹ�þֲ���������ʹ��new��Ϊ���Զ�����
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
	/// @brief ͷ�ڵ�
	/// @return ����ͷ�ڵ�
	StudentListNode* begin() const { return head->next; }
	/// @brief ����β�ڵ��һ���ڵ��ָ��
	/// @return ��Զ��nullptr
	StudentListNode* end()const { return nullptr; }
};
