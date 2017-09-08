// Source : https://leetcode.com/problems/remove-linked-list-elements/
// Author : Li Junjun
// Date   : 2017/09/08

/**********************************************************************************
*
* Remove all elements from a linked list of integers that have value val.
*
* Example
* Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6,  val = 6
* Return: 1 --> 2 --> 3 --> 4 --> 5
*
* Credits:Special thanks to @mithmatt for adding this problem and creating all test cases.
*
**********************************************************************************/

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

ListNode * makeList(ListNode * head, int val)
{
	ListNode * currPtr;
	ListNode * node = new ListNode(val);
	if (head == NULL)
	{
		head = node;
		return head;
	}
	currPtr = head;
	while (currPtr->next != NULL)
		currPtr = currPtr->next;
	currPtr->next = node;
	return head;
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

// 从链表中删除值为val的结点
ListNode* removeElements(ListNode* head, int val) {
	if (head == NULL)
		return NULL;
	ListNode * currPtr = head;
	ListNode * prevPtr = NULL;
	ListNode * deletePtr = NULL;
	while (currPtr != NULL)
	{
		if (currPtr->val == val)
		{
			if (currPtr == head)
			{
				head = head->next;
				deletePtr = currPtr;
			}
			else{
				prevPtr->next = currPtr->next;
				deletePtr = currPtr;
			}
		}
		else
			prevPtr = currPtr;
		currPtr = currPtr->next;
		delete deletePtr;
		deletePtr = NULL;
	}
	return head;
}

int main()
{
	int n, val;
	cout << "input list length: ";
	while (cin >> n)
	{
		ListNode *LIST = NULL;
		ListNode *node, *p, *q = NULL;
		cout << "input list（" << n << " datas): " << endl;
		for (int i = 0; i < n; i++)
		{
			cin >> val;
			LIST = makeList(LIST, val);
		}
		cout << "LIST is: ";
		showList(LIST);
		cout << endl;
		showList(removeElements(LIST, 1));
		cout << endl << "input list length: ";
	}
	
	return 0;
}