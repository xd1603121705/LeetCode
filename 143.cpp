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

using namespace std;

/* 链表结点 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL){}
};

/* 打印链表 */
void PrintList(ListNode *head)
{
    ListNode *currPtr = head;
    while(currPtr->next != NULL)
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
    if(head == NULL)
        head = node;
    else
    {
        while(currPtr->next)
            currPtr = currPtr->next;
        currPtr->next = node;
    }
    return head;
}

/* 清空链表 */
ListNode* freeList(ListNode *head)
{
    ListNode *currPtr = NULL;
    while(head)
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
    while(q)
    {
        p = q;
        q = q->next;
        p->next = head;
        head = p;
    }
    return head;
}

/* 交叉合并两个排好序链表 */
ListNode* MergeList(ListNode *left, ListNode *right)
{
    ListNode *head = left; // left的首结点为新链表的首结点
    left = left->next; // 左边第一个默认首结点，从第二个开始合并
    ListNode *tail = head; // 新链表的尾结点
    bool leftNode = false; // 选择的标志 为true选择left结点 false选择right结点
    while(left || right) // "||"操作保证所有结点均合并
    {
        if(leftNode)
        {
            tail->next = left;
            tail = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            tail = right;
            right = right->next;
        }
        leftNode = leftNode ? false : true; // 每次操作将标志取反
    }
    return head;
}

/* Reorder List */
void ReorderList(ListNode *head)
{
    if(!head || !head->next)
        return;
    /* 快慢指针找到链表中间结点 中间结点的下一结点为新链表的尾结点 */
    ListNode *low = head;
    ListNode *fast = head;
    while(fast->next && fast->next->next)
    {
        fast = fast->next->next;
        low = low->next;
    }
    /* 链表分为两部分 */
    fast = low->next;
    low->next = NULL;

    fast = ReverseList(fast);  // 翻转右半部分
    head = MergeList(head, fast);  // 合并
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
    while(cin >> n)
    {
        for(int i = 0; i < n; i++)
        {
            cin >> val;
            head = CreateList(head, val);
        }
        cout << "original list is: ";
        PrintList(head);
        //head = InsertionSortList(head);
        ReorderList(head);
        cout << "reorder list is: ";
        PrintList(head);
        head = freeList(head);
    }

    cin.rdbuf(readbuf);
    cout.rdbuf(writebuf);

    fin.close();
    fout.close();

    return 0;
}
