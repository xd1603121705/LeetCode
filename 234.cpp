// Source : https://leetcode.com/problems/palindrome-linked-list/
// Author : Li Junjun
// Date   : 2017/09/07

/**********************************************************************************
 *
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
 *
 *********************************************************************************/

/*
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>

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
	ListNode * p, *q = NULL;
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

/* ��ת���� */
ListNode * reverseList(ListNode * & head)
{
	ListNode* p = NULL;

	while (head) {
		ListNode* q = head->next;
		head->next = p;
		p = head;
		head = q;
	}
	return p;
}

/* �ҵ������м��� */
ListNode * findMidNode(ListNode * head)
{
	ListNode * slow = head, *fast = head;
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

/* �ж��Ƿ�Ϊ�������� */
bool isPalindrome(ListNode * head)
{
	ListNode * mid = findMidNode(head);
	//cout << endl;
	//showList(mid);
	//cout << endl;
	ListNode * rev = reverseList(mid);
	//showList(rev);
	//cout << endl << mid->val << endl;
	
	while (head != mid)
	{
		if (head->val != rev->val)
			return false;
		head = head->next;
		rev = rev->next;
	}
	return true;
}

int main()
{
	ListNode *LIST = NULL;
	ListNode *p, *q = NULL;
	int a[10] = { 1, 1, 2, 1, 1 };
	cout << " list is: ";

	makeList(a, 5, LIST);
	showList(LIST);
	cout << endl << isPalindrome(LIST);

	cout << endl;

	return 0;
}