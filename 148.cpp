// Source : https://oj.leetcode.com/problems/sort-list/
// Author : Li Junjun
// Date   : 2017/09/13

/**********************************************************************************
*
*     problem: Sort a linked list in O(n log n) time using constant space complexity.
*
*    solution: 题目要求O(n log n)的时间复杂度，备选排序算法为快速排序、堆排序和归
*              并排序，快排最差会达到O(n^2)，所以排除，堆排序显然不适用单链表的结
*              构，归并排序才是符合要求的排序算法，对于空间复杂度，因为结构为链表
*              ，所以用指针即可，不用像数组那样单独开辟空间，所以此题选用归并排序。
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
                     sorted list is: 1->2->3->4->5
                     original list is: 6->3->5->7->9->2->1->4->8->0
                     sorted list is: 0->1->2->3->4->5->6->7->8->9
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

ListNode* mergeList(ListNode *left, ListNode *right)
{
    ListNode temp(0);
    ListNode *tail = &temp;
    while(left && right)
    {
        if(left->val <= right->val)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    if(left) tail->next = left;
    if(right) tail->next = right;

    return temp.next;
}

ListNode* sortList(ListNode *head)
{
    if(head == NULL || head->next == NULL)
        return head;

    // 快慢指针找到链表中点
    ListNode *low = head;
    ListNode *fast = head;
    while(fast->next && fast->next->next)
    {
        low = low->next;
        fast = fast->next->next;
    }

    // 链表拆成两半
    fast = low->next;
    low->next = NULL;

    // 左右链表分别排序
    ListNode *left = sortList(head);
    ListNode *right = sortList(fast);

    // 合并
    return mergeList(left, right);

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
        head = sortList(head);
        cout << "sorted list is: ";
        PrintList(head);
        head = freeList(head);
    }

    cin.rdbuf(readbuf);
    cout.rdbuf(writebuf);

    fin.close();
    fout.close();

    return 0;
}
