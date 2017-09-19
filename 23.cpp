// Source : https://leetcode.com/problems/merge-k-sorted-lists/description/
// Author : Li Junjun
// Date   : 2017/09/19

/**********************************************************************************
*
*       title: 23. Merge k Sorted Lists
*
*     problem: Merge k sorted linked lists and return it as one sorted list. 
*                    Analyze and describe its complexity.
*
*    solution: 依次merge两个链表，直至所有链表有序
*
* description: 程序输入输出重定向到了文件中，输入从"data.in"中读取，输出读入到
*              "data.out"中。
*              输入：第一行为结点数目N（输入字符退出），第二行为N个整数。
*              举例：5
*                    1 3 5 7 9
*                    5
*                    0 2 4 6 8
*                    5
*                    1 4 7 8 10
*              输出：list head is: 1->3->5->7->9
*                    list head2 is: 0->2->4->6->8
*                    list head3 is: 1->4->7->8->10
*                    list after merge is: 0->1->2->4->4->6->7->8->8->10
*
**********************************************************************************/

// Source : https://leetcode.com/problems/reorder-list/description/
// Author : Li Junjun
// Date   : 2017/09/14

/**********************************************************************************
*
*     problem: Given a singly linked list L: L0?L1?…?Ln-1?Ln,
*              reorder it to: L0?Ln?L1?Ln-1?L2?Ln-2?…
*
*              You must do this in-place without altering the nodes' values.
*
*              For example,
*              Given {1,2,3,4}, reorder it to {1,4,2,3}.
*
*    solution: 找到中间结点，反转后半部分，再交叉插入构造新链表
*
* description: 程序输入输出重定向到了文件中，输入从"data.in"中读取，输出读入到
*              "data.out"中。
*              输入：第一行为结点数目N（输入字符退出），第二行为N个整数。
*              举例：5
5 4 3 2 1
10
6 3 5 7 9 2 1 4 8 0
q
输出：original list is: 5->4->3->2->1
reorder list is: 5->1->4->2->3
original list is: 6->3->5->7->9->2->1->4->8->0
reorder list is: 6->0->3->8->5->4->7->1->9->2
*
**********************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <climits>
#include <vector>

using namespace std;

/* 链表结点 */
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
};

/* 带随机指针的链表结点 */
struct RandomListNode
{
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL){}
};

/* 打印链表 */
void PrintList(ListNode *head)
{
	if (!head)
		return;
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

/* 寻找链表产生环的结点 */
ListNode *detectCycle(ListNode *head)
{
	if (!hasCycle(head))
		return NULL;
	ListNode *fast = head->next->next;
	ListNode *low = head->next;

	while (fast != low)
	{
		fast = fast->next->next;
		low = low->next;
	}
	fast = head;
	while (fast != low)
	{
		fast = fast->next;
		low = low->next;
	}

	return fast;
}

/***************************************************************************************************************/

ListNode* mergeTwoLists(ListNode *head1, ListNode *head2)
{
	ListNode dummy(0);
	ListNode *newhead = &dummy;
	while (head1 && head2)
	{
		/*if (head1->val <= head2->val)
		{
			newhead->next = head1;
			newhead = head1;
			head1 = head1->next;
		}
		else
		{
			newhead->next = head2;
			newhead = head2;
			head2 = head2->next;
		}*/
		ListNode *&p = head1->val <= head2->val ? head1 : head2;
		newhead->next = p;
		newhead = p;
		p = p->next;
	}
	if (head1)
		newhead->next = head1;
	if (head2)
		newhead->next = head2;
	return dummy.next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
	ListNode *head = NULL;
	if(lists.size() == 0) return NULL;
	if (lists.size() > 1){
		head = lists.back();
		lists.pop_back();
		ListNode *head2 = mergeKLists(lists);
		head = mergeTwoLists(head, head2);
	}
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
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		head = CreateList(head, val);
	}
	cout << "list head is: ";
	PrintList(head);
	ListNode *head2 = NULL, *head3 = NULL;
	vector<ListNode* > lists;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		head2 = CreateList(head2, val);
	}
	cout << "list head2 is: ";
	PrintList(head2);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> val;
		head3 = CreateList(head3, val);
	}
	cout << "list head3 is: ";
	PrintList(head3);
	lists.push_back(head);
	lists.push_back(head2);
	lists.push_back(head3);
	head = mergeKLists(lists);
	cout << "list after merge is: ";
	PrintList(head);

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
/*
10
6 3 5 7 9 2 1 4 8 0

*/