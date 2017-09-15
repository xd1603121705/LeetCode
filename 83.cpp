// Source : https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
// Author : Li Junjun
// Date   : 2017/09/15

/**********************************************************************************
*
*     problem: Given a sorted linked list, delete all duplicates such that each element appear only once.
*
*			   For example,
*              Given 1->1->2, return 1->2.
*              Given 1->1->2->3->3, return 1->2->3.
*
*    solution: 两个指针一前一后来遍历，若值相等，则把前指针指向后指针的next就可以了。
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head)
            return head;
        ListNode *currPtr = head->next; 
        ListNode *prevPtr = head;       
        while(currPtr)
        {
            if(currPtr->val == prevPtr->val)
                prevPtr->next = currPtr->next;
            else
                prevPtr = currPtr;
            currPtr = currPtr->next;
        }
        return head;
    }
};
