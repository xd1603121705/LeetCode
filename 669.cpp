// Source : https://leetcode.com/problems/trim-a-binary-search-tree/description/
// Author : Li Junjun
// Date   : 2017/09/25

/**********************************************************************************
*
*       title: 669. Trim a Binary Search Tree
*
*     problem: Given a binary search tree and the lowest and highest boundaries as 
*              L and R, trim the tree so that all its elements lies in [L, R] (R >= L). 
*              You might need to change the root of the tree, so the result should 
*              return the new root of the trimmed binary search tree.
*
*    solution: 题目的意思是写一个函数，返回树中值在给定数据域[L, R]内的子树，需要注意的
*              题目不要求进行delete操作。
*              看到题的第一反应我就顺着题的思维想着先通过层次遍历找到跟L或者R相等的结点，
*              然后再通过遍历找到所有符合要求的结点，最后新建树。这是最基本但也是最愚钝
*              的方法，跟算法毫不相关，最后看了discuss里大神的源码才知道用递归很简单。
*              颇有感慨，不管是解题还是设计程序，其实都应该多思考，要从根本上接收诸如递归
*              等思想，才能灵活运用，找到最好的解决方案。
*
* description: 大神的解法基于递归。从三个方面考虑：
*                  如果root的值val在[L, R]内，则返回root，但是要重新整理它的左右子树；
*                  如果root的值val < L，根据BST的性质，可知root的左子树不在要求的范围内，
*              返回整理后的右子树即可；
*                  如果root的值val > R，同样可知右子树不在范围内，返回整理后的左子树即可。
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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(!root)
            return root;
        if(root->val < L)
            return trimBST(root->right, L, R);
        if(root->val > R)
            return trimBST(root->left, L, R);
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
    }
};
