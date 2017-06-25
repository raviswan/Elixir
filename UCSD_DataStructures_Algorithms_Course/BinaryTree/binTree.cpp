#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "binTree.h"

using namespace std;
const int MAX_VALUE =  65535;
const int MIN_VALUE =  0;


/*--------------Binary Tree Node definition-------------------*/

int compareNodes(void* key1, void* key2){
	BinTreeNode* node1 = (BinTreeNode*) key1;
	BinTreeNode* node2 = (BinTreeNode*) key2;

	if(*(int*)node1->getData() < *(int*)node2->getData())
		return -1;
	else
		return 1;

}

/*Tree Node Constructor*/
BinTreeNode::BinTreeNode(void *data):left(NULL),right(NULL),data(data){
}

BinTreeNode::~BinTreeNode(){
}

BinTreeNode* BinTreeNode::getLeftNode() const{
	return this->left;
}

BinTreeNode* BinTreeNode::getRightNode() const{
	return this->right;
}

BinTreeNode* BinTreeNode::getParentNode() const{
	return this->parent;
}

void* BinTreeNode::getData() const{
	return data;
}


int BinTreeNode::setLeftNode(void* data) {
	this->left =  new BinTreeNode(data);
	return SUCCESS;
}


int BinTreeNode::setRightNode(void* data) {
	this->right =  new BinTreeNode(data);
	return SUCCESS;
}

int BinTreeNode::setParent(BinTreeNode* parent) {
	this->parent =  parent;
	return SUCCESS;
}

int BinTreeNode::setLeftToNull() {
	this->left =  NULL;
	return SUCCESS;
}


int BinTreeNode::setRightToNull() {
	this->right =  NULL;
	return SUCCESS;
}

bool BinTreeNode::isLeafNode() const{
	if(this->left == NULL && this->right==NULL)
		return true;
	return false;
}


/*--------------Binary Tree definition-------------------*/

/*Binary Tree Constructor*/
BinTree::BinTree():size(0),root(NULL),leafCount(0),height(-1),firstNodeFlag(false){
}

BinTree::~BinTree(){
}

int BinTree::getTreeSize() const{
	return this->size;
}

BinTreeNode* BinTree::getRoot() const{
	return this->root;
}


int BinTree::insertLeft(BinTreeNode* parent,void *data){
	/*If we are inserting a new root*/
	if(parent==NULL){
		if(this->size==0){
			root = new BinTreeNode(data);
			this->size++;
			return SUCCESS;
		}
		return FAILURE;
	}
	/*If left of parent is empty*/
	if(parent->getLeftNode()==NULL){
		/*Inserting node to left of parent*/
		if(parent->setLeftNode(data) == SUCCESS){
			this->size++;
			return SUCCESS;
		}
	}
	return FAILURE;
	
}

/*Insert a node to right of parent node*/
int BinTree::insertRight(BinTreeNode* parent,void* data){
	/*If we are inserting a new root*/
	if(parent==NULL){
		if(this->size==0){
			root = new BinTreeNode(data);
			this->size++;
			return SUCCESS;
		}
		return FAILURE;
	}
	/*If right of parent is empty*/
	if(parent->getRightNode()==NULL){
		/*Inserting node to right of parent*/
		if(parent->setRightNode(data) == SUCCESS){
			this->size++;
			return SUCCESS;
		}
	}
	return FAILURE;
}

/*Insert a node to right of parent node*/
void BinTree::connectToParent(BinTreeNode* child,BinTreeNode* parent){
	child->setParent(parent);
}


void BinTree::removeLeft(BinTreeNode* parent){
	BinTreeNode *toRemove;
	/*No removal from emtpy tree*/
	if(this->size == 0)
		return;
	/*If deleting from root*/
	if(parent == NULL)
		toRemove = this->root;
	else
		toRemove = parent->getLeftNode();
	/*recursively remove all nodes to left of parent*/
	if(toRemove != NULL){
		this->removeLeft(toRemove);
		this->removeRight(toRemove);
		//this->destroyData(toRemove);
	}
	delete(toRemove);
	this->size--;
}


void  BinTree::removeRight(BinTreeNode* parent){
	BinTreeNode *toRemove;
	/*No removal from emtpy tree*/
	if(this->size == 0)
		return;
	/*if deleting from root*/
	if(parent == NULL)
		toRemove = this->root;
	else
		toRemove = parent->getRightNode();
	/*recursively remove all nodes to right of parent*/
	if(toRemove != NULL){
		this->removeLeft(toRemove);
		this->removeRight(toRemove);
		//this->destroyData(toRemove);
	}
	delete(toRemove);
	this->size--;
}


int BinTree::destroyData(BinTreeNode* data){
	if(data){
		delete data;
		return SUCCESS;
	}
	else{
		printf("Nothing to delete\n");
		return SUCCESS;
	}
}


int BinTree::countLeaves() {
	leafCount = 0;
	doCountLeaves(root);
	return leafCount;
}

/*Recursively count the number of leaves*/
void BinTree::doCountLeaves(BinTreeNode* node){
	if(node == NULL)
		return;
	if(node->isLeafNode()){
		leafCount++;
	}
	doCountLeaves(node->getLeftNode());
	doCountLeaves(node->getRightNode());
}

/*Count number of non-leaves in the tree*/
int BinTree::countNonLeaves(){
	return(size - countLeaves());
}

/*Get the height of a tree*/
int BinTree::getHeight(){
	return (doGetHeight(root));
}

/*Recursively find height of tree. Tree with root alone has zero height*/
int BinTree::doGetHeight(BinTreeNode* node) {
	if(node==NULL)
		return -1;
	int l = doGetHeight(node->getLeftNode());
	int r = doGetHeight(node->getRightNode());
	/*Compute which side has a higher value*/
	height = 1 + std::max(l,r);
	return height;
}

