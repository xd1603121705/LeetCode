// Source : https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
// Author : Li Junjun
// Date   : 2017/09/18

/**********************************************************************************
*
*       title: 82. Remove Duplicates from Sorted List II
*
*     problem: Given a sorted linked list, delete all nodes that have 
*              duplicate numbers, leaving only distinct numbers from 
*              the original list.
*
*              For example,
*              Given 1->2->3->3->4->4->5, return 1->2->5.
*              Given 1->1->1->2->3, return 2->3.
*
*    solution: 用head->next->val值作为标志来删除所有val值相同的结点，此方案
*              时间复杂度6ms。
*
* description: 程序输入输出重定向到了文件中，输入从"data.in"中读取，输出读入到
*              "data.out"中。
*              输入：第一行为结点数目N（输入字符退出），第二行为N个整数。
*              举例：7
*                    1 1 2 2 3 4 4
*                    2
*                    1 2
*                    q
*              输出：original list is: 1->1->2->2->3->4->4
*                    swap list: 3
*                    original list is: 1->2
*                    swap list: 1->2
*
**********************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>

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

/* 反转链表 */
ListNode* ReverseList(ListNode *head)
{
	if (!head)
		return head;
	ListNode *p = head;
	ListNode *q = p->next;
	head->next = NULL;
	while (q)
	{
		p = q;
		q = q->next;
		p->next = head;
		head = p;
	}
	return head;
}

/* 反转链表2（用于某两点之间的链表反转）*/
ListNode* ReverseList2(ListNode *head)
{
	if (!head)
		return head;
	ListNode dummy(0);
	ListNode *prev = &dummy;
	prev->next = head;
	ListNode *curr = head;
	while (curr->next)
	{
		ListNode *move = curr->next;
		curr->next = move->next;
		move->next = prev->next;
		prev->next = move;
	}
	return dummy.next;
}

/* 创建带环链表 */
ListNode* CreateCycle(ListNode *head, int n)
{
	ListNode *tail = head;
	ListNode *currPtr = head;
	while (tail->next)
		tail = tail->next;
	while (--n)
	{
		if (!currPtr)
			return NULL;
		currPtr = currPtr->next;
	}
	tail->next = currPtr;
	return head;
}

/* 判断链表是否有环 */
bool hasCycle(ListNode *head) {
	if (!head || !head->next)
		return false;
	ListNode *fast = head;
	ListNode *low = head;

	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		low = low->next;
		if (fast == low)
			return true;
	}
	return false;
}

/************************************************提交部分***********************************************************/
/***************************************************************************************************************/
ListNode* deleteDuplicates(ListNode* head) {
	if (!head || !head->next) 
		return head;
	ListNode dummy(0);
	ListNode *prev = &dummy;
	dummy.next = head;
	int val = head->next->val; // val值用来表示当前扫描节点的下一结点值
	while (head)
	{
		if (head->val == val)
		{
			while (head && head->val == val) // 如果存在相同结点，则一直扫描到下一val值结点
				head = head->next;
			prev->next = head;
			if (head && head->next) // 
				val = head->next->val;
			else
				break;
		}
		else
		{
			prev = head;
			head = head->next;
			//val = head->next ? head->next->val : 0;
			if (head->next)
				val = head->next->val;
			else
				break;
		}
	}
	return dummy.next;
}
/***************************************************************************************************************/
/***************************************************************************************************************/

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

	clock_t startTime, endTime;

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

		startTime = clock();

		head = partition(head, 2);

		endTime = clock();

		cout << "swap list: ";
		//cout << "reorder list is: ";
		PrintList(head);
		cout << "The runtime is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000 << "ms!" << endl;
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