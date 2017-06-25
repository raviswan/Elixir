#include "binTree.h"
 /*   BST
 		12                           10
        / \                           \
       11  13                         12
       /\   \                         /\
      9 11.5 14                      9 13
 */

void printNodeData(const void* node){
	BinTreeNode* elem = (BinTreeNode*) node;
	printf("%d\n",*(int*)elem->getData());
}


void BuildTreeOne(BinTree &t, int data[]){
	t.insertLeft(NULL,&data[0]);
	t.insertLeft(t.getRoot(),&data[1]);
	t.insertLeft((t.getRoot())->getLeftNode(),&data[2]);
	t.insertLeft((t.getRoot())->getLeftNode()->getLeftNode(),&data[3]);
	t.insertRight(t.getRoot(),&data[4]);
	t.insertLeft((t.getRoot())->getRightNode(),&data[5]);
	t.insertRight((t.getRoot())->getRightNode(),&data[6]);
	t.insertRight((t.getRoot())->getRightNode()->getRightNode(),&data[7]);
	t.insertRight((t.getRoot())->getRightNode()->getRightNode()->getRightNode(),&data[8]);
}

void BuildTreeTwo(BinTree &t, int data[]){
	t.insertLeft(NULL,&data[0]);
	t.connectToParent(t.getRoot(),NULL);

	t.insertLeft(t.getRoot(),&data[1]);
	t.connectToParent((t.getRoot())->getLeftNode(),t.getRoot());

	t.insertLeft((t.getRoot())->getLeftNode(),&data[2]);
	t.connectToParent((t.getRoot())->getLeftNode()->getLeftNode(),(t.getRoot())->getLeftNode());

	t.insertLeft((t.getRoot())->getLeftNode()->getLeftNode(),&data[3]);
	t.connectToParent((t.getRoot())->getLeftNode()->getLeftNode()->getLeftNode(),
		(t.getRoot())->getLeftNode()->getLeftNode());

	t.insertRight((t.getRoot())->getLeftNode()->getLeftNode(),&data[4]);
	t.connectToParent((t.getRoot())->getLeftNode()->getLeftNode()->getRightNode(),
		(t.getRoot())->getLeftNode()->getLeftNode());

	t.insertRight((t.getRoot())->getLeftNode(),&data[5]);
	t.connectToParent((t.getRoot())->getLeftNode()->getRightNode(),
		(t.getRoot())->getLeftNode());

	t.insertRight(t.getRoot(),&data[6]);
	t.connectToParent((t.getRoot())->getRightNode(),t.getRoot());

	t.insertLeft((t.getRoot())->getRightNode(),&data[7]);
	t.connectToParent((t.getRoot())->getRightNode()->getLeftNode(),(t.getRoot())->getRightNode());

	t.insertRight((t.getRoot())->getRightNode(),&data[8]);
	t.connectToParent((t.getRoot())->getRightNode()->getRightNode(),(t.getRoot())->getRightNode());
}


int main(){
	BinTree tree1, tree2;
	/*elements in pre-order*/
	//int treeOneData[] = {1,2,4,7,3,5,6,8,9};
	int treeTwoData[] = {6,4,2,1,3,5,8,7,9};
	int treeOneData[] = {11,10,9,8,13,7,16,18,19};
	

	BuildTreeOne(tree1,treeOneData);
	BuildTreeTwo(tree2,treeTwoData);

	if (tree1.isBinarySearchTree() )
		printf("tree1 is a BST\n\n");
	else
		printf("tree1 is not a BST\n\n");


	if (tree2.isBinarySearchTree() )
		printf("tree2 is a BST\n");
	else
		printf("tree2 is not a BST\n");



	printf("no. of leaves in Tree 1 = %d\n",tree1.countLeaves());
	printf("no. of leaves in Tree 2 = %d\n",tree2.countLeaves());
	printf("\nno. of non-leaves in Tree 1 = %d\n",tree1.countNonLeaves());
	printf("no. of non-leaves in Tree 2 = %d\n",tree2.countNonLeaves());
	printf("\nHeight of Tree 1 = %d\n",tree1.getHeight());
	printf("Height of Tree 2 = %d\n",tree2.getHeight());

	printf("\n\nPrinting Tree1 in Pre-Order \n");
	tree1.printPreOrder(printNodeData);
	printf("Printing Tree1 in In-Order \n");
	tree1.printInOrder(printNodeData);
	printf("Printing Tree1 in Post-Order \n");
	tree1.printPostOrder(printNodeData);

	printf("\n\nPrinting Tree2 in Pre-Order \n");
	tree2.printPreOrder(printNodeData);
	printf("Printing Tree2 in In-Order \n");
	tree2.printInOrder(printNodeData);
	printf("Printing Tree2 in Post-Order \n");
	tree2.printPostOrder(printNodeData);

	printf("\nRemoving leaves from tree1\n");
	tree1.removeLeaves();
	printf("Printing Tree1 in Pre-Order after removal\n");
	tree1.printPreOrder(printNodeData);
	printf("Printing Tree1 in In-Order after removal \n");
	tree1.printInOrder(printNodeData);
	printf("Printing Tree1 in Post-Order after removal \n");
	tree1.printPostOrder(printNodeData);
/*
	printf("\nRemoving leaves from tree2\n");
	tree2.removeLeaves();
	printf("Printing Tree2 in Pre-Order after removal \n");
	tree2.printPreOrder(printNodeData);
	printf("Printing Tree2 in In-Order after removal \n");
	tree2.printInOrder(printNodeData);
	printf("Printing Tree2 in Post-Order after removal \n");
	tree2.printPostOrder(printNodeData);
*/

	printf("\n----Printing BST in ascending order-----\n");
	BinTreeNode* node = tree2.getNextNodeBST();
	while(node != NULL){
		printf("value is : %d\n",*(int*)node->getData());
		node = tree2.getNextNodeBST();

	}

	

	return 0;

}