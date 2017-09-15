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
*    solution: ʹ�ó����ռ䣬���Բ����õݹ飬ֻ�ܸı��㣬���ܸı����ֵ�����ѡ��
*              �����ڵĽ�㷴ת����ƴ�ӵ��������ϼ��ɡ�
*
* description: ������������ض������ļ��У������"data.in"�ж�ȡ��������뵽
*              "data.out"�С�
*              ���룺��һ��Ϊ�����ĿN�������ַ��˳������ڶ���ΪN��������
*              ������5
*                    5 4 3 2 1
*                    10
*                    6 3 5 7 9 2 1 4 8 0
*                    q(����������ַ�����)
*              �����original list: 5->4->3->2->1
*                    swap list: 4->5->2->3->1
*                    original list: 6->3->5->7->9->2->1->4->8->0
*                    swap list: 3->6->7->5->2->9->4->1->0->8
*
**********************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

/* ������ */
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
};

/* ��ӡ���� */
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

/* ��������*/
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

/* ������� */
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
/* p->q�ĳ�q->p */
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
	int n; // ������
	int val; // ���ֵ
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