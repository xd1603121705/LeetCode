// Source : https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/description/
// Author : Li Junjun
// Date   : 2017/09/18

/**********************************************************************************
*
*       title: 671. Second Minimum Node In a Binary Tree
*
*     problem: Given a non-empty special binary tree consisting of nodes with the 
*              non-negative value, where each node in this tree has exactly two or 
*              zero sub-node. If the node has two sub-nodes, then this node's value 
*              is the smaller value among its two sub-nodes.

*              Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

*              If no such second minimum value exists, output -1 instead.
*
*    solution: 题目要求找出树中第二小的数，可以通过遍历时比较，也可以遍历把所有的值
*              存到set里（set自动排序且无重复值）。
*
* description: 多想想各种数据结构的特性，灵活运用。
*
**********************************************************************************/

// 用set
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
    int findSecondMinimumValue(TreeNode* root) {
    set<int> vals;
    stack<TreeNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {//BFS
        TreeNode* node = nodes.top();
        nodes.pop();
        vals.insert(node->val);
        if (node->left){
            nodes.push(node->left);
            nodes.push(node->right);
        }
    }
    set<int>::iterator it = vals.begin();
    if (vals.size() > 1)//取第二个元素
        return *(++it);
    else
        return -1;
}
};

// 直接遍历
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
    int minVal(TreeNode* node, int val) {
        if (node->val != val)
            return node->val;
        else if (node->val == val && node->left)
            return min(minVal(node->left, val), minVal(node->right, val));
        else
            return INT_MAX;
    }
    int findSecondMinimumValue(TreeNode* root) {
        if (root == NULL || root->left == NULL)
            return -1;
        int val = root->val;
        int ans = minVal(root,val);
        return ans == INT_MAX ? -1 : ans;
    }
};