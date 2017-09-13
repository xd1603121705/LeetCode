// Source : https://leetcode.com/problems/insertion-sort-list/description/
// Author : Li Junjun
// Date   : 2017/09/13

/**********************************************************************************
*
*     problem: Sort a linked list in O(n log n) time using constant space complexity.
*
*    solution: ֱ�Ӳ��������㷨ʵ����������
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

/* ֱ�Ӳ��������㷨ʵ���������� */
ListNode* InsertionSortList(ListNode *head)
{
    if(!head || !head->next) // ����Ϊ�ջ��ߵ���㣬ֱ�ӷ���ԭ����
        return head;
    ListNode *rest = head->next; // head���Ĭ������ʣ��ڵ������
    head->next = NULL;
    while(rest) // ����ʣ����
    {
        ListNode *currPtr = head; // ��������������
        ListNode *prevPtr = NULL; // currPtr��ǰ����㣬���ڲ������
        ListNode *temp = rest->next;  // �ݴ�rest������
        while(currPtr && currPtr->val <= rest->val) // Ѱ�ҵ�һ������restֵ�Ľ��
        {
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
        if(currPtr == head) // �½��ֵС�������������� �嵽��ǰ��
        {
            rest->next = head;
            head = rest;
        }
        else                // �½���������������
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
