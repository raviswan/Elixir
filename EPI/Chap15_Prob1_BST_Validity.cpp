#include <iostream>
#include <memory>
const int MIN = -32768;
const int MAX =  +32767;

template<typename T>
struct BSTNode{
	T data;
	std::unique_ptr<BSTNode<T>> left,right;
};

bool checkBST(std::unique_ptr<BSTNode<int>>& root,int minVal, int maxVal){
	if(root ==nullptr)
		return true;
	else if ( (root->data < minVal) || (root->data > maxVal) )
		return false;
	return (checkBST(root->left,minVal,root->data) && checkBST(root->right,root->data,maxVal) );
} 

bool isBST(std::unique_ptr<BSTNode<int>> root){
	return (checkBST(root,std::numeric_limits<int>::min(),std::numeric_limits<int>::max()));	
}


int main(int argc, char** argv){
	return 0;
}