#include "BSTY.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

BSTY::BSTY() {
	root = NULL;
}

// You write:  insert a new node with data x (a string) into the
// binary search tree
// This method should return true if a new node is inserted and
// false if the data x is already in the tree
// Remember to check whether the new node will be the root
// (meaning the root is currently NULL) and if so, set the root
// to be the new node.
// Note: Make sure you make the new node point to its parent!!!
// Note2: after you've inserted a new node, you should call the
// adjustHeights method that will update the heights of all the
// ancestors of the node that was just inserted.
bool BSTY:: insertit(string x) {
	//Iterative method

	if (root == NULL) {
		NodeT *newNode = new NodeT(x);
		root = newNode;
		root -> height = 1;
		//Don't need to adjust heights if creating root
		return true;
	}

	else {
		NodeT *tmp = root;
		while (tmp != NULL) {
			if (x < (tmp -> data)) {
				if ((tmp -> left) == NULL) {
					NodeT *newNode = new NodeT(x);
					tmp -> left = newNode;
					newNode -> parent = tmp;
					adjustHeights(newNode -> parent); //Update the heights starting with parent
					return true;
				}
				else {
					tmp = tmp -> left;
				}
			}

			else if (x > (tmp -> data)) {
				if ((tmp -> right) == NULL) {
					NodeT *newNode = new NodeT(x);
					tmp -> right = newNode;
					newNode -> parent = tmp;
					adjustHeights(newNode -> parent); //Update the heights starting with parent
					return true;
				}
				else {
					tmp = tmp -> right;
				}
			}
			else {
				return false; //Already in tree
			}
		}
	}
}

// the adjustHeights method updates the heights of every ancestor of the node n.
// This method will be massively useful with our next lab, so make sure you have
// this working now.  It should be called whenever you change the height of a
// a particular node.  So, for instance, when a new node is inserted as a leaf,
// its height is 1.  The adjustHeights method should then check the parent to see
// if the height of the parent changes (the height of each node is the maximum of
// the height of the left child and the height of the right child, plus 1).  If
// the parent's height changes, then the grandparent's height should be checked and,
// if necessary, adjusted.  If the grandparent's height is updated, then the great-
// grandparent's height should be adjusted, etc.  The checking stops when either
// the loop has worked its way up to the root, or until the currently being checked
// ancestor is not changed.
void BSTY::adjustHeights(NodeT *n) {

	int prevHeight;
	int newHeight;
	int leftHeight;
	int rightHeight;

	if (n == root) {
		return;
	}

	//Do while the parent exists
	//Last iteration will be the root

	while (n != NULL){

		prevHeight = n -> height;

		if (n -> left == NULL) {
			leftHeight = 0;
		}
		else {
			leftHeight = n -> left -> height;
		}

		if (n -> right == NULL) {
			rightHeight = 0;
		}
		else {
			rightHeight = n -> right -> height;
		}


		if (leftHeight > rightHeight) {
			newHeight = 1 + leftHeight;
		}
		else {
			newHeight = 1 + rightHeight;
		}

		if (newHeight == prevHeight) {
			return; //Exit because no change
		}

		else {
			n -> height = newHeight;
		}

		n = n -> parent;  //Go up the tree

	}


}

void BSTY::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreeIO(root);
	}
}

// Print the tree in order (left child, then parent, then right child).
// Use the slides, but make sure you can understand how the tree is
// traversed in order
void BSTY::printTreeIO(NodeT *n) {
	if (n == NULL) {
		return;
	}

	else {
		printTreeIO(n->left);
		n -> printNode();
		printTreeIO(n->right);
	}
}

void BSTY::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreePre(root);
	}
}

// Prints the tree using pre-order traversal (parent, then left child, then right
// child.  Use the slides, but make sure you understand how a tree is traversed in
// pre-order
void BSTY::printTreePre(NodeT *n) {
	if (n == NULL) {
		return;
	}

	else {
		n -> printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

void BSTY::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreePost(root);
		cout << endl;
	}
}

