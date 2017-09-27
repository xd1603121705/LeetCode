// Source : https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
// Author : Li Junjun
// Date   : 2017/09/27

/**********************************************************************************
*
*       title: 653. Two Sum IV - Input is a BST
*
*     problem: Given a Binary Search Tree and a target number, return true if there
*              exist two elements in the BST such that their sum is equal to the 
*              given target.
*
*              Example 1:
*              Input: 
*                  5
*                 / \
*                3   6
*               / \   \
*              2   4   7
*
*              Target = 9

*              Output: True
*              Example 2:
*              Input: 
*                  5
*                 / \
*                3   6
*               / \   \
*              2   4   7
*              
*              Target = 28

*              Output: False
*
*    solution: 这里用了一种新的数据结构---unordered_set，
*              unordered_set/unordered_multiset/unordered_map/unordered_multimap是C++11新
*              加入的标准库顾名思义是无序的set/multiset/map/multimap，但底层实用hashtable
*              实现的，所以可以在答题时用来当做hashtable，更加方便易用。
*
* description: 从discuss那里抄来的...
*
**********************************************************************************/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

    bool dfs(TreeNode *root, unordered_set<int> &set, int k) // 注意这里要用引用
	{
		if (!root)
			return false;
		if (set.count(k - root->val)) //count返回键值查询到的条目数
			return true;
		set.insert(root->val); // insert插入新元素
		return dfs(root->left, set, k) || dfs(root->right, set, k);
	}
 
	bool findTarget(TreeNode* root, int k) {
		unordered_set<int> set;
		return dfs(root, set, k);
	}
};