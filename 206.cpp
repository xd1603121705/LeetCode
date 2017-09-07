// Source : https://leetcode.com/problems/reverse-linked-list/
// Author : Li Junjun
// Date   : 2017/09/07

/**********************************************************************************
 *
 * Reverse a singly linked list.
 *
 * click to show more hints.
 *
 * Hint:
 * A linked list can be reversed either iteratively or recursively. Could you implement both?
 *
 *
 *********************************************************************************/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <iostream>

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
	ListNode * p, *q = NULL;
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

/* 反转链表（迭代）*/
ListNode * reverseList(ListNode * head)
{
	ListNode *p = NULL, *q;
	while (head)
	{
		q = head->next;
		head->next = p;
		p = head;
		head = q;
	}
	return p;
}

/* 反转链表（递归）
 *       input(head)       h               return
 *         5                                  5
 *         4               5                  5->4
 *         3               5->4               5->4->3 
 *         2               5->4->3            5->4->3->2
 *         1               5->4->3->2         5->4->3->2->1
 **/
ListNode * reverseList_recursively(ListNode * head)
{
	if (head == NULL || head->next == NULL)
		return head;
	ListNode *h = reverseList_recursively(head->next);
	head->next->next = head;
	head->next = NULL;
	return h;
}
int main()
{
	ListNode *LIST = NULL;
	ListNode *p, *q = NULL;
	int a[10] = { 1, 2, 3, 4, 5 };
	cout << " list is: ";

	makeList(a, 5, LIST);
	showList(LIST);
	cout << endl;
	showList(reverseList_recursively(LIST));
	cout << endl;
	return 0;
}