/*-------------PRE-ORDER TRAVERSAL----------*/
void BinTree::printPreOrder(void (*print)(const void *data)){
	if(root==NULL)
		return;
	else
		doPrintPreOrder(this->root,print);
}


void BinTree::doPrintPreOrder(BinTreeNode* node,void (*print)(const void *data)){
	if(node==NULL)
		return;
	print(node);
	doPrintPreOrder(node->getLeftNode(),print);
	doPrintPreOrder(node->getRightNode(),print);

}

/*-------------IN-ORDER TRAVERSAL----------*/
void BinTree::printInOrder(void (*print)(const void *data)){
	if(root==NULL)
		return;
	else
		doPrintInOrder(this->root,print);
}

void BinTree::doPrintInOrder(BinTreeNode* node,void (*print)(const void *data)){
	if(node==NULL)
		return;
	doPrintInOrder(node->getLeftNode(),print);
	print(node);
	doPrintInOrder(node->getRightNode(),print);

}


/*-------------POST-ORDER TRAVERSAL----------*/
void BinTree::printPostOrder(void (*print)(const void *data)){
	if(root==NULL)
		return;
	else
		doPrintPostOrder(this->root,print);
}

void BinTree::doPrintPostOrder(BinTreeNode* node,void (*print)(const void *data)){
	if(node==NULL)
		return;
	doPrintPostOrder(node->getLeftNode(),print);
	doPrintPostOrder(node->getRightNode(),print);
	print(node);

}

/*Remove all leaves of a tree*/
void BinTree::removeLeaves(){
	if(root==NULL)
		return;
	else{
		doRemoveLeaves(root);
	}
}

/*recursively remove left and right leaves*/
void BinTree::doRemoveLeaves(BinTreeNode* node){
	if(node==NULL)
		return;
	/*If left(current node) is leaf, set left = NULL, delete left(current node)*/
	if ( (node->getLeftNode() != NULL)  ){
		if ( node->getLeftNode()->isLeafNode() == true ){
			printf("Removed %d\n",*((int*)node->getLeftNode()->getData()));
			node->setLeftToNull();
			delete node->getLeftNode();
			this->size--;
		}
	}
	/*If right(current node) is leaf, set right = NULL, delete right(current node)*/
	if ( (node->getRightNode() != NULL)  ){
		if ( node->getRightNode()->isLeafNode() == true ){
			printf("Removed %d\n",*((int*)node->getRightNode()->getData()));
			node->setRightToNull();
			delete node->getRightNode();
			this->size--;
		}
	}
	doRemoveLeaves(node->getLeftNode());
	doRemoveLeaves(node->getRightNode());
}


 bool BinTree::isBinarySearchTree(){
  	if (isBST(root,MIN_VALUE,MAX_VALUE) ) 
  		return true;
  	else
  		return false;
 }

 bool BinTree::isBST(BinTreeNode* node,int min, int max){
 	if(node == NULL)
 		return (true);
 	printf("node val = %d, min = %d , max = %d\n",*(int*)node->getData(),min,max );
 	if( *(int*)(node->getData()) <= min || *(int*)(node->getData()) >= max){
 		return false;
 	}
 	return( isBST(node->getLeftNode(),min,*(int*)node->getData()) && 
 			isBST(node->getRightNode(),*(int*)node->getData(),max) );
}

BinTreeNode* BinTree::getLeftMostNode(BinTreeNode* node){
 	while(node->getLeftNode() != NULL){
 		node = node->getLeftNode();
 	}
 	return node;
 
}

/*get next node in BST without using in-order traversal*/
BinTreeNode* BinTree::getNextNodeBST(){
	int parentVal;
	int currVal;
	int rightVal;
	if (!firstNodeFlag){
		if(root != NULL){
			current = getLeftMostNode(root);
			//printf("current=%d\n",*(int*)current->getData());
			firstNodeFlag = true;
		}
		else{
			printf("root is NULL\n");
		}
	}
	else{
		/*For a given node, compare parent and right node values*/
		currVal = *((int*)current->getData());
		/*if parent present*/
		if(current->getParentNode() != NULL){
			parentVal = * ((int*)current->getParentNode()->getData());
			//printf("currVal=%d, parentVal=%d\n",currVal,parentVal	);
			/*if current val < parent Val, you are dealing with right subtree*/
			if(currVal < parentVal){
				/*if right node present*/
				if(current->getRightNode() != NULL){
					rightVal = * ((int*)current->getRightNode()->getData());
					/*if right Val < parent Val, go down right sub-tree of current node, till you get leftmost*/
					if(rightVal < parentVal){
						current = getLeftMostNode(current->getRightNode());
					}
				}
				/*when there's no right node, return parent as next*/
				else{
					current = current->getParentNode();
				}
			}
			/*current val > parent Val, already in right subtree*/
			else{
				if(current->getRightNode()!=NULL)
					current = getLeftMostNode(current->getRightNode());
				/*reached end of right subtree, traverse all the way up till you find element > present*/
				else{
					while(currVal > parentVal){
						current = current->getParentNode();
						if(current == root){
							break;
						}
						currVal = *((int*)current->getData());
						parentVal = * ((int*)current->getParentNode()->getData());
						//printf("currVal=%d, parentVal=%d\n",currVal,parentVal	);
					}
					if(current == root){
						printf("reached end of tree\n");
						return NULL;
					}
					current = current->getParentNode();
				}
			}

		}
		/*reached root, so goto right subtree, starting with leftmost there*/
		else{
			if(current->getRightNode()!=NULL)
				current = getLeftMostNode(current->getRightNode());
			else{
				printf("reached end of tree");
				return NULL;
			}

		}
	}
 	return current;
 	

 }

 
