// Source : https://leetcode.com/problems/copy-list-with-random-pointer/description/
// Author : Li Junjun
// Date   : 2017/09/18

/**********************************************************************************
*
*       title: 138. Copy List with Random Pointer
*
*     problem: A linked list is given such that each node contains an additional 
*              random pointer which could point to any node in the list or null.
*
*              Return a deep copy of the list.
*
*    solution: 在原链表的每个节点之后插入一个新的节点，这样原节点与新节点的对应关
*              系就已经明确了，因此不需要用hash_map保存，但是需要第三次循环将整个
*              链表拆分成两个。这种方法的时间复杂度是O(n)，空间复杂度是O(1)。
*
* description: 问题过于简单，直接写解决方案就好了，就不加具体实现了。
*
**********************************************************************************/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
	/* newList表示新链表 curr代表原链表当前结点 newNode代表当前结点后的新结点 */
	RandomListNode *newList, *curr, *newNode;
	if (!head)
		return NULL;
	/* step1：在链表中每个节点后插入新结点 */
	for (curr = head; curr != NULL; curr = curr->next->next)
	{
		newNode = new RandomListNode(curr->label);
		newNode->next = curr->next;
		curr->next = newNode;
	}

	/* step2：根据原结点的random指针给新结点的random指针赋值 */
	for (curr = head; curr != NULL; curr = curr->next->next)
		curr->next->random = curr->random ? curr->random->next : NULL;
	
	/* step3：将链表拆分 */
	newList = head->next;
	for (curr = head; curr != NULL; curr = curr->next)
	{
		RandomListNode *tail = curr->next;
		curr->next = tail->next;
		if (tail->next)
			tail->next = tail->next->next;
	}
	return newList;
}
};
