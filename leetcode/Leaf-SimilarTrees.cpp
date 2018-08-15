//https://leetcode.com/problems/leaf-similar-trees/description/
#include<iostream>
#include<vector>
#include<array>
#include<string.h>



using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	 bool leafSimilar(TreeNode* root1, TreeNode* root2) {
			vector<int> LF1, LF2;
			getLeafNode(root1, LF1);
			getLeafNode(root2, LF2);
			return std::equal(LF1.cbegin(), LF1.cend(), LF2.cbegin());

	 }
	void getLeafNode(TreeNode* node, vector<int>& leafval){
		if(node->left==nullptr&&node->right==nullptr)
			leafval.push_back(node->val);
		else{
			if(node->left!=nullptr)
				getLeafNode(node->left, leafval);
			if(node->right!=nullptr)
				getLeafNode(node->right,leafval);

		}
	}

};
int main(void){
	Solution solu_t;
	//cout<<solu_t.le(100,99)<<endl;;
	return 0;
}


