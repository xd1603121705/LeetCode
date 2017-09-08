// Source : https://leetcode.com/problems/odd-even-linked-list/
// Author : Li Junjun
// Date   : 2017/09/08

/***************************************************************************************
*
* Given a singly linked list, group all odd nodes together followed by the even nodes.
* Please note here we are talking about the node number and not the value in the nodes.
*
* You should try to do it in place. The program should run in O(1) space complexity
* and O(nodes) time complexity.
*
* Example:
* Given 1->2->3->4->5->NULL,
* return 1->3->5->2->4->NULL.
*
* Note:
* The relative order inside both the even and odd groups should remain as it was in
* the input.
* The first node is considered odd, the second node even and so on ...
*
* Credits:Special thanks to @aadarshjajodia for adding this problem and creating all
* test cases.
***************************************************************************************/

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

/* 构造链表 */
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

ListNode * oddEvenList(ListNode *head)
{
	if (head == NULL)
		return head;
	ListNode *currPtr = head->next, *prevPtr = head; // 遍历结点、前一结点（从head->next开始）
	ListNode *oddNode, *oddListTail = head; // odd尾结点
	int i = 2; // 序号
	while (currPtr != NULL)
	{
		if (i % 2 == 1)
		{
			oddNode = currPtr;
			prevPtr->next = currPtr->next;
			currPtr = currPtr->next;
			oddNode->next = oddListTail->next;
			oddListTail->next = oddNode;
			oddListTail = oddNode;
		}
		else
		{
			prevPtr = currPtr;
			currPtr = currPtr->next;
		}
		++i;
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
		showList(oddEvenList(LIST));
		cout << endl << "input list length: ";
	}
	
	return 0;
}