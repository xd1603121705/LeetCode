/*
 *        �ļ���: leetcode445
 *      ��Ҫ����: LeetCode445�⣺Add Two Numbers II
 *          ˼·��������������ת��Ȼ�������ͣ�����ٽ����֮�������ת
 *      �����¼��1 һ��ʼֱ�Ӱ������е�ֵȡ����������������ͣ���ת��������û�п�����������ֻ��һ������������������ַ���ֻ�ܼ������long long���ܱ�ʾ����������Ŀ����˼
 *                  �ǵ�������������и�λ��ӣ�����������9->9->9->9->9->9->9->9->9->9->9->9->9->9 + 7->8�����޷����㡣
 *                2 δ��ʼ������ռ�Ľ��ָ�벻��ֱ��ʹ�ã�
 *                  NodeList * newList;
 *			     	newList->next = newNode;
 *				    �������newListû�з���ռ䣬���Բ��ܽ��еڶ���������
 *
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

/* ������ṹ */
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// ��������
void makeList(int Array[], int length, ListNode * & List)
{
	ListNode * p, * q = NULL;
	for (int i = 0; i < length; i++)
	{
		p = new ListNode(Array[i]);
		if (List == NULL) // ͷ���
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

/* ��ӡ���� */
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

/* ��ת������Ҫ�ύ�� */
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

/* ����l1��l2��ͣ�������ͺ��������Ҫ�ύ�����������֣� */
ListNode * addTwoNumbers(ListNode* l1, ListNode* l2)
{
	if (l1 == NULL)
		return l2;
	if (l2 == NULL)
		return l1;

	// l1 l2��ת
	l1 = reverseList(l1);
	l2 = reverseList(l2);

	int flag = 0; // ��λ
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
			if (l1 == NULL) // ͷ���
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
			if (l2 == NULL) // ͷ���
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
