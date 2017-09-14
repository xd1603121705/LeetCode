// Source : https://leetcode.com/problems/linked-list-cycle/description/
// Author : Li Junjun
// Date   : 2017/09/14

/**********************************************************************************
*
*     problem: Given a linked list, determine if it has a cycle in it.
* 
*              Follow up:
*              Can you solve it without using extra space?
*
*    solution: ����ָ�룬��ָ��һ������������ָ��һ��һ����������ָ���غϣ�����ڻ���
*
* description: ������������ض������ļ��У������"data.in"�ж�ȡ��������뵽
*              "data.out"�С�
*              ��������һ�����ڴ�����������ĺ���CreateCycle����ʱ���ܵ����������
*              �����������������һ�飬�мǡ�
*              ���룺��һ��Ϊ�����ĿN�������ַ��˳������ڶ���ΪN��������
*              ������5
*                    5 4 3 2 1
*                    q
*              �����original list is: 5->4->3->2->1
*                    cycle: 1(1��ʾ�л���0��ʾ��)
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

/* ��ת���� */
ListNode* ReverseList(ListNode *head)
{
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

/* ������������������head�ĵ� n ���������Ϊ������㣩 */
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

/* �ж������Ƿ��л� */
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
		cout << "original list is: ";
		PrintList(head);
		head = CreateCycle(head, 4);
		cout << "cycle: " << hasCycle(head) << endl;

	}

	cin.rdbuf(readbuf);
	cout.rdbuf(writebuf);

	fin.close();
	fout.close();

	return 0;
}

