// Source : https://oj.leetcode.com/problems/intersection-of-two-linked-lists/
// Author : Li Junjun
// Date   : 2017/09/08

/**********************************************************************************
*
* Write a program to find the node at which the intersection of two singly linked lists begins.
*
* For example, the following two linked lists:
*
*
*    A:          a1 → a2
*                       ↘
*                         c1 → c2 → c3
*                       ↗
*    B:     b1 → b2 → b3
*
* begin to intersect at node c1.
*
* Notes:
*
* If the two linked lists have no intersection at all, return null.
* The linked lists must retain their original structure after the function returns.
* You may assume there are no cycles anywhere in the entire linked structure.
* Your code should preferably run in O(n) time and use only O(1) memory.
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

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if (headA == NULL || headB == NULL) //任一为空，返回NULL
		return NULL;
	int lengthA = 0, lengthB = 0, diff;
	ListNode *currPtrA = headA, *currPtrB = headB;
	ListNode *longPtr, *shortPtr;
	/* 获取链表A长度 */
	while (currPtrA) 
	{
		currPtrA = currPtrA->next;
		++lengthA;
	}
	/* 获取链表B长度 */
	while (currPtrB)
	{
		currPtrB = currPtrB->next;
		++lengthB;
	}
	diff = lengthA - lengthB;
	// 分别得到长链表、短链表
	longPtr = diff >= 0 ? headA : headB; 
	shortPtr = diff < 0 ? headA : headB;
	// 让两个链表等长
	if (diff != 0){
		for (int i = 0; i < abs(diff); i++)
			longPtr = longPtr->next;
	}
	/* 进行比较 */
	while (longPtr && shortPtr)
	{
		if (longPtr == shortPtr)
			return longPtr;
		longPtr = longPtr->next;
		shortPtr = shortPtr->next;
	}
	return NULL;
}