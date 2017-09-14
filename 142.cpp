// Source : https://leetcode.com/problems/linked-list-cycle/description/
// Author : Li Junjun
// Date   : 2017/09/14

/**********************************************************************************
*
*     problem: Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
*
*              Note: Do not modify the linked list.
*
*              Follow up:
*              Can you solve it without using extra space?
*
*    solution: 对于如下所示的带环链表        n6--------n5
*                                            |          |
*                                       n1---n2---n3---n4      环的起点是n2
*              首先我们知道， fast每次比slow多走一步， 所以重合的时候， fast移动的距离是slot的两倍， 我们假设n1到
*              n2距离为a， n2到n5距离为b， n5到n2距离为c， fast走动距离为 a + b + c + b ， 而slow为 a + b ， 有方
*              程 a + b + c + b = 2 x (a + b) ， 可以知道 a = c ， 所以我们只需要在重合之后， 一个指针从n1， 而
*              另一个指针从n5， 都每次走一步， 那么就可以在n2重合了。

* description: 程序输入输出重定向到了文件中，输入从"data.in"中读取，输出读入到
*              "data.out"中。
*              程序构造了一个用于创建带环链表的函数CreateCycle，此时不能调用清空链表
*              函数，而且输入就用一组，切记。
*              输入：第一行为结点数目N（输入字符退出），第二行为N个整数。
*              举例：5
*                    5 4 3 2 1
*                    q
*              输出：original list is: 5->4->3->2->1
*                    cycle: 1(1表示有环，0表示无)
*                    crossing point is: 2（环起点的val值）
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

/* 反转链表 */
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

/* 创建带环链表（将链表head的第 n 个结点设置为环的起点） */
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

