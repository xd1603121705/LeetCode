// Source : https://leetcode.com/problems/insertion-sort-list/description/
// Author : Li Junjun
// Date   : 2017/09/13

/**********************************************************************************
*
*     problem: Sort a linked list in O(n log n) time using constant space complexity.
*
*    solution: 直接插入排序算法实现链表排序
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

/* 直接插入排序算法实现链表排序 */
ListNode* InsertionSortList(ListNode *head)
{
    if(!head || !head->next) // 链表为空或者单结点，直接返回原链表
        return head;
    ListNode *rest = head->next; // head结点默认有序，剩余节点待插入
    head->next = NULL;
    while(rest) // 遍历剩余结点
    {
        ListNode *currPtr = head; // 已排序链表索引
        ListNode *prevPtr = NULL; // currPtr的前驱结点，用于插入操作
        ListNode *temp = rest->next;  // 暂存rest后面结点
        while(currPtr && currPtr->val <= rest->val) // 寻找第一个大于rest值的结点
        {
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
        if(currPtr == head) // 新结点值小于所有已排序结点 插到最前面
        {
            rest->next = head;
            head = rest;
        }
        else                // 新结点插入已排序链表
        {
            rest->next = currPtr;
            prevPtr->next = rest;
        }
        rest = temp;
    }
    return head;
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
        head = InsertionSortList(head);
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