// Prints the tree using pre-order traversal (left child, then right, then parent)
// Use the slides, but make sure you understand how a tree is traversed in
// post-order
void BSTY::printTreePost(NodeT *n) {
	if (n == NULL) {
		return;
	}

	else {
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}

}
void BSTY::myPrint() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		myPrint(root);
		cout << endl;
	}
}
void BSTY::myPrint(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		myPrint(n->left);
		cout << n->data.length()-1;
		if (mine) {
			cout <<".";
			mine = false;
		}
		myPrint(n->right);
	}
}

// the find method takes as input a string, and finds whether that string is already
// in the tree or not.  If it is in the tree, that node is returned from the tree.
// If it isn't, NULL is returned.
// NOTE: If the node can't be found, this method prints out that x can't be found.
// if it is found, the printNode method is called for the node.
NodeT *BSTY::find(string x) {

	if (root == NULL) {
		cout << "x can't be found" << endl;
	}

	NodeT *tmp = root;
	/*
	 * Start with the root and then compare node to the data
	 * Move left if the data is less than the node
	 * Move right if the data is less than the node
	*/
	while (tmp != NULL) {
		if (x == (tmp -> data)) {
			tmp->printNode();
			return tmp;
		}
		else if (x < (tmp -> data)) {
			tmp = tmp -> left;

			continue;

		}
		else if (x > (tmp -> data)){
			tmp = tmp -> right;

			continue;
		}

		else {
			cout<<x<<"can't be found";
			return NULL;
		}
	}


}

/*************************************************************************************/
/* Extra Credit Methods                                                              */
/* Challenging: worth 35 EC pts to go towards labs                                   */
/* NOTE: IF YOU CHOOSE NOT TO IMPLEMENT THESE METHODS, YOU ARE STILL RESPONSIBLE FOR */
/* UNDERSTANDING HOW THEY WORK!!                                                     */
/*************************************************************************************/
/* When removing a node from a binary search tree, the resulting tree MUST BE a binary
/* search tree.
/*
/* When removing a node, there are 3 conditions:
/* 1: when the node being removed has no children, in which case the node is deleted,
/* the node's parent is set to NULL, and the node's parent's height is adjusted (if
/* necessary) and heights on up are adjusted.
/* 2: when the node being removed has one child, in which case the node's parent points
/* to the node's child, and the node's child points to the node's parent, and the node
/* is deleted (and the height of the parent on up as necessary is adjusted)
/* 3: when the node has 2 children, in which case the left-most child of the node's
/* right child replaces the node.
/* A couple of notes about this one: you are replacing a node with a node that is lower
/* down in the tree.  That means that you are, in essence, removing the node from that
/* lower position and moving it up to the old node's location.  Thus the replacing node
/* must be removed using 1 or 2 above (why not 3?).  The heights must be adjusted after
/* the replacing node is removed from its old location but before it is inserted into its
/* new location.  Equally, the replacing node's height must be adjusted to be the larger of
/* its two children's heights before you adjust heights above that.
/*****************************************************************************************/
/* remove(): takes as input a string, uses the find method to find the node in the tree that
/* holds that string, and then calls replace1, replace2, or replace3 depending on what type
/* of replacing should be done.  It adjusts the heights, deletes teh node, and returns
/* true if the removal was successful.
*/
bool BSTY::remove(string s) {
	NodeT *search = find(s);
	if (search != NULL) {
		if ((search -> left == NULL) && (search -> right == NULL)) {
			//when node has no children
			remove1(search);
			return true;
		}


		else if ((search -> left != NULL) && (search -> right != NULL)) {
			//when node has two children
			remove3(search);
			return true;
		}

		else {
			remove2(search);
			return true;
		}

	}
	return false;
}

