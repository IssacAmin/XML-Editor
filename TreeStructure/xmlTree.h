/*
 * xmlTree.h
 *
 *  
 *      Author: Poula
 */


#ifndef xmlTree_H_
#define xmlTree_H_

#include <iostream>
#include <vector>
#include "Node.h"
class xmlTree { //Root Node

	Node *root;
public:
	int currentLevel = 0;
	Node* currentNode = NULL;

	xmlTree();
	xmlTree(Node*);
	~xmlTree();


	bool empty() ;
	void setRoot(Node *n);
	Node* getRoot();
	void deleteTree();
};

void deleteSubTree(Node* n);
void printTree(Node* node);

#endif /* xmlTree_H_ */
