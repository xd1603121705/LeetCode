// Source : https://leetcode.com/problems/reorder-list/description/
// Author : Li Junjun
// Date   : 2017/09/14

/**********************************************************************************
*
*     problem: Given a singly linked list L: L0?L1?��?Ln-1?Ln,
*              reorder it to: L0?Ln?L1?Ln-1?L2?Ln-2?��
*
*              You must do this in-place without altering the nodes' values.
*
*              For example,
*              Given {1,2,3,4}, reorder it to {1,4,2,3}.
*
*    solution: �ҵ��м��㣬��ת��벿�֣��ٽ�����빹��������
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
                     reorder list is: 5->1->4->2->3
                     original list is: 6->3->5->7->9->2->1->4->8->0
                     reorder list is: 6->0->3->8->5->4->7->1->9->2
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

/* ��ת���� */
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

/* ����ϲ������ź������� */
ListNode* MergeList(ListNode *left, ListNode *right)
{
    ListNode *head = left; // left���׽��Ϊ��������׽��
    left = left->next; // ��ߵ�һ��Ĭ���׽�㣬�ӵڶ�����ʼ�ϲ�
    ListNode *tail = head; // �������β���
    bool leftNode = false; // ѡ��ı�־ Ϊtrueѡ��left��� falseѡ��right���
    while(left || right) // "||"������֤���н����ϲ�
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
        leftNode = leftNode ? false : true; // ÿ�β�������־ȡ��
    }
    return head;
}

/* Reorder List */
void ReorderList(ListNode *head)
{
    if(!head || !head->next)
        return;
    /* ����ָ���ҵ������м��� �м������һ���Ϊ�������β��� */
    ListNode *low = head;
    ListNode *fast = head;
    while(fast->next && fast->next->next)
    {
        fast = fast->next->next;
        low = low->next;
    }
    /* �����Ϊ������ */
    fast = low->next;
    low->next = NULL;

    fast = ReverseList(fast);  // ��ת�Ұ벿��
    head = MergeList(head, fast);  // �ϲ�
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