/* remove1(): called when the node to be removed has no children. Takes as input the
/* node to be removed, and sets the parent of the node to point to NULL.
/* helpful hint: if (n->parent->left == n) is true, then n is its parent's left child.
/* Make sure you check to whether n is the root or not.
*/
void BSTY::remove1(NodeT *n) {
	if(n==root){

		return;
	}
	NodeT *nParent = n -> parent;
	if ((n -> parent -> left) == n) {
		n -> parent -> left = NULL;
		delete n;

	}
	else {
		n -> parent -> right = NULL;
		delete n;
	}

	adjustHeights(nParent);

}

/* remove2(): called when the node to be removed has 1 child only.  Takes as input
/* the node to be removed and bypasses it by making the parent point to the node's
/* one child, and makes the node's one child point to the node's parent.
/* This one needs a bunch of checking - you need to see if the node is the parent's
/* left or right child, and you need to see if the node's child is its left or its
/* right child.
/* Also, make sure you check that if the node to be removed is the root, then the
/* one child becomes the root.
*/
void BSTY::remove2(NodeT *n) {

	if(n == root){

			NodeT *tmp;

				if(n->right != NULL){

					tmp = n->right;

					delete n;

					root = tmp;
				}

				else if(n->left !=NULL){

					tmp = n->left;

					delete n;

					root = tmp;
				}

		}

		if(n->parent != NULL){

			if(n == n->parent->right){

				if(n->right !=NULL){

					n->parent->right = n->right;
				}

				if(n->left !=NULL){

					n->parent->right = n->left;
				}

				adjustHeights(n->parent);
			}

			else{
				if(n == n->parent->left){
					if(n->right !=NULL){

						n->parent->left = n->right;
					}

					if(n->left !=NULL){
						n->parent->left = n->right;
					}
				}

				adjustHeights(n->parent);
			}
		}


}

/* remove3(): called when the node to be removed has 2 children.  Takes as input the
/* node to be removed.  The node to replace the node to be removed should be the
/* left-most descendent of the node's right child.  That way the binary search tree
/* properties are guaranteed to be maintained.
/* When replacing the node to be removed with the replacing node, the replacing node
/* is, in essence, being removed from its place in the tree, and thus replace1 or
/* replace2 methods should be used.
/* The new node's parent must be set to the removed node's parent, the removed node's
/* parent must point to the new node, the new node's left child must point to the
/* removed node's left child (and the child must point to the new node as a parent),
/* and the same for teh right child.
/* Remember to take into account that the node being removed might be the root.
*/
void BSTY::remove3(NodeT *n) {






	if(n == root){


				if(n->left !=NULL && n->right !=NULL){

					if(n->right->left !=NULL){



						n->data = n->right->left->data;

						NodeT *tmproot;
											tmproot = n->right->left; //tmproot hold that node

											if(tmproot->right == NULL && tmproot->left == NULL){

												remove1(tmproot);
											}
											else{
												remove2(tmproot);
											}
					}

				}


		}

		if(n->parent != NULL){
			if(n->left != NULL && n->right !=NULL){

				if(n->right->left !=NULL){ //Checking the left-most descendant of the node's right child
					n->data = n->right->left->data;

					NodeT *tmp;
					tmp = n->right->left; //tmp hold that node

					if(tmp->right == NULL && tmp->left == NULL){

						remove1(tmp);
					}
					else{
						remove2(tmp);
					}



				}


			}


			adjustHeights(n->parent);
		}

}

/* findMin(): takes as input a node, and finds the left-most descendant of its
/* right child.  The left-most descendent is returned.
*/
NodeT *BSTY::findMin(NodeT *n) {

	while (n -> left != NULL) {
		n =  n -> left;
	}

	//Will return the root if no other values in tree
	return n;
}

void BSTY::myPrintEC() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		myPrintEC(root);
		cout << endl;
	}
}
void BSTY::myPrintEC(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		myPrintEC(n->left);
		cout << alpha[n->data.length()-2];
		myPrintEC(n->right);
	}
}


/************************************************************************/


