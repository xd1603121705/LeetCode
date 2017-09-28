// Source : https://leetcode.com/problems/average-of-levels-in-binary-tree/description/
// Author : Li Junjun
// Date   : 2017/09/28

/**********************************************************************************
*
*       title: 637. Average of Levels in Binary Tree
*
*     problem: Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

*              Example 1:
*              Input:
*                  3
*                 / \
*                9  20
*                  /  \
*                 15   7
*              Output: [3, 14.5, 11]
*              Explanation:
*              The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
*
*    solution: 问题要求二叉树中每层结点的平均值，显然要用层次遍历，对于level的判断刚好
*              刚好借助层次遍历中用到的队列长度，在每层出队之前队列的长度刚好可以作为
*              循环变量判断每层的结束，详见代码。
*
* description: 其实此题主要考察对层次遍历的熟悉程度啦。
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> sum;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            long temp=0;
            int s=q.size();
            for(int i = 0; i < s; i++) {
                TreeNode* t=q.front();
                q.pop();
                if(t->left) q.push(t->left);
                if(t->right) q.push(t->right);
                temp+=t->val;
            }
            sum.push_back((double)temp/s);
        }
        return sum;
    }
};