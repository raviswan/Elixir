#include <iostream>
#include <memory>
#include <vector>

template<typename T>
struct TreeNode{
	T data;
	std::unique_ptr<TreeNode<T>> left, right;
};


void findKlargest(std::unique_ptr<TreeNode<int>>& tree, std::vector<int>* vec,int k){
	if(tree && vec->size() < k){
		findKlargest(tree->right,vec, k);
		if(vec->size() < k){
			vec->emplace_back(tree->data);
			findKlargest(tree->left,vec, k);
		}
	}

}

std::vector<int> findK(std::unique_ptr<TreeNode<int>> root, int k){
	std::vector<int> vec;
	findKlargest(root,&vec,k);
	return vec;
}

