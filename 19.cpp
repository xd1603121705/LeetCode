// Source : https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
// Author : Li Junjun
// Date   : 2017/09/19

/**********************************************************************************
*
*       title: 19. Remove Nth Node From End of List
*
*     problem: Given a linked list, remove the nth node from the end of list and return its head.
*              For example,
*
*                    Given linked list: 1->2->3->4->5, and n = 2.
*
*                    After removing the second node from the end, the linked list becomes 1->2->3->5.
*                    Note:
*                    Given n will always be valid.
*                    Try to do this in one pass.
*
*    solution: 用前后两个指针，前指针先走N步，然后一起走直到front走到链表尾，删除rear->next.
*
* description: 程序输入输出重定向到了文件中，输入从"data.in"中读取，输出读入到
*              "data.out"中。
*              输入：第一行为结点数目N（输入字符退出），第二行为N个整数。
*              举例：5
*                    5 4 3 2 1
*                    10
*                    6 3 5 7 9 2 1 4 8 0
*                    q
*              输出：original list is: 5->4->3->2->1
*                    swap list: 5->4->3->1
*                    original list is: 6->3->5->7->9->2->1->4->8->0
*                    swap list: 6->3->5->7->9->2->1->4->0
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

ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode *front = head, *rear = head; // front go first, then together
	while (n--) front = front->next;      // front go n steps
	if (!front) return head->next;        // if n is equal to the length of list, delete first node
	while (front->next)                   // go together til front get to end
	{
		rear = rear->next;
		front = front->next;
	}
	rear->next = rear->next ? rear->next->next : NULL; // delete that node
	return head;
}

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

		head = removeNthFromEnd(head, 2);

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