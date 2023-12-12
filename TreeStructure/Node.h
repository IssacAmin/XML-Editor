/*
 * Node.h
 *
 *  
 *      Author: Poula
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <iostream>
using namespace std;

class Node {
private:

	int dataInt;
	string dataString;
	int level;
	string tagName;
	Node* parent;
    vector<Node *> children;

public:
	Node();
	Node(int data, int Level, string tagName);
	Node(string data, int Level, string tagName);

	~Node();

    void add(Node* n);
    Node* getNode(int i);
    int getChildrenNumber();
	vector<Node*>& getChildren();
	void setChildren( vector<Node*>& children);
	int getDataInt()  ;
	void setDataInt(int dataInt);
	string& getDataString() ;
	void setDataString( string& dataString);
	int getLevel() ;
	void setLevel(int level) ;

	 Node*& getParent();

	 void setParent( Node*& parent);

	string& getTagName();

	void setTagName( string& tagName);

	void printNode();


};

#endif /* NODE_H_ */

