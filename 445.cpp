/*
 *        文件名: leetcode445
 *      简要描述: LeetCode445题：Add Two Numbers II
 *          思路：将给定的链表反转，然后进行求和，最后再将求和之后的链表反转
 *      问题记录：1 一开始直接把链表中的值取出，进行整数的求和，再转换成链表，没有考虑两个链表只有一个结点的情况；而且这种方法只能计算最大long long所能表示的整数，题目的意思
 *                  是单纯的用链表进行各位相加，所以类似于9->9->9->9->9->9->9->9->9->9->9->9->9->9 + 7->8这种无法计算。
 *                2 未初始化分配空间的结点指针不能直接使用：
 *                  NodeList * newList;
 *			     	newList->next = newNode;
 *				    上面代码newList没有分配空间，所以不能进行第二步操作。
 *
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

/* 链表结点结构 */
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// 构造链表
void makeList(int Array[], int length, ListNode * & List)
{
	ListNode * p, * q = NULL;
	for (int i = 0; i < length; i++)
	{
		p = new ListNode(Array[i]);
		if (List == NULL) // 头结点
		{
			List = p;
			q = p;
		}
		else
		{
			q->next = p;
			q = p;
		}
	}
}

/* 打印链表 */
void showList(ListNode * mylist)
{
	ListNode * ptr = mylist;
	while (ptr->next != NULL)
	{
		cout << ptr->val << "-> ";
		ptr = ptr->next;
	}
	cout << ptr->val;
}

/* 反转链表（需要提交） */
ListNode* reverseList(ListNode * & l)
{
	ListNode *p, *q;
	p = l;
	q = p->next;
	p->next = NULL;
	while (q != NULL)
	{
		p = q;
		q = q->next;
		p->next = l;
		l = p;
	}
	return l;
}

/* 链表l1和l2求和，返回求和后的链表（需要提交的主函数部分） */
ListNode * addTwoNumbers(ListNode* l1, ListNode* l2)
{
	if (l1 == NULL)
		return l2;
	if (l2 == NULL)
		return l1;

	// l1 l2反转
	l1 = reverseList(l1);
	l2 = reverseList(l2);

	int flag = 0; // 进位
	int sum = 0;

	ListNode * newList = NULL;
	ListNode * currPtrNew = new ListNode(0);
	newList = currPtrNew;
	ListNode * newNode;
	
	while (l1 != NULL || l2 != NULL)
	{
		int a = l1 == NULL ? 0 : l1->val;
		int b = l2 == NULL ? 0 : l2->val;
		sum = a + b + flag;
		flag = sum / 10;
		newNode = new ListNode(sum % 10);
		currPtrNew->next = newNode;
		currPtrNew = newNode;

		l1 = l1 == NULL ? NULL : l1->next;
		l2 = l2 == NULL ? NULL : l2->next;
	}

	if (flag == 1)
	{
		newNode = new ListNode(flag);
		currPtrNew->next = newNode;
	}

	return reverseList(newList->next);
}

int main()
{
	ListNode *l1 = NULL;
	ListNode *l2 = NULL;
	ListNode *p, *q = NULL;
	int a[10] = { 7, 2, 4, 3 };
	int b[10] = { 5, 6, 4 };
	cout << " list l1: ";
		/*for (int i = 0; i < sizeof(a); i++)
		{
			p = new ListNode(a[i]);
			if (l1 == NULL) // 头结点
			{
				l1 = p;
				q = p;
			}
			q->next = p;
			q = p;
		}*/
	makeList(a, 4, l1);
	showList(l1);
	cout << endl << " list l2: ";
		//delete p;
		//q = NULL;
		/*for (int i = 0; i < 3; i++)
		{
			p = new ListNode(b[i]);
			if (l2 == NULL) // 头结点
			{
				l2 = p;
				q = p;
			}
			q->next = p;
			q = p;
		}*/
	makeList(b, 3, l2);
	showList(l2);
	cout << endl << "sum list: ";
	showList(addTwoNumbers(l1, l2));
	cout << endl;

	return 0;
}
