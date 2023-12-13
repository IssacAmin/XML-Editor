/*
 * xmlTree.cpp
 *
 *  
 *      Author: Poula
 */

#include "xmlTree.h"

xmlTree::xmlTree() {
	root = NULL;
}
xmlTree::xmlTree(Node* r){
	root = r;
}
xmlTree::~xmlTree() {
	deleteTree();
}
bool xmlTree::empty() {return root == NULL;}
void xmlTree::setRoot(Node *n) {root = n;}
Node* xmlTree::getRoot() {return root;}
void xmlTree::deleteTree(){
	deleteSubTree(root);
}
void deleteSubTree(Node* node){
	if(node == NULL){
		return;
	}

	if(node->getChildren().size() > 0){
		for(int i = 0, n = node->getChildrenNumber(); i < n; i++){
			deleteSubTree(node->getChildren()[i]);
		}
		delete node;

}
}
void printTree(Node* root){
	if(root == NULL){
		return;
	}
	else{
		Node* node = root;
		node->printNode();

			if(node->getChildren().size() > 0){
				for(int i = 0, n = node->getChildrenNumber(); i < n; i++){
					printTree(node->getChildren()[i]);
				}

		}
	}
}


