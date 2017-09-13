// Source : https://oj.leetcode.com/problems/sort-list/
// Author : Li Junjun
// Date   : 2017/09/13

/**********************************************************************************
*
*     problem: Sort a linked list in O(n log n) time using constant space complexity.
*
*    solution: ��ĿҪ��O(n log n)��ʱ�临�Ӷȣ���ѡ�����㷨Ϊ�������򡢶�����͹�
*              �����򣬿�������ﵽO(n^2)�������ų�����������Ȼ�����õ�����Ľ�
*              �����鲢������Ƿ���Ҫ��������㷨�����ڿռ临�Ӷȣ���Ϊ�ṹΪ����
*              ��������ָ�뼴�ɣ����������������������ٿռ䣬���Դ���ѡ�ù鲢����
*
* description: ������������ض������ļ��У������"data.in"�ж�ȡ��������뵽
*              "data.out"�С�
*              ���룺��һ��Ϊ�����ĿN�������ַ��˳������ڶ���ΪN��������
*              ������5
                     5 4 3 2 1
                     10
                     6 3 5 7 9 2 1 4 8 0
                     q
               �����original list is: 5->4->3->2->1
                     sorted list is: 1->2->3->4->5
                     original list is: 6->3->5->7->9->2->1->4->8->0
                     sorted list is: 0->1->2->3->4->5->6->7->8->9
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
    ListNode(int x): val(x), next(NULL){}
};

/* ��ӡ���� */
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

/* ��������*/
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

/* ������� */
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

    // ����ָ���ҵ������е�
    ListNode *low = head;
    ListNode *fast = head;
    while(fast->next && fast->next->next)
    {
        low = low->next;
        fast = fast->next->next;
    }

    // ����������
    fast = low->next;
    low->next = NULL;

    // ��������ֱ�����
    ListNode *left = sortList(head);
    ListNode *right = sortList(fast);

    // �ϲ�
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
    int n; // ������
    int val; // ���ֵ
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
