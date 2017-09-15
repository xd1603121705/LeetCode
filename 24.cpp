// Source : https://leetcode.com/problems/swap-nodes-in-pairs/description/
// Author : Li Junjun
// Date   : 2017/09/15

/**********************************************************************************
*
*     problem: Given a linked list, swap every two adjacent nodes and return its head.
*
*              For example,
*              Given 1->2->3->4, you should return the list as 2->1->4->3.
*
*              Your algorithm should use only constant space. You may not modify the 
*              values in the list, only nodes itself can be changed.
*
*    solution: 使用常量空间，所以不能用递归，只能改变结点，不能改变结点的值，因此选择
*              把相邻的结点反转，再拼接到新链表上即可。
*
* description: 程序输入输出重定向到了文件中，输入从"data.in"中读取，输出读入到
*              "data.out"中。
*              输入：第一行为结点数目N（输入字符退出），第二行为N个整数。
*              举例：5
*                    5 4 3 2 1
*                    10
*                    6 3 5 7 9 2 1 4 8 0
*                    q(任意非数字字符均可)
*              输出：original list: 5->4->3->2->1
*                    swap list: 4->5->2->3->1
*                    original list: 6->3->5->7->9->2->1->4->8->0
*                    swap list: 3->6->7->5->2->9->4->1->0->8
*
**********************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

/* 链表结点 */
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
};

/* 打印链表 */
void PrintList(ListNode *head)
{
	ListNode *currPtr = head;
	while (currPtr->next != NULL)
	{
		cout << currPtr->val << "->";
		currPtr = currPtr->next;
	}
	cout << currPtr->val << endl;
}

/* 构造链表*/
ListNode* CreateList(ListNode *head, int val)
{
	ListNode *currPtr = head;
	ListNode *node = new ListNode(val);
	if (head == NULL)
		head = node;
	else
	{
		while (currPtr->next)
			currPtr = currPtr->next;
		currPtr->next = node;
	}
	return head;
}

/* 清空链表 */
ListNode* freeList(ListNode *head)
{
	ListNode *currPtr = NULL;
	while (head)
	{
		currPtr = head->next;
		delete head;
		head = currPtr;
	}
	return head;
}

/*----------------------------submit part----------------------------------------*/
/* p->q改成q->p */
ListNode* swapNode(ListNode *head)
{
	if (head->next)
	{
		head->next->next = head;
		head = head->next;
		head->next->next = NULL;
	}
	return head;
}

/* 24. Swap Nodes in Pairs */
ListNode* swapPairs(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode *currPtr = head;
	ListNode *temp = NULL;
	head = NULL;
	ListNode dummy(0);
	ListNode *tail = &dummy;
	while (currPtr && currPtr->next)
	{
		temp = currPtr;
		currPtr = currPtr->next->next;
		temp->next->next = NULL;
		if (!head)
		{
			head = swapNode(temp);
			tail = head->next;
		}
		else
		{
			tail->next = swapNode(temp);
			tail = temp->next ? temp->next : temp;
		}
	}
	if (currPtr)
		tail->next = currPtr;
	return head;
}
/*----------------------------submit part----------------------------------------*/

int main()
{
	streambuf *readbuf = cin.rdbuf();
	streambuf *writebuf = cout.rdbuf();

	ifstream fin;
	ofstream fout;

	fin.open("data.in");
	fout.open("data.out");

	cin.rdbuf(fin.rdbuf());
	cout.rdbuf(fout.rdbuf());

	ListNode *head = NULL;
	int n; // 链表长度
	int val; // 结点值
	while (cin >> n)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> val;
			head = CreateList(head, val);
		}
		cout << "original list: ";
		PrintList(head);
		head = swapPairs(head);
		cout << "swap list: ";
		//cout << "reorder list is: ";
		PrintList(head);
		head = freeList(head);
	}

	cin.rdbuf(readbuf);
	cout.rdbuf(writebuf);

	fin.close();
	fout.close();

	return 0;
}

/*
10
6 3 5 7 9 2 1 4 8 0

*/