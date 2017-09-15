// Source : https://leetcode.com/problems/merge-two-sorted-lists/description/
// Author : Li Junjun
// Date   : 2017/09/15

/**********************************************************************************
*
*     problem: Merge two sorted linked lists and return it as a new list. 
*              The new list should be made by splicing together the nodes of the first two lists.
*
*    solution: 考虑所有的情况即可。
*
* description: 问题过于简单，直接写解决方案就好了，就不加具体实现了。
*
**********************************************************************************/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode temp(0);
        ListNode *head = &temp;
        ListNode *tail = head;
        while(l1 || l2)
        {
            if(!l1)
            {
                tail->next = l2;
                break;
            }
            if(!l2)
            {
                tail->next =l1;
                break;
            }
            if(l1->val <= l2->val)
            {
                tail->next = l1;
                tail = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                tail = l2;
                l2 = l2->next;
            }
        }
        return head->next;
    }
};